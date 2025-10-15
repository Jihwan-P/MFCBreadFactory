
// MFCBreadFactoryView.h: CMFCBreadFactoryView 클래스의 인터페이스
//

#pragma once

#include "MFCBreadFactoryDoc.h"
#include "CTab1Dlg.h"
#include "CTab2Dlg.h"
#include "CTab3Dlg.h"
#include "CTab4Dlg.h"

class CMFCBreadFactoryView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CMFCBreadFactoryView() noexcept;
	DECLARE_DYNCREATE(CMFCBreadFactoryView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MFCBREADFACTORY_FORM };
#endif

// 특성입니다.
public:
	CMFCBreadFactoryDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CMFCBreadFactoryView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CTab1Dlg* m_pTab1Dlg;
	CTab2Dlg* m_pTab2Dlg;
	CTab3Dlg* m_pTab3Dlg;
	CTab4Dlg* m_pTab4Dlg;

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
protected:
	CTabCtrl m_Tab;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // MFCBreadFactoryView.cpp의 디버그 버전
inline CMFCBreadFactoryDoc* CMFCBreadFactoryView::GetDocument() const
   { return reinterpret_cast<CMFCBreadFactoryDoc*>(m_pDocument); }
#endif

