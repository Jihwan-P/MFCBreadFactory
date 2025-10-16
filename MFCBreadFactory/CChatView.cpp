// CChatView.cpp: 구현 파일
//

#include "pch.h"
#include "MFCBreadFactory.h"
#include "CChatView.h"

#define TIMER_UPDATE_TIME 1

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
    DDX_Control(pDX, IDC_STATIC_TIME, m_staticTimeDisplay);
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
	cs.style &= ~WS_HSCROLL;
    cs.style &= ~WS_VSCROLL;

	return CFormView::PreCreateWindow(cs);
}

void CChatView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	SetScrollSizes(MM_TEXT, CSize(0, 0));

	SetTimer(TIMER_UPDATE_TIME, 1000, NULL);
	OnTimer(TIMER_UPDATE_TIME);

	GetParentFrame()->RecalcLayout();
	// 크기 조정에 영향을 주지 않도록 합니다.
	// ResizeParentToFit()
}

void CChatView::OnSize(UINT nType, int cx, int cy)
{
    CFormView::OnSize(nType, cx, cy);

    // 컨트롤이 생성되었는지 확인
	if (m_staticTimeDisplay.GetSafeHwnd() && m_listChat.GetSafeHwnd() && m_editChat.GetSafeHwnd() && m_btnSend.GetSafeHwnd())
	{
		// 컨트롤 재배치를 위한 상수 정의
		const int nMargin = 10;
		const int nTimeHeight = 14;
		const int nInputHeight = 32;
		const int nButtonWidth = 65;
		const int nGap = 8; // 컨트롤 간의 간격

		// 1. 시간 표시 (Static Text) 위치 및 크기 조정
		m_staticTimeDisplay.MoveWindow(nMargin, nMargin, cx - (nMargin * 2), nTimeHeight);

		// 2. 채팅 입력창 (Edit Control) 위치 및 크기 조정
		m_editChat.MoveWindow(nMargin, cy - nInputHeight - nMargin, cx - (nMargin * 2) - nButtonWidth - nGap, nInputHeight);

		// 3. 전송 버튼 위치 및 크기 조정
		m_btnSend.MoveWindow(cx - nMargin - nButtonWidth, cy - nInputHeight - nMargin, nButtonWidth, nInputHeight);

		// 4. 채팅 내역 (List Box) 위치 및 크기 조정
		// (시간 표시 아래부터 입력창 위까지)
		int nListTop = nMargin + nTimeHeight + nGap;
		int nListHeight = cy - nListTop - nInputHeight - nMargin - nGap;
		m_listChat.MoveWindow(nMargin, nListTop, cx - (nMargin * 2), nListHeight);
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
        m_listChat.AddString(strText); // 예시: 리스트 박스에 추가
        m_editChat.SetWindowText(_T("")); // 입력창 비우기
    }
    m_editChat.SetFocus(); // 입력창에 포커스 유지
}

void CChatView::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == TIMER_UPDATE_TIME)
	{
		// 현재 시간을 가져와 CStatic 컨트롤에 표시
		CTime time = CTime::GetCurrentTime();
		CString strTime = time.Format(_T("%Y-%m-%d %H:%M:%S"));
		m_staticTimeDisplay.SetWindowText(strTime);
	}

	CFormView::OnTimer(nIDEvent);
}

void CChatView::OnDestroy()
{
	CFormView::OnDestroy();

	// 뷰가 파괴될 때 타이머를 해제합니다.
	KillTimer(TIMER_UPDATE_TIME);
}