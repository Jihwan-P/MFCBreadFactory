#pragma once


// ChildFrm 프레임

class ChildFrm : public CMDIChildWnd
{
	DECLARE_DYNCREATE(ChildFrm)
protected:
	ChildFrm();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~ChildFrm();

protected:
	DECLARE_MESSAGE_MAP()
};


