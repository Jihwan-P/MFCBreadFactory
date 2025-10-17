
// MainFrm.h: CMainFrame 클래스의 인터페이스
//

#pragma once
#include "CStaticSplitterWnd.h"
#include <afxext.h> // CSplitterWnd 클래스를 사용하기 위해 필요합니다.
#include "CTab1Dlg.h"
#include "CTab2Dlg.h"
#include "CTab3Dlg.h"
#include "CTab4Dlg.h"

// 숙성고 데이터 구조체
struct AgingChamberData
{
	CString methodName;
	double setTemp = 25.0;
	double currentTemp = 0.0;
	double setHumid = 60.0;
	double currentHumid = 0.0;
};

class CMainFrame : public CFrameWnd
{

protected: // create from serialization only
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

	// Attributes
public:

	// Operations
public:
	// 탭 다이얼로그 업데이트 함수
	void UpdateChamberData(int chamberIndex, const AgingChamberData& data);
	AgingChamberData GetChamberData(int chamberIndex);

	// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

	CTabCtrl m_wndTabs;
	CTab1Dlg* m_pTab1Dlg;
	CTab2Dlg* m_pTab2Dlg;
	CTab3Dlg* m_pTab3Dlg;
	CTab4Dlg* m_pTab4Dlg;
	CDialog* m_pActiveTab;

	// 숙성고 데이터 배열
	AgingChamberData m_ChamberData[3];

	// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSelchangeTabs(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent); // 타이머 핸들러
	DECLARE_MESSAGE_MAP()
};