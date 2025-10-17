#pragma once
#include "afxdialogex.h"
#include "MainFrm.h"


// CTab4Dlg 대화 상자

class CTab4Dlg : public CDialog
{
	DECLARE_DYNAMIC(CTab4Dlg)

public:
	CTab4Dlg(int chamberIndex, CWnd* pParent = nullptr);   // 생성자에 인덱스 추가
	virtual ~CTab4Dlg();

	void UpdateCurrentData(const AgingChamberData& data);

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB4_DLG };
#endif

protected: 
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	int m_nChamberIndex; // 숙성고 인덱스
	void UpdateMainFrameData(); // 메인 프레임에 데이터 전송

public:
	afx_msg void OnEnChangeEditTempSet();
	afx_msg void OnEnChangeEditHumidSet();
	afx_msg void OnCbnSelchangeComboMethod();
};