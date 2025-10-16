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
    // 숙성고 1 정보 컨트롤
    CStatic m_stcRoom1Method;
    CStatic m_stcRoom1Temp;
    CStatic m_stcRoom1Humidity;

    // 숙성고 2 정보 컨트롤
    CStatic m_stcRoom2Method;
    CStatic m_stcRoom2Temp;
    CStatic m_stcRoom2Humidity;

    // 숙성고 3 정보 컨트롤
    CStatic m_stcRoom3Method;
    CStatic m_stcRoom3Temp;
    CStatic m_stcRoom3Humidity;
};