#pragma once
#include "afxdialogex.h"
#include "CChartCtrl.h"
#include <vector>


// CTab1View 폼 보기

class CTab2Dlg : public CDialog
{
	DECLARE_DYNAMIC(CTab2Dlg)

public:
	CTab2Dlg(CWnd* pParent = nullptr);
	virtual ~CTab2Dlg();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB2_FORM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButtonApply();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	// 설정 정보를 반환하는 함수 선언
	void GetSettings(CString& method, CString& temp, CString& humidity);


private:
	CChartCtrl m_chart; // 차트 컨트롤 멤버 변수

	// 데이터
	std::vector<float> m_tempData;
	std::vector<float> m_humidityData;

	// 설정값
	float m_minTemp, m_maxTemp;
	float m_minHumidity, m_maxHumidity;
	int m_method;

	// UI 컨트롤 변수
	CStatic m_stcCurrentTemp;
	CStatic m_stcCurrentHumidity;
	CEdit m_editMinTemp;
	CEdit m_editMaxTemp;
	CEdit m_editMinHumidity;
	CEdit m_editMaxHumidity;
	CComboBox m_comboMethod;

	void UpdateData(bool bInit = false); // 데이터를 업데이트하고 알림을 확인하는 함수
};