// CTab4Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCBreadFactory.h"
#include "afxdialogex.h"
#include "CTab4Dlg.h"


// CTab4Dlg 대화 상자

IMPLEMENT_DYNAMIC(CTab4Dlg, CDialog)

CTab4Dlg::CTab4Dlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_TAB4_FORM, pParent)
{

}

CTab4Dlg::~CTab4Dlg()
{
}

void CTab4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTab4Dlg, CDialog)
END_MESSAGE_MAP()


// CTab4Dlg 메시지 처리기
