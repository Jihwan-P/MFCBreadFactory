
// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "MFCBreadFactory.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 타이머 ID 및 간격(ms)
#define DATA_UPDATE_TIMER_ID 1
#define DATA_UPDATE_INTERVAL 2000 // 2초

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_NOTIFY(TCN_SELCHANGE, AFX_IDC_TAB_CONTROL, &CMainFrame::OnSelchangeTabs)
	ON_WM_TIMER() // 타이머 메시지 맵 추가
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

CMainFrame::CMainFrame() noexcept : m_pTab1Dlg(nullptr), m_pTab2Dlg(nullptr), m_pTab3Dlg(nullptr), m_pTab4Dlg(nullptr), m_pActiveTab(nullptr)
{
}

CMainFrame::~CMainFrame()
{
	// 동적 할당된 다이얼로그 해제
	if (m_pTab1Dlg) delete m_pTab1Dlg;
	if (m_pTab2Dlg) delete m_pTab2Dlg;
	if (m_pTab3Dlg) delete m_pTab3Dlg;
	if (m_pTab4Dlg) delete m_pTab4Dlg;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	// 탭 컨트롤 생성
	CRect rect;
	GetClientRect(&rect);
	m_wndTabs.Create(TCS_TABS | WS_CHILD | WS_VISIBLE, rect, this, AFX_IDC_TAB_CONTROL);
	m_wndTabs.InsertItem(0, _T("요약"));
	m_wndTabs.InsertItem(1, _T("숙성고 1"));
	m_wndTabs.InsertItem(2, _T("숙성고 2"));
	m_wndTabs.InsertItem(3, _T("숙성고 3"));

	// 탭 다이얼로그 생성
	m_pTab1Dlg = new CTab1Dlg();
	m_pTab1Dlg->Create(IDD_TAB1_DLG, &m_wndTabs);
	m_pTab2Dlg = new CTab2Dlg(0); // 숙성고 인덱스 0
	m_pTab2Dlg->Create(IDD_TAB2_DLG, &m_wndTabs);
	m_pTab3Dlg = new CTab3Dlg(1); // 숙성고 인덱스 1
	m_pTab3Dlg->Create(IDD_TAB3_DLG, &m_wndTabs);
	m_pTab4Dlg = new CTab4Dlg(2); // 숙성고 인덱스 2
	m_pTab4Dlg->Create(IDD_TAB4_DLG, &m_wndTabs);

	// 초기 탭 설정
	m_pActiveTab = m_pTab1Dlg;
	m_pTab1Dlg->ShowWindow(SW_SHOW);

	OnSelchangeTabs(NULL, NULL); // 탭 위치 조정

	// 타이머 설정
	SetTimer(DATA_UPDATE_TIMER_ID, DATA_UPDATE_INTERVAL, NULL);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

void CMainFrame::OnSelchangeTabs(NMHDR* pNMHDR, LRESULT* pResult)
{
	if (m_pActiveTab != NULL)
		m_pActiveTab->ShowWindow(SW_HIDE);

	int nIndex = m_wndTabs.GetCurSel();
	switch (nIndex)
	{
	case 0:
		m_pActiveTab = m_pTab1Dlg;
		break;
	case 1:
		m_pActiveTab = m_pTab2Dlg;
		break;
	case 2:
		m_pActiveTab = m_pTab3Dlg;
		break;
	case 3:
		m_pActiveTab = m_pTab4Dlg;
		break;
	}

	if (m_pActiveTab)
	{
		CRect rect;
		m_wndTabs.GetClientRect(rect);
		rect.top += 22; // 탭 높이만큼 내림
		m_pActiveTab->MoveWindow(&rect);
		m_pActiveTab->ShowWindow(SW_SHOW);
	}

	if (pResult)
		*pResult = 0;
}

// 데이터 업데이트 함수
void CMainFrame::UpdateChamberData(int chamberIndex, const AgingChamberData& data)
{
	if (chamberIndex >= 0 && chamberIndex < 3)
	{
		m_ChamberData[chamberIndex] = data;
	}
}

AgingChamberData CMainFrame::GetChamberData(int chamberIndex)
{
	if (chamberIndex >= 0 && chamberIndex < 3)
	{
		return m_ChamberData[chamberIndex];
	}
	return AgingChamberData();
}

// 타이머 핸들러
void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == DATA_UPDATE_TIMER_ID)
	{
		// 임시로 현재 온습도 데이터 시뮬레이션
		for (int i = 0; i < 3; ++i)
		{
			// 설정값 주변에서 랜덤하게 변동
			m_ChamberData[i].currentTemp = m_ChamberData[i].setTemp + (rand() % 21 - 10) / 10.0; // ±1.0
			m_ChamberData[i].currentHumid = m_ChamberData[i].setHumid + (rand() % 41 - 20) / 10.0; // ±2.0
		}

		// 각 탭 다이얼로그에 데이터 업데이트 요청
		m_pTab1Dlg->UpdateData(m_ChamberData);
		m_pTab2Dlg->UpdateCurrentData(m_ChamberData[0]);
		m_pTab3Dlg->UpdateCurrentData(m_ChamberData[1]);
		m_pTab4Dlg->UpdateCurrentData(m_ChamberData[2]);
	}

	CFrameWnd::OnTimer(nIDEvent);
}