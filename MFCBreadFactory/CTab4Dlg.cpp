// CTab4Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCBreadFactory.h"
#include "afxdialogex.h"
#include "CTab4Dlg.h"
#include "MainFrm.h"
#include "CChatView.h"


// CTab4Dlg 대화 상자

IMPLEMENT_DYNAMIC(CTab4Dlg, CDialog)

CTab4Dlg::CTab4Dlg(CWnd* pParent /*=nullptr*/)
    : CDialog(IDD_TAB4_FORM, pParent)
{
    // 초기값 설정
    m_minTemp = 22.0f;
    m_maxTemp = 28.0f;
    m_minHumidity = 55.0f;
    m_maxHumidity = 65.0f;
    m_method = 1; // 상온 숙성
}

CTab4Dlg::~CTab4Dlg()
{
}

void CTab4Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTab4Dlg, CDialog)
    ON_WM_TIMER()
END_MESSAGE_MAP()


// CTab4Dlg 메시지 처리기
BOOL CTab4Dlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // 타이머 설정 (5초마다 데이터 업데이트)
    SetTimer(3, 5000, NULL);
    UpdateData(true);

    return TRUE;
}

void CTab4Dlg::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent == 3) {
        UpdateData();
    }
    CDialog::OnTimer(nIDEvent);
}

void CTab4Dlg::UpdateData(bool bInit)
{
    // 임시로 랜덤 데이터 생성
    if (bInit) {
        m_tempData.resize(24);
        m_humidityData.resize(24);
        for (int i = 0; i < 24; ++i) {
            m_tempData[i] = (float)(rand() % 10 + 20); // 20 ~ 30
            m_humidityData[i] = (float)(rand() % 20 + 50); // 50 ~ 70
        }
    }
    else {
        m_tempData.erase(m_tempData.begin());
        m_humidityData.erase(m_humidityData.begin());
        m_tempData.push_back((float)(rand() % 10 + 20));
        m_humidityData.push_back((float)(rand() % 20 + 50));
    }

    // 알림 확인
    float currentTemp = m_tempData.back();
    float currentHumidity = m_humidityData.back();
    CString alertMsg;
    if (currentTemp > m_maxTemp) {
        alertMsg.Format(_T("숙성실3 적정 온도보다 %.1f도 높습니다."), currentTemp - m_maxTemp);
    }
    else if (currentTemp < m_minTemp) {
        alertMsg.Format(_T("숙성실3 적정 온도보다 %.1f도 낮습니다."), m_minTemp - currentTemp);
    }

    if (!alertMsg.IsEmpty()) {
        AfxMessageBox(alertMsg, MB_ICONWARNING);
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
                if (nIndex >= 0) { pChatView->m_listChat.SetTopIndex(nIndex); }
            }
        }
    }
}

void CTab4Dlg::GetSettings(CString& method, CString& temp, CString& humidity)
{
    if (m_method == 0) method = "저온 숙성";
    else method = "상온 숙성";

    temp.Format(_T("%.1f °C ~ %.1f °C"), m_minTemp, m_maxTemp);
    humidity.Format(_T("%.1f %% ~ %.1f %%"), m_minHumidity, m_maxHumidity);
}