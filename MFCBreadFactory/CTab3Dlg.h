#pragma once
#include "afxdialogex.h"
#include "CChartCtrl.h"
#include <vector>

class CTab3Dlg : public CDialog
{
	DECLARE_DYNAMIC(CTab3Dlg)

public:
	CTab3Dlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTab3Dlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB3_FORM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButtonApply();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	void GetSettings(CString& method, CString& temp, CString& humidity);

private:
	CChartCtrl m_chart;
	std::vector<float> m_tempData;
	std::vector<float> m_humidityData;
	float m_minTemp, m_maxTemp;
	float m_minHumidity, m_maxHumidity;
	int m_method;
	CStatic m_stcCurrentTemp;
	CStatic m_stcCurrentHumidity;
	CEdit m_editMinTemp;
	CEdit m_editMaxTemp;
	CEdit m_editMinHumidity;
	CEdit m_editMaxHumidity;
	CComboBox m_comboMethod;
	void UpdateData(bool bInit = false);
};