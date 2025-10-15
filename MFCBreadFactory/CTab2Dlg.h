#pragma once



// CTab1View 폼 보기

class CTab2Dlg : public CDialog
{
	DECLARE_DYNAMIC(CTab2Dlg)

public:
	CTab2Dlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTab2Dlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB2_FORM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
