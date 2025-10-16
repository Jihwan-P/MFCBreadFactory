// CTab1View.cpp: 구현 파일
//

#include "pch.h"
#include "MFCBreadFactory.h"
#include "afxdialogex.h"
#include "CTab1Dlg.h"

// CTab1Dlg 대화 상자

IMPLEMENT_DYNAMIC(CTab1Dlg, CDialog)

CTab1Dlg::CTab1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_TAB1_FORM, pParent)
{

}

CTab1Dlg::~CTab1Dlg()
{
}

void CTab1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTab1Dlg, CDialog)
END_MESSAGE_MAP()


// CTab1Dlg 메시지 처리기

BOOL CTab1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 폰트 설정
	// 1. 라벨에 적용할 폰트를 생성합니다. (12pt, Malgun Gothic)
	m_fontLabels.CreatePointFont(120, _T("Malgun Gothic"));

	// 2. 고유 ID를 이용해 각 라벨 컨트롤에 폰트를 적용합니다.
	GetDlgItem(IDC_STATIC_LABEL_CAM1)->SetFont(&m_fontLabels);
	GetDlgItem(IDC_STATIC_LABEL_CAM2)->SetFont(&m_fontLabels);
	GetDlgItem(IDC_STATIC_LABEL_CAM3)->SetFont(&m_fontLabels);
	GetDlgItem(IDC_STATIC_LABEL_CAM4)->SetFont(&m_fontLabels);
	GetDlgItem(IDC_STATIC_LABEL_GRAPH1)->SetFont(&m_fontLabels);
	GetDlgItem(IDC_STATIC_LABEL_GRAPH2)->SetFont(&m_fontLabels);
	GetDlgItem(IDC_STATIC_LABEL_GRAPH3)->SetFont(&m_fontLabels);

	// 카메라 설정
	// 각 카메라 ID와 URL을 지정하여 WebView 컨트롤 생성
	CreateWebViewCtrl(IDC_STATIC_CAM1, 0, _T("http://192.168.0.118:18081"));
	CreateWebViewCtrl(IDC_STATIC_CAM2, 1, _T("http://192.168.0.91:18081"));
	CreateWebViewCtrl(IDC_STATIC_CAM3, 2, _T("http://192.168.0.84:18081"));
	CreateWebViewCtrl(IDC_STATIC_CAM4, 3, _T("http://192.168.0.108:18081"));

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CTab1Dlg::CreateWebViewCtrl(int nID, int index, const CString& url)
{
	CStatic* pStatic = (CStatic*)GetDlgItem(nID);
	if (!pStatic)
	{
		CString msg;
		msg.Format(_T("ID %d 컨트롤을 찾을 수 없습니다."), nID);
		AfxMessageBox(msg);
		return;
	}

	CRect rect;
	pStatic->GetWindowRect(&rect);
	ScreenToClient(&rect);

	// WebView2 환경 생성
	CreateCoreWebView2EnvironmentWithOptions(nullptr, nullptr, nullptr,
		Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
			[this, rect, url, index](HRESULT result, ICoreWebView2Environment* env) -> HRESULT {
				if (FAILED(result)) return result;

				// WebView2 컨트롤러 생성
				env->CreateCoreWebView2Controller(m_hWnd, Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
					[this, rect, url, index](HRESULT result, ICoreWebView2Controller* controller) -> HRESULT {
						if (FAILED(result)) return result;

						m_controllers[index] = controller;
						m_controllers[index]->get_CoreWebView2(&m_webViews[index]);

						// WebView2 컨트롤 크기 및 위치 설정
						m_controllers[index]->put_Bounds(rect);

						// WebView2 설정 (예: 줌 기능 비활성화, 스크롤바 숨기기 등)
						ICoreWebView2Settings* settings;
						m_webViews[index]->get_Settings(&settings);
						settings->put_AreDefaultContextMenusEnabled(FALSE);
						settings->put_IsZoomControlEnabled(FALSE);

						// 지정된 URL로 이동
						m_webViews[index]->Navigate(url);

						return S_OK;
					}).Get());
				return S_OK;
			}).Get());
}