// CTab2Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCBreadFactory.h"
#include "afxdialogex.h"
#include "CTab2Dlg.h"
#include "MainFrm.h" // MainFrame 접근을 위해
#include "CChatView.h" // CChatView 접근을 위해

IMPLEMENT_DYNAMIC(CTab2Dlg, CDialog)

CTab2Dlg::CTab2Dlg(CWnd* pParent /*=nullptr*/)
    : CDialog(IDD_TAB2_FORM, pParent)
{
    // 초기값 설정
    m_minTemp = 20.0f;
    m_maxTemp = 30.0f;
    m_minHumidity = 50.0f;
    m_maxHumidity = 70.0f;
    m_method = 0;
}

CTab2Dlg::~CTab2Dlg()
{
}

void CTab2Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATIC_CHART, m_chart);
    DDX_Control(pDX, IDC_STATIC_CURRENT_TEMP, m_stcCurrentTemp);
    DDX_Control(pDX, IDC_STATIC_CURRENT_HUMIDITY, m_stcCurrentHumidity);
    DDX_Control(pDX, IDC_EDIT_MIN_TEMP, m_editMinTemp);
    DDX_Control(pDX, IDC_EDIT_MAX_TEMP, m_editMaxTemp);
    DDX_Control(pDX, IDC_EDIT_MIN_HUMIDITY, m_editMinHumidity);
    DDX_Control(pDX, IDC_EDIT_MAX_HUMIDITY, m_editMaxHumidity);
    DDX_Control(pDX, IDC_COMBO_METHOD, m_comboMethod);
}

BEGIN_MESSAGE_MAP(CTab2Dlg, CDialog)
    ON_BN_CLICKED(IDC_BUTTON_APPLY, &CTab2Dlg::OnBnClickedButtonApply)
    ON_WM_TIMER()
END_MESSAGE_MAP()

BOOL CTab2Dlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // ComboBox 초기화
    m_comboMethod.AddString(_T("저온 숙성"));
    m_comboMethod.AddString(_T("상온 숙성"));
    m_comboMethod.SetCurSel(0);

    // Edit Control 초기값 설정
    CString str;
    str.Format(_T("%.1f"), m_minTemp); m_editMinTemp.SetWindowText(str);
    str.Format(_T("%.1f"), m_maxTemp); m_editMaxTemp.SetWindowText(str);
    str.Format(_T("%.1f"), m_minHumidity); m_editMinHumidity.SetWindowText(str);
    str.Format(_T("%.1f"), m_maxHumidity); m_editMaxHumidity.SetWindowText(str);

    // 타이머 설정 (5초마다 데이터 업데이트)
    SetTimer(1, 5000, NULL);
    UpdateData(true); // 초기 데이터 로드

    return TRUE;
}

void CTab2Dlg::OnBnClickedButtonApply()
{
    CString str;
    m_editMinTemp.GetWindowText(str); m_minTemp = _ttof(str);
    m_editMaxTemp.GetWindowText(str); m_maxTemp = _ttof(str);
    m_editMinHumidity.GetWindowText(str); m_minHumidity = _ttof(str);
    m_editMaxHumidity.GetWindowText(str); m_maxHumidity = _ttof(str);
    m_method = m_comboMethod.GetCurSel();

    m_chart.SetRanges(m_minTemp, m_maxTemp, m_minHumidity, m_maxHumidity);
    AfxMessageBox(_T("설정이 적용되었습니다."));
}

void CTab2Dlg::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent == 1) {
        UpdateData();
    }
    CDialog::OnTimer(nIDEvent);
}

