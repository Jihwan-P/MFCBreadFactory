// CStaticSplitterWnd.cpp: 구현 파일
//

#include "pch.h"
#include "MFCBreadFactory.h"
#include "CStaticSplitterWnd.h"


// CStaticSplitterWnd

IMPLEMENT_DYNAMIC(CStaticSplitterWnd, CSplitterWnd)

CStaticSplitterWnd::CStaticSplitterWnd()
{

}

CStaticSplitterWnd::~CStaticSplitterWnd()
{
}


BEGIN_MESSAGE_MAP(CStaticSplitterWnd, CSplitterWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()



// CStaticSplitterWnd 메시지 처리기

void CStaticSplitterWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 기본 클래스의 함수를 호출하지 않아 크기 조절 시작을 막습니다.
}

void CStaticSplitterWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	// 기본 클래스의 함수를 호출하지 않아 크기 조절 종료를 막습니다.
}

void CStaticSplitterWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	// 기본 클래스의 함수를 호출하지 않아 크기 조절 중 바(bar) 이동을 막습니다.
}

BOOL CStaticSplitterWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TRUE를 반환하여 커서 변경을 막고, 기본 핸들러 호출을 방지합니다.
	return TRUE;
}
