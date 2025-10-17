// CTab1View.cpp: 구현 파일
//

#include "pch.h"
#include "MFCBreadFactory.h"
#include "afxdialogex.h"
#include "CTab1Dlg.h"


// CTab1Dlg 대화 상자

IMPLEMENT_DYNAMIC(CTab1Dlg, CDialog)

CTab1Dlg::CTab1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_TAB1_DLG, pParent)
{
}

CTab1Dlg::~CTab1Dlg()
{
}

void CTab1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHART_CTRL, m_chartCtrl); // 차트 컨트롤 연결
}

BEGIN_MESSAGE_MAP(CTab1Dlg, CDialog)
END_MESSAGE_MAP()

BOOL CTab1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 차트 컨트롤 초기화
	m_chartCtrl.GetTitle()->Add(_T("시간대별 온습도 변화"));
	m_chartCtrl.GetLegend()->SetVisible(true);

	// X축, Y축 설정
	m_chartCtrl.GetBottomAxis()->GetTitle()->Add(_T("시간"));
	m_chartCtrl.GetLeftAxis()->GetTitle()->Add(_T("온도 (°C) / 습도 (%)"));
	m_chartCtrl.GetLeftAxis()->SetMinMax(0, 100);

	// 시리즈 추가
	CChartLineSerie* pTempSerie = m_chartCtrl.CreateLineSerie();
	pTempSerie->SetColor(RGB(255, 0, 0));
	pTempSerie->SetName(_T("평균 온도"));

	CChartLineSerie* pHumidSerie = m_chartCtrl.CreateLineSerie();
	pHumidSerie->SetColor(RGB(0, 0, 255));
	pHumidSerie->SetName(_T("평균 습도"));

	return TRUE;
}

// 메인 프레임으로부터 데이터를 받아 UI 업데이트
void CTab1Dlg::UpdateData(const AgingChamberData* chamberData)
{
	if (!GetSafeHwnd()) return;

	CString str;
	double totalTemp = 0.0, totalHumid = 0.0;

	// 숙성고 1
	str.Format(_T("%.1f °C"), chamberData[0].setTemp);
	SetDlgItemText(IDC_STATIC_TEMP_SET_1, str);
	str.Format(_T("%.1f °C"), chamberData[0].currentTemp);
	SetDlgItemText(IDC_STATIC_TEMP_CUR_1, str);
	str.Format(_T("%.1f %%"), chamberData[0].setHumid);
	SetDlgItemText(IDC_STATIC_HUMID_SET_1, str);
	str.Format(_T("%.1f %%"), chamberData[0].currentHumid);
	SetDlgItemText(IDC_STATIC_HUMID_CUR_1, str);
	totalTemp += chamberData[0].currentTemp;
	totalHumid += chamberData[0].currentHumid;

	// 숙성고 2
	str.Format(_T("%.1f °C"), chamberData[1].setTemp);
	SetDlgItemText(IDC_STATIC_TEMP_SET_2, str);
	str.Format(_T("%.1f °C"), chamberData[1].currentTemp);
	SetDlgItemText(IDC_STATIC_TEMP_CUR_2, str);
	str.Format(_T("%.1f %%"), chamberData[1].setHumid);
	SetDlgItemText(IDC_STATIC_HUMID_SET_2, str);
	str.Format(_T("%.1f %%"), chamberData[1].currentHumid);
	SetDlgItemText(IDC_STATIC_HUMID_CUR_2, str);
	totalTemp += chamberData[1].currentTemp;
	totalHumid += chamberData[1].currentHumid;

	// 숙성고 3
	str.Format(_T("%.1f °C"), chamberData[2].setTemp);
	SetDlgItemText(IDC_STATIC_TEMP_SET_3, str);
	str.Format(_T("%.1f °C"), chamberData[2].currentTemp);
	SetDlgItemText(IDC_STATIC_TEMP_CUR_3, str);
	str.Format(_T("%.1f %%"), chamberData[2].setHumid);
	SetDlgItemText(IDC_STATIC_HUMID_SET_3, str);
	str.Format(_T("%.1f %%"), chamberData[2].currentHumid);
	SetDlgItemText(IDC_STATIC_HUMID_CUR_3, str);
	totalTemp += chamberData[2].currentTemp;
	totalHumid += chamberData[2].currentHumid;

	// 차트 데이터 추가
	double avgTemp = totalTemp / 3.0;
	double avgHumid = totalHumid / 3.0;

	COleDateTime now = COleDateTime::GetCurrentTime();
	double timeValue = now; // 시간 값을 double로 변환

	CChartLineSerie* pTempSerie = (CChartLineSerie*)m_chartCtrl.GetSerie(0);
	CChartLineSerie* pHumidSerie = (CChartLineSerie*)m_chartCtrl.GetSerie(1);

	pTempSerie->AddPoint(timeValue, avgTemp);
	pHumidSerie->AddPoint(timeValue, avgHumid);

	// X축을 시간 포맷으로 설정
	m_chartCtrl.GetBottomAxis()->SetDateTimeFormat(_T("%H:%M:%S"));

	// 데이터가 너무 많아지면 오래된 데이터 삭제
	if (pTempSerie->GetPointsCount() > 100)
	{
		pTempSerie->RemovePoints(0, pTempSerie->GetPointsCount() - 100);
		pHumidSerie->RemovePoints(0, pHumidSerie->GetPointsCount() - 100);
	}

	m_chartCtrl.Invalidate();
}