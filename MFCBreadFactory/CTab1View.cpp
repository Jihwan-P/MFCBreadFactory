// CTab1View.cpp: 구현 파일
//

#include "pch.h"
#include "MFCBreadFactory.h"
#include "CTab1View.h"


// CTab1View

IMPLEMENT_DYNCREATE(CTab1View, CFormView)

CTab1View::CTab1View()
	: CFormView(IDD_TAB1_FORM)
{

}

CTab1View::~CTab1View()
{
}

void CTab1View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTab1View, CFormView)
END_MESSAGE_MAP()


// CTab1View 진단

#ifdef _DEBUG
void CTab1View::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTab1View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTab1View 메시지 처리기
