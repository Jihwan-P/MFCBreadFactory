#pragma once


// CStaticSplitterWnd

class CStaticSplitterWnd : public CSplitterWnd
{
	DECLARE_DYNAMIC(CStaticSplitterWnd)

public:
	CStaticSplitterWnd();
	virtual ~CStaticSplitterWnd();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};