void CTab2Dlg::UpdateData(bool bInit)
{
    // 임시로 랜덤 데이터 생성 (실제로는 센서 등에서 데이터를 가져와야 함)
    if (bInit) {
        m_tempData.resize(24);
        m_humidityData.resize(24);
        for (int i = 0; i < 24; ++i) {
            m_tempData[i] = (float)(rand() % 15 + 20); // 20 ~ 35
            m_humidityData[i] = (float)(rand() % 30 + 50); // 50 ~ 80
        }
    }
    else {
        // 가장 오래된 데이터 지우고 새 데이터 추가
        m_tempData.erase(m_tempData.begin());
        m_humidityData.erase(m_humidityData.begin());
        m_tempData.push_back((float)(rand() % 15 + 20));
        m_humidityData.push_back((float)(rand() % 30 + 50));
    }

    // 차트 업데이트
    m_chart.SetData(m_tempData, m_humidityData);
    m_chart.SetRanges(m_minTemp, m_maxTemp, m_minHumidity, m_maxHumidity);


    // 현재 값 UI 업데이트
    float currentTemp = m_tempData.back();
    float currentHumidity = m_humidityData.back();
    CString str;
    str.Format(_T("%.1f °C"), currentTemp);
    m_stcCurrentTemp.SetWindowText(str);
    str.Format(_T("%.1f %%"), currentHumidity);
    m_stcCurrentHumidity.SetWindowText(str);

    // 알림 확인
    CString alertMsg;
    if (currentTemp > m_maxTemp) {
        alertMsg.Format(_T("숙성실1 적정 온도보다 %.1f도 높습니다."), currentTemp - m_maxTemp);
    }
    else if (currentTemp < m_minTemp) {
        alertMsg.Format(_T("숙성실1 적정 온도보다 %.1f도 낮습니다."), m_minTemp - currentTemp);
    }
    else if (currentHumidity > m_maxHumidity) {
        alertMsg.Format(_T("숙성실1 적정 습도보다 %.1f%% 높습니다."), currentHumidity - m_maxHumidity);
    }
    else if (currentHumidity < m_minHumidity) {
        alertMsg.Format(_T("숙성실1 적정 습도보다 %.1f%% 낮습니다."), m_minHumidity - currentHumidity);
    }

    if (!alertMsg.IsEmpty()) {
        AfxMessageBox(alertMsg, MB_ICONWARNING);

        // 채팅창에 메시지 보내기
        CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
        if (pFrame)
        {
            CWnd* pWnd = pFrame->m_wndSplitter.GetPane(0, 1);
            if (pWnd && pWnd->IsKindOf(RUNTIME_CLASS(CChatView))) {
                CChatView* pChatView = (CChatView*)pWnd;

                CTime t = CTime::GetCurrentTime();
                CString strTime;
                strTime.Format(_T("[%02d:%02d:%02d]"), t.GetHour(), t.GetMinute(), t.GetSecond());

                CString strMessage;
                strMessage.Format(_T("%s [시스템] : %s"), strTime, alertMsg);

                pChatView->m_listChat.AddString(strMessage);
                int nIndex = pChatView->m_listChat.GetCount() - 1;
                if (nIndex >= 0)
                {
                    pChatView->m_listChat.SetTopIndex(nIndex);
                }
            }
        }
    }
}

// 설정 정보를 CString 참조를 통해 반환하는 함수 구현
void CTab2Dlg::GetSettings(CString& method, CString& temp, CString& humidity)
{
    if (m_comboMethod.GetSafeHwnd()) // 컨트롤이 생성되었는지 확인
    {
        int sel = m_comboMethod.GetCurSel();
        if (sel != CB_ERR)
        {
            m_comboMethod.GetLBText(sel, method);
        }
        else
        {
            method = "미선택";
        }

        temp.Format(_T("%.1f °C ~ %.1f °C"), m_minTemp, m_maxTemp);
        humidity.Format(_T("%.1f %% ~ %.1f %%"), m_minHumidity, m_maxHumidity);
    }
    else // 아직 컨트롤이 생성되지 않았다면 초기값 사용
    {
        method = "저온 숙성"; // 기본값
        temp.Format(_T("%.1f °C ~ %.1f °C"), 20.0f, 30.0f);
        humidity.Format(_T("%.1f %% ~ %.1f %%"), 50.0f, 70.0f);
    }
}