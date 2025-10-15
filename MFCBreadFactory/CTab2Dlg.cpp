// CTab1View.cpp: 구현 파일
//

#include "pch.h"
#include "MFCBreadFactory.h"
#include "CTab2Dlg.h"


// CTab1Dlg 대화 상자

IMPLEMENT_DYNAMIC(CTab2Dlg, CDialog)

CTab2Dlg::CTab2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_TAB1_FORM, pParent)
{

}

CTab2Dlg::~CTab2Dlg()
{
}

void CTab2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTab2Dlg, CDialog)
END_MESSAGE_MAP()


// CTab1Dlg 메시지 처리기