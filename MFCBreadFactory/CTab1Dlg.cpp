// CTab1View.cpp: 구현 파일
//

#include "pch.h"
#include "MFCBreadFactory.h"
#include "afxdialogex.h"
#include "CTab1Dlg.h"
#include "MFCBreadFactoryView.h" // 부모 뷰를 통해 다른 탭에 접근하기 위해 포함

// CTab1Dlg 대화 상자

IMPLEMENT_DYNAMIC(CTab1Dlg, CDialog)

CTab1Dlg::CTab1Dlg(CWnd* pParent /*=nullptr*/)
    : CDialog(IDD_TAB1_FORM, pParent)
{

}

CTab1Dlg::~CTab1Dlg()
{
}

void CTab1Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATIC_ROOM1_METHOD, m_stcRoom1Method);
    DDX_Control(pDX, IDC_STATIC_ROOM1_TEMP, m_stcRoom1Temp);
    DDX_Control(pDX, IDC_STATIC_ROOM1_HUMIDITY, m_stcRoom1Humidity);
    DDX_Control(pDX, IDC_STATIC_ROOM2_METHOD, m_stcRoom2Method);
    DDX_Control(pDX, IDC_STATIC_ROOM2_TEMP, m_stcRoom2Temp);
    DDX_Control(pDX, IDC_STATIC_ROOM2_HUMIDITY, m_stcRoom2Humidity);
    DDX_Control(pDX, IDC_STATIC_ROOM3_METHOD, m_stcRoom3Method);
    DDX_Control(pDX, IDC_STATIC_ROOM3_TEMP, m_stcRoom3Temp);
    DDX_Control(pDX, IDC_STATIC_ROOM3_HUMIDITY, m_stcRoom3Humidity);
}


BEGIN_MESSAGE_MAP(CTab1Dlg, CDialog)
    ON_WM_TIMER()
END_MESSAGE_MAP()


// CTab1Dlg 메시지 처리기

BOOL CTab1Dlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // 1초마다 UpdateSummary 함수를 호출하는 타이머 설정
    SetTimer(1, 1000, NULL);

    return TRUE;  // return TRUE unless you set the focus to a control
}

void CTab1Dlg::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent == 1) {
        UpdateSummary();
    }
    CDialog::OnTimer(nIDEvent);
}

void CTab1Dlg::UpdateSummary()
{
    // 부모 윈도우(CMFCBreadFactoryView)의 포인터를 가져옵니다.
    // this->GetParent()는 탭 컨트롤(CTabCtrl)을 반환하므로,
    // 탭 컨트롤의 부모인 CMFCBreadFactoryView를 가져오기 위해 GetParent()를 한 번 더 호출합니다.
    CWnd* pParentWnd = GetParent()->GetParent();
    if (!pParentWnd || !pParentWnd->IsKindOf(RUNTIME_CLASS(CMFCBreadFactoryView)))
    {
        return;
    }
    CMFCBreadFactoryView* pParentView = static_cast<CMFCBreadFactoryView*>(pParentWnd);


    CString method, temp, humidity;

    // 숙성실 1 (CTab2Dlg) 데이터 업데이트
    if (pParentView->m_pTab2Dlg && pParentView->m_pTab2Dlg->GetSafeHwnd()) {
        pParentView->m_pTab2Dlg->GetSettings(method, temp, humidity);
        m_stcRoom1Method.SetWindowText(method);
        m_stcRoom1Temp.SetWindowText(temp);
        m_stcRoom1Humidity.SetWindowText(humidity);
    }

    // 숙성실 2 (CTab3Dlg) 데이터 업데이트
    if (pParentView->m_pTab3Dlg && pParentView->m_pTab3Dlg->GetSafeHwnd()) {
        pParentView->m_pTab3Dlg->GetSettings(method, temp, humidity);
        m_stcRoom2Method.SetWindowText(method);
        m_stcRoom2Temp.SetWindowText(temp);
        m_stcRoom2Humidity.SetWindowText(humidity);
    }

    // 숙성실 3 (CTab4Dlg) 데이터 업데이트
    if (pParentView->m_pTab4Dlg && pParentView->m_pTab4Dlg->GetSafeHwnd()) {
        pParentView->m_pTab4Dlg->GetSettings(method, temp, humidity);
        m_stcRoom3Method.SetWindowText(method);
        m_stcRoom3Temp.SetWindowText(temp);
        m_stcRoom3Humidity.SetWindowText(humidity);
    }
}