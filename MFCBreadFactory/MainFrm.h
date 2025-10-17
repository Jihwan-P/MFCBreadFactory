
// MainFrm.h: CMainFrame 클래스의 인터페이스
//

#pragma once

#include "CStaticSplitterWnd.h"
#include <afxext.h> // CSplitterWnd 클래스를 사용하기 위해 필요합니다.

class CMainFrame : public CFrameWnd // SDI 구조
{
	
protected: // serialization에서만 만들어집니다.
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	// 주 프레임의 클라이언트 영역에 분할창을 만들기 위해 오버라이드합니다.
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

// 구현입니다.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// 생성된 메시지 맵 함수
protected:
	// 화면을 분할할 CSplitterWnd 객체를 멤버 변수로 선언합니다.
	CStaticSplitterWnd m_wndSplitter;

	// 상태 표시줄과 도구 모음 컨트롤 멤버 변수입니다.
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

};


