#pragma once
#include "afxdialogex.h"


// CTab4Dlg 대화 상자

class CTab4Dlg : public CDialog
{
	DECLARE_DYNAMIC(CTab4Dlg)

public:
	CTab4Dlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTab4Dlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB4_FORM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
