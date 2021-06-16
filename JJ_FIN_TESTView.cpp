
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

	//사용자 정의
	ON_COMMAND(ID_FILE_PRINT,   &CJJFINTESTView::OnClickPreViewPrint)
	ON_COMMAND(ID_MY_PRINT,     &CView::OnFilePrint)

	ON_COMMAND(ID_MY_CIRCLE,		 &CJJFINTESTView::OnClickCircle)
	ON_COMMAND(ID_MY_RECTANGLE,		 &CJJFINTESTView::OnClickRECTANGLE)
	ON_COMMAND(ID_MY_CIRCLE_FILL,	 &CJJFINTESTView::OnClickCircleFILL)
	ON_COMMAND(ID_MY_RECTANGLE_FILL, &CJJFINTESTView::OnClickRECTANGLEFILL)
	ON_COMMAND(ID_MY_CLEAR, &CJJFINTESTView::OnClickCLEAR)


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
	fig.SetInit(x1, y1, x2, y2, curColor, curPixel, curButton,isFill);
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

// 도형을 그리는것은 예제 Circle을 대부분 참고하였습니다.
void CJJFINTESTView::OnMouseMove(UINT nFlags, CPoint point)
{

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
	x2 = point.x;
	y2 = point.y;
	isDraw = FALSE;

	//도형을 초기화합니다.

	if( curButton != 0)
		figureManager.NextFigure(x1,y1,x2,y2,curColor , curPixel , curButton , isFill);

}

void CJJFINTESTView::SetColor(int sel)
{
	curColor = colors[sel];
}

void CJJFINTESTView::SetPixel(int sel)
{
	curPixel = fixels[sel];
}
#endif //_DEBUG

///////////////////////////////////////////
//툴바 선택시 실행되는 함수입니다.
void CJJFINTESTView::OnClickCircle()
{
	curButton = CIRCLE;
	isFill = FALSE;
}
void CJJFINTESTView::OnClickRECTANGLE()
{
	curButton = RECTANGLE;
	isFill = FALSE;
}

void CJJFINTESTView::OnClickCircleFILL()
{
	curButton = CIRCLE;
	isFill = TRUE;
}

void CJJFINTESTView::OnClickRECTANGLEFILL()
{
	curButton = RECTANGLE;
	isFill = TRUE;
}

void CJJFINTESTView::OnClickCLEAR()
{
	for (int i = 0; i < FIGURE_PULL; i++)
	{
		figureManager.figures[i].isAlive = false;
		figureManager.curPos = 0;
	}
	x1 = 0;
	y1 = 0;
	x2 = 0; 
	y2 = 0;
	Invalidate(FALSE);
	
}



void CJJFINTESTView::OnClickPreViewPrint()
{
	CView::OnFilePrintPreview();
}
//툴바 선택시 실행되는 함수입니다.
///////////////////////////////////////////

BOOL CJJFINTESTView::OnPreparePrinting(CPrintInfo* pInfo){return DoPreparePrinting(pInfo);}
void CJJFINTESTView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo){}
void CJJFINTESTView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/){}

CJJFINTESTDoc* CJJFINTESTView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CJJFINTESTDoc)));
	return (CJJFINTESTDoc*)m_pDocument;
}