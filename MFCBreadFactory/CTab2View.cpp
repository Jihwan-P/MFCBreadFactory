// CTab2View.cpp: 구현 파일
//

#include "pch.h"
#include "MFCBreadFactory.h"
#include "CTab2View.h"


// CTab2View

IMPLEMENT_DYNCREATE(CTab2View, CFormView)

CTab2View::CTab2View()
	: CFormView(IDD_TAB2_FORM)
{

}

CTab2View::~CTab2View()
{
}

void CTab2View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTab2View, CFormView)
END_MESSAGE_MAP()


// CTab2View 진단

#ifdef _DEBUG
void CTab2View::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTab2View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTab2View 메시지 처리기
