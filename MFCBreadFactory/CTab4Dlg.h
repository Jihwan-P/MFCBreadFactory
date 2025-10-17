#pragma once
#include "afxdialogex.h"
#include "MainFrm.h"

class CTab4Dlg : public CDialog
{
	DECLARE_DYNAMIC(CTab4Dlg)

public:
	CTab4Dlg(int chamberIndex = 0, CWnd* pParent = nullptr); // 생성자 수정
	virtual ~CTab4Dlg();

	void UpdateCurrentData(const AgingChamberData& data);

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB2_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	int m_nChamberIndex;
	void UpdateMainFrameData();

public:
	afx_msg void OnEnChangeEditTempSet();
	afx_msg void OnEnChangeEditHumidSet();
	afx_msg void OnCbnSelchangeComboMethod();
};