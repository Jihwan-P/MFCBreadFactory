#pragma once
#include "afxdialogex.h"


// CTab1View 폼 보기

class CTab1Dlg : public CDialog
{
	DECLARE_DYNAMIC(CTab1Dlg)

public:
	CTab1Dlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTab1Dlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB1_FORM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	// 4개의 WebView2 컨트롤러와 뷰에 대한 ComPtr 멤버 변수 선언
	Microsoft::WRL::ComPtr<ICoreWebView2Controller> m_controllers[4];
	Microsoft::WRL::ComPtr<ICoreWebView2> m_webViews[4];

	CFont m_fontLabels;

	// WebView 컨트롤을 생성하고 초기화하는 헬퍼 함수
	void CreateWebViewCtrl(int nID, int index, const CString& url);
};
