
// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "JJ_FIN_TEST.h"
#include "MainFrm.h"
#include "JJ_FIN_TESTView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)

	ON_WM_CREATE()
	ON_CBN_SELCHANGE(ID_COMBO_01, OnClorCheckBox)//선택할때
	ON_CBN_SELCHANGE(ID_COMBO_02, OnPixelCheckBox)//선택할때

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸
CMainFrame::CMainFrame() noexcept{}
CMainFrame::~CMainFrame(){}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;


	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("도구 모음을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	 //TODO: 도구 모음을 도킹할 수 없게 하려면 이 세 줄을 삭제하십시오.
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	// 콤보박스를 추가합니다.
	AddCombo(&m_wndToolBar, &colorBox, 4, 100, 100,   WS_CHILD | CBS_DROPDOWN |
		CBS_AUTOHSCROLL | WS_VSCROLL | CBS_HASSTRINGS, ID_COMBO_01);
	colorBox.AddString(_T("RED"));
	colorBox.AddString(_T("BLUE"));
	colorBox.AddString(_T("GREEN"));
	colorBox.SetCurSel(0);

	AddCombo(&m_wndToolBar, &pixelBox, 5, 100, 100, WS_CHILD | CBS_DROPDOWN |
		CBS_AUTOHSCROLL | WS_VSCROLL | CBS_HASSTRINGS, ID_COMBO_02);
	pixelBox.AddString(_T("1  px"));
	pixelBox.AddString(_T("5  px"));
	pixelBox.AddString(_T("10 px"));
	pixelBox.SetCurSel(0);

	return 0;
}

// CMainFrame 진단
#ifdef _DEBUG

BOOL CMainFrame::AddCombo(CToolBar* pToolBar, CComboBox* pComboBox, int nIndex, int cx, int cy, DWORD dwStyle, UINT nID)
{
	CRect rect;
	//툴바의 nIndex번째 버튼의 크기를 가져온다.
	pToolBar->GetItemRect(nIndex, rect);

	//크기 재설정
	rect.right = rect.left + cx;
	rect.bottom = rect.top + cy;

	//콤보박스 생성
	if (!pComboBox->Create(dwStyle, rect, pToolBar, nID))
		return FALSE;
	pComboBox->ShowWindow(SW_SHOW);

	//콤보박스가 추가되어야할 버튼의 크기를 재설정
	pToolBar->SetButtonInfo(nIndex, nID, TBBS_SEPARATOR, cx);
	return TRUE;
}


// 체크박스 선택시 실행됩니다.
void CMainFrame::OnClorCheckBox()
{

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CJJFINTESTView* pView = (CJJFINTESTView*)pFrame->GetActiveView();
	pView->SetColor(colorBox.GetCurSel());

}
// 체크박스 선택시 실행됩니다.
void CMainFrame::OnPixelCheckBox()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CJJFINTESTView* pView = (CJJFINTESTView*)pFrame->GetActiveView();
	pView->SetPixel(pixelBox.GetCurSel());
}


#endif //_DEBUG