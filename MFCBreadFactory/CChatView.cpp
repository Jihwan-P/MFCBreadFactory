// CChatView.cpp: 구현 파일
//

#include "pch.h"
#include "MFCBreadFactory.h"
#include "CChatView.h"


// CChatView

IMPLEMENT_DYNCREATE(CChatView, CFormView)

CChatView::CChatView()
	: CFormView(IDD_CHAT_FORM)
{

}

CChatView::~CChatView()
{
}

void CChatView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CChatView, CFormView)
END_MESSAGE_MAP()


// CChatView 진단

#ifdef _DEBUG
void CChatView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CChatView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CChatView 메시지 처리기
