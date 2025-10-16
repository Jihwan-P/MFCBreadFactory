#pragma once
#include "afxdialogex.h"


// CTab3Dlg 대화 상자

class CTab3Dlg : public CDialog
{
	DECLARE_DYNAMIC(CTab3Dlg)

public:
	CTab3Dlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTab3Dlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB3_FORM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

};
