#include "pch.h"
#include "MFCBreadFactory.h"
#include "CTab1Dlg.h"
#include "afxdialogex.h"
#include <gdiplus.h> // GDI+ 사용을 위해 추가
#pragma comment(lib, "gdiplus.lib")

IMPLEMENT_DYNAMIC(CTab1Dlg, CDialog)

CTab1Dlg::CTab1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_TAB1_DLG, pParent)
{
	// GDI+ 초기화
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

CTab1Dlg::~CTab1Dlg()
{
}

void CTab1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHART_CTRL, m_chartCtrl);
}

BEGIN_MESSAGE_MAP(CTab1Dlg, CDialog)
END_MESSAGE_MAP()


BOOL CTab1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 차트 초기 데이터 및 범위 설정 (예시)
	std::vector<float> tempData(24, 25.0f); // 24시간 동안 25도로 가정
	std::vector<float> humidData(24, 60.0f); // 24시간 동안 60%로 가정
	m_chartCtrl.SetData(tempData, humidData);
	m_chartCtrl.SetRanges(20, 30, 50, 70); // 적정 온습도 범위 설정

	return TRUE;
}

void CTab1Dlg::UpdateData(const AgingChamberData* chamberData)
{
	if (!GetSafeHwnd()) return;

	CString str;

	// 숙성고 1
	str.Format(_T("%.1f °C"), chamberData[0].setTemp);
	SetDlgItemText(IDC_STATIC_TEMP_SET_1, str);
	str.Format(_T("%.1f °C"), chamberData[0].currentTemp);
	SetDlgItemText(IDC_STATIC_TEMP_CUR_1, str);
	str.Format(_T("%.1f %%"), chamberData[0].setHumid);
	SetDlgItemText(IDC_STATIC_HUMID_SET_1, str);
	str.Format(_T("%.1f %%"), chamberData[0].currentHumid);
	SetDlgItemText(IDC_STATIC_HUMID_CUR_1, str);

	// 숙성고 2
	str.Format(_T("%.1f °C"), chamberData[1].setTemp);
	SetDlgItemText(IDC_STATIC_TEMP_SET_2, str);
	str.Format(_T("%.1f °C"), chamberData[1].currentTemp);
	SetDlgItemText(IDC_STATIC_TEMP_CUR_2, str);
	str.Format(_T("%.1f %%"), chamberData[1].setHumid);
	SetDlgItemText(IDC_STATIC_HUMID_SET_2, str);
	str.Format(_T("%.1f %%"), chamberData[1].currentHumid);
	SetDlgItemText(IDC_STATIC_HUMID_CUR_2, str);

	// 숙성고 3
	str.Format(_T("%.1f °C"), chamberData[2].setTemp);
	SetDlgItemText(IDC_STATIC_TEMP_SET_3, str);
	str.Format(_T("%.1f °C"), chamberData[2].currentTemp);
	SetDlgItemText(IDC_STATIC_TEMP_CUR_3, str);
	str.Format(_T("%.1f %%"), chamberData[2].setHumid);
	SetDlgItemText(IDC_STATIC_HUMID_SET_3, str);
	str.Format(_T("%.1f %%"), chamberData[2].currentHumid);
	SetDlgItemText(IDC_STATIC_HUMID_CUR_3, str);

	// 차트 데이터 업데이트 (예: 현재 시간의 평균값으로 데이터 업데이트)
	CTime time = CTime::GetCurrentTime();
	int hour = time.GetHour();

	float avgTemp = (chamberData[0].currentTemp + chamberData[1].currentTemp + chamberData[2].currentTemp) / 3.0f;
	float avgHumid = (chamberData[0].currentHumid + chamberData[1].currentHumid + chamberData[2].currentHumid) / 3.0f;

	// CChartCtrl의 데이터 업데이트 방식에 맞게 수정 필요
	// 현재 CChartCtrl은 24시간 전체 데이터를 한 번에 받으므로,
	// 실시간으로 데이터를 추가하는 기능을 CChartCtrl에 구현하거나
	// 아래와 같이 전체 데이터를 매번 새로 생성하여 전달해야 합니다.
	std::vector<float> tempData(24);
	std::vector<float> humidData(24);
	// ... (기존 데이터 유지 로직) ...
	tempData[hour] = avgTemp;
	humidData[hour] = avgHumid;
	m_chartCtrl.SetData(tempData, humidData);
}