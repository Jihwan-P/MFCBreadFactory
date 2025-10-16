// CTab3Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCBreadFactory.h"
#include "afxdialogex.h"
#include "CTab3Dlg.h"
#include "MainFrm.h"
#include "CChatView.h"

IMPLEMENT_DYNAMIC(CTab3Dlg, CDialog)

CTab3Dlg::CTab3Dlg(CWnd* pParent /*=nullptr*/)
    : CDialog(IDD_TAB3_FORM, pParent)
{
    // 초기값 설정
    m_minTemp = 18.0f;
    m_maxTemp = 25.0f;
    m_minHumidity = 60.0f;
    m_maxHumidity = 75.0f;
    m_method = 1; // 상온 숙성
}

CTab3Dlg::~CTab3Dlg()
{
}

void CTab3Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    // CTab2Dlg와 동일하게 DDX_Control 매핑을 추가해야 하지만,
    // 현재 IDD_TAB3_FORM에는 해당 컨트롤이 없으므로 추가하지 않습니다.
    // 추후 숙성실3 탭의 UI를 구성할 때 추가해야 합니다.
}


BEGIN_MESSAGE_MAP(CTab3Dlg, CDialog)
    // ON_BN_CLICKED(IDC_BUTTON_APPLY, &CTab3Dlg::OnBnClickedButtonApply) // 버튼 ID가 다름
    ON_WM_TIMER()
END_MESSAGE_MAP()


// CTab3Dlg 메시지 처리기
BOOL CTab3Dlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // 타이머 설정 (5초마다 데이터 업데이트)
    SetTimer(2, 5000, NULL);
    UpdateData(true);

    return TRUE;
}

void CTab3Dlg::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent == 2) {
        UpdateData();
    }
    CDialog::OnTimer(nIDEvent);
}

void CTab3Dlg::UpdateData(bool bInit)
{
    // 임시로 랜덤 데이터 생성
    if (bInit) {
        m_tempData.resize(24);
        m_humidityData.resize(24);
        for (int i = 0; i < 24; ++i) {
            m_tempData[i] = (float)(rand() % 12 + 18); // 18 ~ 30
            m_humidityData[i] = (float)(rand() % 25 + 60); // 60 ~ 85
        }
    }
    else {
        m_tempData.erase(m_tempData.begin());
        m_humidityData.erase(m_humidityData.begin());
        m_tempData.push_back((float)(rand() % 12 + 18));
        m_humidityData.push_back((float)(rand() % 25 + 60));
    }

    // 알림 확인
    float currentTemp = m_tempData.back();
    float currentHumidity = m_humidityData.back();
    CString alertMsg;
    if (currentTemp > m_maxTemp) {
        alertMsg.Format(_T("숙성실2 적정 온도보다 %.1f도 높습니다."), currentTemp - m_maxTemp);
    }
    else if (currentTemp < m_minTemp) {
        alertMsg.Format(_T("숙성실2 적정 온도보다 %.1f도 낮습니다."), m_minTemp - currentTemp);
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

void CTab3Dlg::GetSettings(CString& method, CString& temp, CString& humidity)
{
    // CTab2Dlg와 달리 UI 컨트롤이 없으므로, 멤버 변수 값으로 직접 설정 정보를 만듭니다.
    if (m_method == 0) method = "저온 숙성";
    else method = "상온 숙성";

    temp.Format(_T("%.1f °C ~ %.1f °C"), m_minTemp, m_maxTemp);
    humidity.Format(_T("%.1f %% ~ %.1f %%"), m_minHumidity, m_maxHumidity);
}