#include "pch.h"
#include "MFCBreadFactory.h"
#include "afxdialogex.h"
#include "CTab4Dlg.h"

IMPLEMENT_DYNAMIC(CTab4Dlg, CDialog)

CTab4Dlg::CTab4Dlg(int chamberIndex, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_TAB2_DLG, pParent), m_nChamberIndex(chamberIndex)
{
}

CTab4Dlg::~CTab4Dlg()
{
}

void CTab4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTab4Dlg, CDialog)
	ON_EN_CHANGE(IDC_EDIT_TEMP_SET, &CTab4Dlg::OnEnChangeEditTempSet)
	ON_EN_CHANGE(IDC_EDIT_HUMID_SET, &CTab4Dlg::OnEnChangeEditHumidSet)
	ON_CBN_SELCHANGE(IDC_COMBO_METHOD, &CTab4Dlg::OnCbnSelchangeComboMethod)
END_MESSAGE_MAP()

BOOL CTab4Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_METHOD);
	pCombo->AddString(_T("저온 숙성"));
	pCombo->AddString(_T("상온 숙성"));
	pCombo->AddString(_T("고온 숙성"));
	pCombo->SetCurSel(0);

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	if (pMainFrame)
	{
		AgingChamberData data = pMainFrame->GetChamberData(m_nChamberIndex);

		CString str;
		str.Format(_T("%.1f"), data.setTemp);
		SetDlgItemText(IDC_EDIT_TEMP_SET, str);
		str.Format(_T("%.1f"), data.setHumid);
		SetDlgItemText(IDC_EDIT_HUMID_SET, str);

		UpdateMainFrameData();
	}

	return TRUE;
}

void CTab4Dlg::UpdateCurrentData(const AgingChamberData& data)
{
	if (!GetSafeHwnd()) return;

	CString str;
	str.Format(_T("%.1f °C"), data.currentTemp);
	SetDlgItemText(IDC_STATIC_TEMP_CUR, str);
	str.Format(_T("%.1f %%"), data.currentHumid);
	SetDlgItemText(IDC_STATIC_HUMID_CUR, str);

	double tempDiff = data.currentTemp - data.setTemp;
	double humidDiff = data.currentHumid - data.setHumid;

	str.Format(_T("%+.1f °C"), tempDiff);
	SetDlgItemText(IDC_STATIC_TEMP_DIFF, str);
	str.Format(_T("%+.1f %%"), humidDiff);
	SetDlgItemText(IDC_STATIC_HUMID_DIFF, str);
}

void CTab4Dlg::UpdateMainFrameData()
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	if (pMainFrame)
	{
		AgingChamberData data;
		CString str;

		CComboBox* pCombo = (CComboBox*)GetDlgItem(IDC_COMBO_METHOD);
		int nSel = pCombo->GetCurSel();
		if (nSel != CB_ERR) {
			pCombo->GetLBText(nSel, data.methodName);
		}

		GetDlgItemText(IDC_EDIT_TEMP_SET, str);
		data.setTemp = _ttof(str);

		GetDlgItemText(IDC_EDIT_HUMID_SET, str);
		data.setHumid = _ttof(str);

		pMainFrame->UpdateChamberData(m_nChamberIndex, data);
	}
}

void CTab4Dlg::OnEnChangeEditTempSet() { UpdateMainFrameData(); }
void CTab4Dlg::OnEnChangeEditHumidSet() { UpdateMainFrameData(); }
void CTab4Dlg::OnCbnSelchangeComboMethod() { UpdateMainFrameData(); }