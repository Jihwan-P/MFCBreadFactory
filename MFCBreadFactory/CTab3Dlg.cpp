// CTab3Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCBreadFactory.h"
#include "afxdialogex.h"
#include "CTab3Dlg.h"


// CTab3Dlg 대화 상자

IMPLEMENT_DYNAMIC(CTab3Dlg, CDialog)

CTab3Dlg::CTab3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_TAB3_FORM, pParent)
{

}

CTab3Dlg::~CTab3Dlg()
{
}

void CTab3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTab3Dlg, CDialog)
END_MESSAGE_MAP()


// CTab3Dlg 메시지 처리기
