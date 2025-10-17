#pragma once
#include "afxdialogex.h"


// CTab1View 폼 보기

class CTab1Dlg : public CDialog
{
	DECLARE_DYNAMIC(CTab1Dlg)

public:
	CTab1Dlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CTab1Dlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB1_FORM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()

public:
    void UpdateSummary(); // 요약 정보 갱신 함수
    afx_msg void OnTimer(UINT_PTR nIDEvent);

private:
    // 숙성고 1 정보 컨트롤 및 차트
    CChartCtrl m_chart1; // IDC_STATIC_CHART1
    CStatic m_stcRoom1Method;       // 숙성 종류
    CStatic m_stcRoom1CurrentTemp;  // 현재 온도 (추가)
    CStatic m_stcRoom1MaxMinTemp;   // 적정 온도 (기존 m_stcRoom1Temp 이름 변경)
    CStatic m_stcRoom1CurrentHumidity; // 현재 습도 (추가)
    CStatic m_stcRoom1MaxMinHumidity;  // 적정 습도 (기존 m_stcRoom1Humidity 이름 변경)

    // 숙성고 2 정보 컨트롤 및 차트
    CChartCtrl m_chart2; // IDC_STATIC_CHART2
    CStatic m_stcRoom2Method;
    CStatic m_stcRoom2CurrentTemp;
    CStatic m_stcRoom2MaxMinTemp;
    CStatic m_stcRoom2CurrentHumidity;
    CStatic m_stcRoom2MaxMinHumidity;

    // 숙성고 3 정보 컨트롤 및 차트
    CChartCtrl m_chart3; // IDC_STATIC_CHART3
    CStatic m_stcRoom3Method;
    CStatic m_stcRoom3CurrentTemp;
    CStatic m_stcRoom3MaxMinTemp;
    CStatic m_stcRoom3CurrentHumidity;
    CStatic m_stcRoom3MaxMinHumidity;
};