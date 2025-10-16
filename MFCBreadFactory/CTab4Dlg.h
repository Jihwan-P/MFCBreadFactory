#pragma once
#include "afxdialogex.h"
#include "CChartCtrl.h"
#include <vector>

// CTab4Dlg 대화 상자

class CTab4Dlg : public CDialog
{
	DECLARE_DYNAMIC(CTab4Dlg)

public:
	CTab4Dlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTab4Dlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB4_FORM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void GetSettings(CString& method, CString& temp, CString& humidity);

private:
	std::vector<float> m_tempData;
	std::vector<float> m_humidityData;
	float m_minTemp, m_maxTemp;
	float m_minHumidity, m_maxHumidity;
	int m_method;
	void UpdateData(bool bInit = false);
};