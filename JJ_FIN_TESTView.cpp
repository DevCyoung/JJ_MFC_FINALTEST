
// JJ_FIN_TESTView.cpp: CJJFINTESTView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "MainFrm.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "JJ_FIN_TEST.h"
#endif

#include "JJ_FIN_TESTDoc.h"
#include "JJ_FIN_TESTView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CJJFINTESTView

IMPLEMENT_DYNCREATE(CJJFINTESTView, CView)

BEGIN_MESSAGE_MAP(CJJFINTESTView, CView)


	// 표준 인쇄 명령입니다.
	/*ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)*/
	/*ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)*/

	//사용자 정의
	ON_COMMAND(ID_FILE_PRINT,   &CJJFINTESTView::OnClickPreViewPrint)
	ON_COMMAND(ID_MY_CIRCLE,    &CJJFINTESTView::OnClickCircle)
	ON_COMMAND(ID_MY_RECTANGLE, &CJJFINTESTView::OnClickRECTANGLE)

	// MFC 정의
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()

END_MESSAGE_MAP()

int CJJFINTESTView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	isDraw = TRUE;

	return 0;
}


// CJJFINTESTView 생성/소멸

CJJFINTESTView::CJJFINTESTView() noexcept{}
CJJFINTESTView::~CJJFINTESTView(){}

// CJJFINTESTView 그리기
void CJJFINTESTView::OnDraw(CDC* pDC)
{
	CJJFINTESTDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	/// ///////////////////////////////////////////////////////////////////
	/// Double buffering
	CRect clientRect;
	GetClientRect(&clientRect);
	CDC memDC;
	CBitmap memBitmap;
	CBrush backGround;
	//배경을 흰색으로한다.
	backGround.CreateSolidBrush(RGB(255, 255, 255));
	memDC.CreateCompatibleDC(pDC);
	memBitmap.CreateCompatibleBitmap(pDC, clientRect.right, clientRect.bottom);
	CBitmap* pOldBitmap = (CBitmap*)memDC.SelectObject(&memBitmap);
	memDC.FillRect( &clientRect, &backGround );
	/// Double buffering
	/// ///////////////////////////////////////////////////////////////////

	// 모든 그림은 memDC 에서 그립니다.
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	
	//이전의 모든그림을 그립니다.
	figureManager.AllDraw(memDC);
	
	//현재 그림을 그립니다.
	Figure fig;
	fig.SetInit(x1, y1, x2, y2, curColor, curPixel, curButton);
	fig.Show(memDC);
	
	/// ///////////////////////////////////////////////////////////////////
	/// Double buffering
	pDC->BitBlt(0, 0, clientRect.right, clientRect.bottom, &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOldBitmap);
	ReleaseDC(&memDC);
	/// Double buffering
	/// ///////////////////////////////////////////////////////////////////
}

#ifdef _DEBUG

//여기서부터 사용자가 생성하였습니다.
void CJJFINTESTView::DrawFigure(int x1, int y1, int x2, int y2, CDC& dc)
{

	CPen pen;
	pen.CreatePen(PS_DOT, curPixel, curColor );    
	CPen* oldPen = dc.SelectObject(&pen);
	CBrush brush;
	CBrush* oldBrush = dc.SelectObject(&brush);
	dc.SelectStockObject(NULL_BRUSH);

	switch (curButton)
	{
		case CIRCLE:
			dc.Ellipse(x1, y1, x2, y2);
			break;
		case RECTANGLE:
			dc.Rectangle(x1, y1, x2, y2);
			break;
	}

	dc.SelectObject(oldBrush);
	dc.SelectObject(oldPen);     // 시스템 펜 객체를 돌려줌

}


void CJJFINTESTView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// 그리기 모드이면 타원을 지우고 그리기를 반복한다.

	if (isDraw) {

		CClientDC dc(this);
		x2 = point.x;
		y2 = point.y;

		Invalidate(FALSE);

	}
}


void CJJFINTESTView::OnLButtonDown(UINT nFlags, CPoint point)
{

	isDraw = TRUE;
	x1 = x2 = point.x;
	y1 = y2 = point.y;

}
void CJJFINTESTView::OnLButtonUp(UINT nFlags, CPoint point)
{

	CClientDC dc(this);
	x2 = point.x;
	y2 = point.y;
	isDraw = FALSE;
	figureManager.NextFigure(x1,y1,x2,y2,curColor , curPixel , curButton);
}
void CJJFINTESTView::SetColor(int sel)
{
	curColor = colors[sel];
}

void CJJFINTESTView::SetPixel(int sel)
{
	curPixel = fixels[sel];
}



CJJFINTESTDoc* CJJFINTESTView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CJJFINTESTDoc)));
	return (CJJFINTESTDoc*)m_pDocument;
}
#endif //_DEBUG












void CJJFINTESTView::OnClickCircle()
{
	curButton = CIRCLE;
}
void CJJFINTESTView::OnClickRECTANGLE()
{
	curButton = RECTANGLE;
}
void CJJFINTESTView::OnClickPreViewPrint()
{
	CView::OnFilePrintPreview();
}

BOOL CJJFINTESTView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}
void CJJFINTESTView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{

	

	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}
void CJJFINTESTView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}