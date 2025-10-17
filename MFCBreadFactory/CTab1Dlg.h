#pragma once
#include "CChartCtrl.h"
#include "afxdialogex.h"
#include "MainFrm.h"


// CTab1View 폼 보기

class CTab1Dlg : public CDialog
{
	DECLARE_DYNAMIC(CTab1Dlg)

public:
	CTab1Dlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CTab1Dlg();

	// 데이터 업데이트 함수
	void UpdateData(const AgingChamberData* chamberData);

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB1_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	CChartCtrl m_chartCtrl; // 차트 컨트롤 멤버
};