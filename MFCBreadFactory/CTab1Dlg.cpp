// CTab1View.cpp: 구현 파일
//

#include "pch.h"
#include "MFCBreadFactory.h"
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