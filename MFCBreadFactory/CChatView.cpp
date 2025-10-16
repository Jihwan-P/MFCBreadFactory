// CChatView.cpp: 구현 파일
//

#include "pch.h"
#include "MFCBreadFactory.h"
#include "CChatView.h"


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
	DDX_Control(pDX, IDC_LIST_CHAT, m_listChat);
	DDX_Control(pDX, IDC_EDIT_CHAT, m_editChat);
	DDX_Control(pDX, IDC_BUTTON_SEND, m_btnSend);
}

BEGIN_MESSAGE_MAP(CChatView, CFormView)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CChatView::OnBnClickedBtnSend)
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
	GetParentFrame()->RecalcLayout();
	// 크기 조정에 영향을 주지 않도록 합니다.
	// ResizeParentToFit()
}

void CChatView::OnSize(UINT nType, int cx, int cy)
{
    CFormView::OnSize(nType, cx, cy);

    if (m_listChat.GetSafeHwnd()) // 컨트롤이 생성되었는지 확인
    {
        // 컨트롤 재배치를 위한 상수 정의
        const int nMargin = 10;
        const int nInputHeight = 32;
        const int nButtonWidth = 65;
        const int nGap = 8;

        // 1. 채팅 입력창(Edit Control) 위치 및 크기 조정
        //    (창 너비 - 여백 - 버튼 너비 - 간격)
        m_editChat.MoveWindow(nMargin, cy - nInputHeight - nMargin, cx - (nMargin * 2) - nButtonWidth - nGap, nInputHeight);

        // 2. 전송 버튼 위치 및 크기 조정
        m_btnSend.MoveWindow(cx - nMargin - nButtonWidth, cy - nInputHeight - nMargin, nButtonWidth, nInputHeight);

        // 3. 채팅 내역(List Box) 위치 및 크기 조정
        //    (상단 여백부터 입력창 위까지)
        m_listChat.MoveWindow(nMargin, nMargin, cx - (nMargin * 2), cy - (nMargin * 2) - nInputHeight - nGap);
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