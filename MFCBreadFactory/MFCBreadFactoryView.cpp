
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
END_MESSAGE_MAP()

// CMFCBreadFactoryView 생성/소멸

CMFCBreadFactoryView::CMFCBreadFactoryView() noexcept
	: CFormView(IDD_MFCBREADFACTORY_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFCBreadFactoryView::~CMFCBreadFactoryView()
{
}

void CMFCBreadFactoryView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CMFCBreadFactoryView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CMFCBreadFactoryView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	// 자동 크기 조정을 비활성화해야 원하는 창 크기를 얻을 수 있습니다.
	//ResizeParentToFit();

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
