#pragma once



// CChatView 폼 보기

class CChatView : public CFormView
{
	DECLARE_DYNCREATE(CChatView)

protected:
	CChatView();		// 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CChatView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHAT_FORM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs); // 창 생성 전 속성 수정을 위해 선언

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 뷰 초기화 로직 구현을 위해 선언 (CChatView.cpp에서 정의)

	DECLARE_MESSAGE_MAP()

public:
	// 채팅 UI 컨트롤 멤버 변수
	CStatic m_staticTimeDisplay;
	CListBox m_listChat;
	CEdit m_editChat;
	CButton m_btnSend;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnSend();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
};