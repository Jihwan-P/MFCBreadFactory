// CChatView.cpp: 구현 파일
//

#include "pch.h"
#include "MFCBreadFactory.h"
#include "CChatView.h"
#include <afx.h>

#define IDC_TIMER_CLOCK 1001

// CChatView

IMPLEMENT_DYNCREATE(CChatView, CFormView)

CChatView::CChatView()
	: CFormView(IDD_CHAT_FORM)
{

}

CChatView::~CChatView()
{
}

void CChatView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	// 컨트롤과 멤버 변수를 연결합니다.
    DDX_Control(pDX, IDC_STATIC_CLOCK, m_staticClock);
	DDX_Control(pDX, IDC_LIST_CHAT, m_listChat);
	DDX_Control(pDX, IDC_EDIT_CHAT, m_editChat);
	DDX_Control(pDX, IDC_BUTTON_SEND, m_btnSend);
}

BEGIN_MESSAGE_MAP(CChatView, CFormView)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CChatView::OnBnClickedBtnSend)
    ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CChatView 진단

#ifdef _DEBUG
void CChatView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CChatView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CChatView 메시지 처리기

BOOL CChatView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	// 뷰가 생성되기 전에 윈도우 스타일에서 가로 스크롤바 속성을 제거합니다.
	cs.style &= ~(WS_HSCROLL | WS_VSCROLL);

	return CFormView::PreCreateWindow(cs);
}

void CChatView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	// 크기 조정에 영향을 주지 않도록 합니다.
	// ResizeParentToFit()
    SetScrollSizes(MM_TEXT, CSize(0, 0));

    // 1초마다 OnTimer 함수를 호출하는 타이머를 설정합니다.
    SetTimer(IDC_TIMER_CLOCK, 1000, NULL);
    OnTimer(IDC_TIMER_CLOCK);

    // 채팅 내역 리스트 박스의 폰트를 생성하고 적용합니다.
    // 120 = 12.0pt 크기, "Malgun Gothic" 폰트 (이 값을 조절하여 크기 변경 가능)
    m_fontChat.CreatePointFont(100, _T("Malgun Gothic"));
    m_listChat.SetFont(&m_fontChat);
}

void CChatView::OnSize(UINT nType, int cx, int cy)
{
    CFormView::OnSize(nType, cx, cy);

    // m_staticClock 변수가 유효한지 함께 확인합니다.
    if (m_staticClock.GetSafeHwnd() && m_listChat.GetSafeHwnd())
    {
        // 컨트롤 재배치를 위한 상수 정의
        const int nMargin = 10;
        const int nClockHeight = 14;
        const int nInputHeight = 32;
        const int nButtonWidth = 65;
        const int nGap = 8;

        // 1. 시계 컨트롤 위치 및 크기 조정
        m_staticClock.MoveWindow(nMargin, nMargin, cx - (nMargin * 2), nClockHeight);

        // 2. 채팅 입력창(Edit Control) 위치 및 크기 조정
        m_editChat.MoveWindow(nMargin, cy - nInputHeight - nMargin, cx - (nMargin * 2) - nButtonWidth - nGap, nInputHeight);

        // 3. 전송 버튼 위치 및 크기 조정
        m_btnSend.MoveWindow(cx - nMargin - nButtonWidth, cy - nInputHeight - nMargin, nButtonWidth, nInputHeight);

        // 4. 채팅 내역(List Box) 위치 및 크기 조정 (겹치지 않도록 수정)
        //    (시계 아래부터 입력창 위까지의 공간을 차지하도록 계산)
        int listTop = nMargin + nClockHeight + nGap;
        int listHeight = cy - listTop - nInputHeight - nMargin - nGap;
        m_listChat.MoveWindow(nMargin, listTop, cx - (nMargin * 2), listHeight);
    }
}

void CChatView::OnBnClickedBtnSend()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
    // 전송 버튼 클릭 시 동작할 코드를 여기에 작성합니다.
    CString strText;
    m_editChat.GetWindowText(strText);
    
    if (!strText.IsEmpty())
    {
        // 1. 현재 시간 가져오기 및 형식 지정
        CTime t = CTime::GetCurrentTime();
        CString strTime;
        strTime.Format(_T("[%02d:%02d:%02d]"), t.GetHour(), t.GetMinute(), t.GetSecond());

        // 2. 사용자 이름 설정 (추후 로그인 기능과 연동 가능합니다)
        CString strName = _T("사용자");

        // 3. 최종 채팅 문자열 조합
        CString strMessage;
        strMessage.Format(_T("%s %s : %s"), strTime, strName, strText);

        // 4. 조합된 문자열을 리스트 박스에 추가
        m_listChat.AddString(strMessage);

        // 새 메시지 추가 후 맨 아래로 스크롤되도록 설정
        int nIndex = m_listChat.GetCount() - 1;
        if (nIndex >= 0)
        {
            m_listChat.SetTopIndex(nIndex);
        }

        // 입력창 비우기 및 포커스 설정
        m_editChat.SetWindowText(_T(""));
    }
    m_editChat.SetFocus();
}

void CChatView::OnTimer(UINT_PTR nIDEvent)
{
    // 시계 타이머 이벤트일 경우
    if (nIDEvent == IDC_TIMER_CLOCK)
    {
        // 현재 시간을 가져와 "현재 시간 : YYYY-MM-DD hh:mm:ss" 형식으로 변환합니다.
        CTime t = CTime::GetCurrentTime();
        CString strTime;
        strTime.Format(_T("현재 시간 : %04d-%02d-%02d %02d:%02d:%02d"),
            t.GetYear(), t.GetMonth(), t.GetDay(),
            t.GetHour(), t.GetMinute(), t.GetSecond());

        // Static Text 컨트롤에 시간을 업데이트합니다.
        m_staticClock.SetWindowText(strTime);
    }

    CFormView::OnTimer(nIDEvent);
}

void CChatView::OnDestroy()
{
    CFormView::OnDestroy();
    // 뷰가 파괴될 때 타이머를 해제합니다.
    KillTimer(IDC_TIMER_CLOCK);
}