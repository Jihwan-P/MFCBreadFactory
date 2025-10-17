
// MFCBreadFactoryView.cpp: CMFCBreadFactoryView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCBreadFactory.h"
#endif

#include "MFCBreadFactoryDoc.h"
#include "MFCBreadFactoryView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCBreadFactoryView

IMPLEMENT_DYNCREATE(CMFCBreadFactoryView, CFormView)

BEGIN_MESSAGE_MAP(CMFCBreadFactoryView, CFormView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMFCBreadFactoryView::OnTcnSelchangeTab)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CMFCBreadFactoryView 생성/소멸

CMFCBreadFactoryView::CMFCBreadFactoryView() noexcept
	: CFormView(IDD_MFCBREADFACTORY_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_pTab1Dlg = nullptr;
	m_pTab2Dlg = nullptr;
	m_pTab3Dlg = nullptr;
	m_pTab4Dlg = nullptr;

}

CMFCBreadFactoryView::~CMFCBreadFactoryView()
{
}

void CMFCBreadFactoryView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}

BOOL CMFCBreadFactoryView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	// 뷰의 3D 테두리(클라이언트 가장자리) 스타일을 제거합니다.
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

	return CFormView::PreCreateWindow(cs);
}

void CMFCBreadFactoryView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// 탭 컨트롤 초기화
	m_Tab.InsertItem(0, _T("요약"));
	m_Tab.InsertItem(1, _T("숙성실1"));
	m_Tab.InsertItem(2, _T("숙성실2"));
	m_Tab.InsertItem(3, _T("숙성실3"));

	// 탭으로 보여줄 다이얼로그 객체를 생성합니다.
	m_pTab1Dlg = new CTab1Dlg;
	m_pTab1Dlg->Create(IDD_TAB1_DLG, &m_Tab);

	m_pTab2Dlg = new CTab2Dlg;
	m_pTab2Dlg->Create(IDD_TAB2_DLG, &m_Tab);

	m_pTab3Dlg = new CTab3Dlg;
	m_pTab3Dlg->Create(IDD_TAB3_DLG, &m_Tab);

	m_pTab4Dlg = new CTab4Dlg;
	m_pTab4Dlg->Create(IDD_TAB4_DLG, &m_Tab);

	// 첫 번째 탭을 초기에 보여줍니다.
	m_pTab1Dlg->ShowWindow(SW_SHOW);
	m_pTab2Dlg->ShowWindow(SW_HIDE);
	m_pTab3Dlg->ShowWindow(SW_HIDE);
	m_pTab4Dlg->ShowWindow(SW_HIDE);

	// 프로그램 시작 시 뷰의 크기를 올바르게 설정하기 위해 OnSize 함수를 수동으로 한번 호출합니다.
	CRect rect;
	GetClientRect(&rect);
	OnSize(SIZE_RESTORED, rect.Width(), rect.Height());
}


// CMFCBreadFactoryView 진단

#ifdef _DEBUG
void CMFCBreadFactoryView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMFCBreadFactoryView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMFCBreadFactoryDoc* CMFCBreadFactoryView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCBreadFactoryDoc)));
	return (CMFCBreadFactoryDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCBreadFactoryView 메시지 처리기


void CMFCBreadFactoryView::OnTcnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nSel = m_Tab.GetCurSel();
	switch (nSel)
	{
	case 0:
		m_pTab1Dlg->ShowWindow(SW_SHOW);
		m_pTab2Dlg->ShowWindow(SW_HIDE);
		m_pTab3Dlg->ShowWindow(SW_HIDE);
		m_pTab4Dlg->ShowWindow(SW_HIDE);
		break;
	case 1:
		m_pTab1Dlg->ShowWindow(SW_HIDE);
		m_pTab2Dlg->ShowWindow(SW_SHOW);
		m_pTab3Dlg->ShowWindow(SW_HIDE);
		m_pTab4Dlg->ShowWindow(SW_HIDE);
		break;
	case 2:
		m_pTab1Dlg->ShowWindow(SW_HIDE);
		m_pTab2Dlg->ShowWindow(SW_HIDE);
		m_pTab3Dlg->ShowWindow(SW_SHOW);
		m_pTab4Dlg->ShowWindow(SW_HIDE);
		break;
	case 3:
		m_pTab1Dlg->ShowWindow(SW_HIDE);
		m_pTab2Dlg->ShowWindow(SW_HIDE);
		m_pTab3Dlg->ShowWindow(SW_HIDE);
		m_pTab4Dlg->ShowWindow(SW_SHOW);
		break;
	}
	*pResult = 0;
}

void CMFCBreadFactoryView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// 탭 컨트롤과 다이얼로그들이 유효한지 확인합니다.
	if (m_Tab.GetSafeHwnd() && m_pTab1Dlg->GetSafeHwnd() && m_pTab2Dlg->GetSafeHwnd())
	{
		// 1. 탭 컨트롤의 크기를 부모 뷰(CMFCBreadFactoryView)를 꽉 채우도록 조절합니다.
		m_Tab.MoveWindow(0, 0, cx, cy);

		// 2. 탭 페이지(다이얼로그)가 표시될 영역을 계산합니다.
		CRect rect;
		m_Tab.GetClientRect(&rect);
		rect.top += 22;    // 탭 버튼의 높이만큼 아래로 내립니다.
		rect.left += 2;    // 좌우 여백을 줍니다.
		rect.right -= 4;
		rect.bottom -= 4;

		// 3. 두 개의 탭 다이얼로그의 크기와 위치를 계산된 영역에 맞게 조절합니다.
		m_pTab1Dlg->MoveWindow(&rect);
		m_pTab2Dlg->MoveWindow(&rect);
		m_pTab3Dlg->MoveWindow(&rect);
		m_pTab4Dlg->MoveWindow(&rect);
	}
}
