
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

	ON_CBN_SELCHANGE(ID_COMBO_01, OnSelectClorBox)//선택할때
	ON_CBN_SELCHANGE(ID_COMBO_02, OnSelectPixelBox)//선택할때
	

END_MESSAGE_MAP()



static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame() noexcept
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

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

	// 콤보박스 추가하는곳

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

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return TRUE;
}
// CMainFrame 진단
#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}
void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

BOOL CMainFrame::AddCombo(CToolBar* pToolBar, CComboBox* pComboBox, int nIndex, int cx, int cy, DWORD dwStyle, UINT nID)
{
	CRect rect;
	pToolBar->GetItemRect(nIndex, rect);//툴바의 nIndex번째 버튼의 크기를 가져온다.

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


void CMainFrame::OnSelectClorBox()
{

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CJJFINTESTView* pView = (CJJFINTESTView*)pFrame->GetActiveView();
	pView->SetColor(colorBox.GetCurSel());


	/*int number = colorBox.GetCurSel();

	CString tmpStr;
	tmpStr.Format(_T("%d"), number);
	AfxMessageBox(tmpStr);*/

}

void CMainFrame::OnSelectPixelBox()
{

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CJJFINTESTView* pView = (CJJFINTESTView*)pFrame->GetActiveView();
	pView->SetPixel(pixelBox.GetCurSel());


	/*int number = colorBox.GetCurSel();
	CString tmpStr;
	tmpStr.Format(_T("%d"), number);
	AfxMessageBox(tmpStr);*/

}





#endif //_DEBUG


// CMainFrame 메시지 처리기

