// CTab1View.cpp: 구현 파일
//

#include "pch.h"
#include "MFCBreadFactory.h"
#include "afxdialogex.h"
#include "CTab1Dlg.h"


// CTab1Dlg 대화 상자

IMPLEMENT_DYNAMIC(CTab1Dlg, CDialog)

CTab1Dlg::CTab1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_TAB1_FORM, pParent),
	m_caps(4),
	m_frames(4),
	m_mutexes(4),
	m_bThreadRunning(false)
{

}

CTab1Dlg::~CTab1Dlg()
{
	m_bThreadRunning = false;
	for (auto& th : m_threads)
	{
		if (th.joinable())
		{
			th.join();
		}
	}
}

void CTab1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC_CAM1, m_picCam1);
	DDX_Control(pDX, IDC_STATIC_CAM2, m_picCam2);
	DDX_Control(pDX, IDC_STATIC_CAM3, m_picCam3);
	DDX_Control(pDX, IDC_STATIC_CAM4, m_picCam4);
}


BEGIN_MESSAGE_MAP(CTab1Dlg, CDialog)
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CTab1Dlg 메시지 처리기

BOOL CTab1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_bThreadRunning = true;
	for (int i = 0; i < 4; ++i)
	{
		// 각 카메라에 대한 스레드 생성
		m_threads.emplace_back(&CTab1Dlg::CameraThread, this, i);
	}

	// 100ms 간격으로 화면 갱신 타이머 설정
	SetTimer(TIMER_UPDATE_CAMERA, 100, NULL);

	return TRUE;
}

// 각 카메라의 영상 프레임을 독립적으로 받아오는 스레드 함수
void CTab1Dlg::CameraThread(int index)
{
	if (index < 0 || index >= m_cameraUrls.size()) return;

	while (m_bThreadRunning)
	{
		try
		{
			if (!m_caps[index].isOpened())
			{
				if (!m_caps[index].open(m_cameraUrls[index]))
				{
					std::this_thread::sleep_for(std::chrono::seconds(5));
					continue;
				}
			}

			cv::Mat tempFrame;
			if (m_caps[index].read(tempFrame))
			{
				std::lock_guard<std::mutex> lock(m_mutexes[index]);
				m_frames[index] = tempFrame.clone();
			}
			else
			{
				m_caps[index].release();
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
		}
		catch (const cv::Exception& e)
		{
			// OpenCV 예외 처리
			m_caps[index].release();
			std::this_thread::sleep_for(std::chrono::seconds(5));
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(30)); // 약 33fps
	}
	if (m_caps[index].isOpened())
	{
		m_caps[index].release();
	}
}

// 받아온 프레임을 CStatic 컨트롤에 그리는 함수
void CTab1Dlg::DrawFrame(int index)
{
	CStatic* pPic;
	switch (index)
	{
	case 0: pPic = &m_picCam1; break;
	case 1: pPic = &m_picCam2; break;
	case 2: pPic = &m_picCam3; break;
	case 3: pPic = &m_picCam4; break;
	default: return;
	}

	if (!pPic->GetSafeHwnd()) return;

	cv::Mat currentFrame;
	{
		std::lock_guard<std::mutex> lock(m_mutexes[index]);
		if (m_frames[index].empty())
		{
			return;
		}
		currentFrame = m_frames[index].clone();
	}

	CRect rect;
	pPic->GetClientRect(&rect);

	// 프레임 크기를 CStatic 컨트롤 크기에 맞게 조절
	cv::resize(currentFrame, currentFrame, cv::Size(rect.Width(), rect.Height()));

	// Mat을 CImage로 변환하여 화면에 출력
	CImage cimage;
	int bpp = currentFrame.channels() * 8;
	cimage.Create(currentFrame.cols, currentFrame.rows, bpp);
	if (bpp == 8)
	{
		static RGBQUAD gray[256];
		for (int i = 0; i < 256; i++) gray[i].rgbRed = gray[i].rgbGreen = gray[i].rgbBlue = i;
		cimage.SetColorTable(0, 256, gray);
	}

	int pitch = cimage.GetPitch();
	uchar* pBits = (uchar*)cimage.GetBits();

	memcpy(pBits, currentFrame.data, currentFrame.rows * currentFrame.cols * currentFrame.channels());

	CDC* pDC = pPic->GetDC();
	cimage.Draw(pDC->GetSafeHdc(), 0, 0);
	ReleaseDC(pDC);
	cimage.Destroy();
}


void CTab1Dlg::OnDestroy()
{
	CDialog::OnDestroy();
	KillTimer(TIMER_UPDATE_CAMERA);
	m_bThreadRunning = false;
}

void CTab1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == TIMER_UPDATE_CAMERA)
	{
		for (int i = 0; i < 4; ++i)
		{
			DrawFrame(i);
		}
	}
	CDialog::OnTimer(nIDEvent);
}