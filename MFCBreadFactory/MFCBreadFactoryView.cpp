
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
	m_pTab1View = nullptr;
	m_pTab2View = nullptr;

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
	m_Tab.InsertItem(0, _T("첫 번째 탭"));
	m_Tab.InsertItem(1, _T("두 번째 탭"));

	// CCreateContext를 사용하여 뷰 생성
	CCreateContext context;
	context.m_pNewViewClass = RUNTIME_CLASS(CTab1View);
	context.m_pCurrentDoc = GetDocument();
	m_pTab1View = (CTab1View*)((CFrameWnd*)GetParent())->CreateView(&context, AFX_IDW_PANE_FIRST);
	m_pTab1View->OnInitialUpdate();

	context.m_pNewViewClass = RUNTIME_CLASS(CTab2View);
	context.m_pCurrentDoc = GetDocument();
	m_pTab2View = (CTab2View*)((CFrameWnd*)GetParent())->CreateView(&context, AFX_IDW_PANE_FIRST + 1);
	m_pTab2View->OnInitialUpdate();

	// 초기 탭 페이지 보이기/숨기기
	m_pTab1View->ShowWindow(SW_SHOW);
	m_pTab2View->ShowWindow(SW_HIDE);
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
		m_pTab1View->ShowWindow(SW_SHOW);
		m_pTab2View->ShowWindow(SW_HIDE);
		break;
	case 1:
		m_pTab1View->ShowWindow(SW_HIDE);
		m_pTab2View->ShowWindow(SW_SHOW);
		break;
	}
	*pResult = 0;
}

void CMFCBreadFactoryView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// 탭 컨트롤과 뷰들이 생성되었는지 확인
	if (m_Tab.GetSafeHwnd() && m_pTab1View && m_pTab2View)
	{
		// 1. 탭 컨트롤의 크기를 부모 뷰의 클라이언트 영역에 맞게 조절
		m_Tab.MoveWindow(0, 0, cx, cy);

		// 2. 탭 페이지(뷰)가 표시될 영역 계산
		CRect rect;
		m_Tab.GetClientRect(&rect);
		rect.top += 22;
		rect.left += 2;
		rect.right -= 4;
		rect.bottom -= 4;

		// 3. 두 개의 탭 뷰의 크기를 계산된 영역에 맞게 조절
		m_pTab1View->MoveWindow(&rect);
		m_pTab2View->MoveWindow(&rect);
	}
}
