#pragma once
#include "afxdialogex.h"
#include "CChartCtrl.h" // CChartCtrl 헤더 추가
#include "MainFrm.h"    // AgingChamberData 사용을 위해

class CTab1Dlg : public CDialog
{
	DECLARE_DYNAMIC(CTab1Dlg)

public:
	CTab1Dlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CTab1Dlg();

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
	CChartCtrl m_chartCtrl; // 멤버 변수 이름을 IDC_CHART_CTRL에 맞게 수정
};