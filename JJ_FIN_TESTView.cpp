
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


//	ON_WM_PAINT()
ON_WM_TIMER()
END_MESSAGE_MAP()

int CJJFINTESTView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}


// CJJFINTESTView 생성/소멸

CJJFINTESTView::CJJFINTESTView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	isDraw = TRUE;
}

CJJFINTESTView::~CJJFINTESTView()
{
}

BOOL CJJFINTESTView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.
	return CView::PreCreateWindow(cs);
}

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
	backGround.CreateSolidBrush(RGB(255, 255, 255));
	memDC.CreateCompatibleDC(pDC);
	memBitmap.CreateCompatibleBitmap(pDC, clientRect.right, clientRect.bottom);
	CBitmap* pOldBitmap = (CBitmap*)memDC.SelectObject(&memBitmap);
	memDC.FillRect( &clientRect, &backGround );
	/// Double buffering
	/// ///////////////////////////////////////////////////////////////////




	// 모든 그림은 memDC 에서 그린다.
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.


	

	

	

	//pre Draw
	figureManager.AllDraw(memDC);
	
	DrawFigure(x1, y1, x2, y2, memDC);

	//cur Draw





	/// ///////////////////////////////////////////////////////////////////
	/// Double buffering
	pDC->BitBlt(0, 0, clientRect.right, clientRect.bottom, &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOldBitmap);
	ReleaseDC(&memDC);
	/// Double buffering
	/// ///////////////////////////////////////////////////////////////////


}


// CJJFINTESTView 인쇄




#ifdef _DEBUG
// CJJFINTESTView 진단
void CJJFINTESTView::AssertValid() const
{
	CView::AssertValid();
}

void CJJFINTESTView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CJJFINTESTDoc* CJJFINTESTView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CJJFINTESTDoc)));
	return (CJJFINTESTDoc*)m_pDocument;
}


//////////////////////////////////////////////
//여기서부터 사용자가 생성하였습니다.
//////////////////////////////////////////////
void CJJFINTESTView::DrawFigure(int x1, int y1, int x2, int y2, CDC& dc)
{
	

	CPen pen;
	pen.CreatePen(PS_DOT, curPixel, curColor );    // 빨간색 펜을 생성
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
	dc.SelectObject(oldBrush);    // 시스템 브러시 객체를 돌려줌


}

//////////////////////////////////////////////
// CJJFINTESTView 메시지 처리기
//////////////////////////////////////////////
void CJJFINTESTView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	// 그리기 모드이면 타원을 지우고 그리기를 반복한다.

	if (isDraw) {

		CClientDC dc(this);
		dc.SelectStockObject(NULL_BRUSH);
		// 이전에 그린 타원을 지운다.
		dc.SetROP2(R2_NOT);

		/*DrawFigure(x1, y1, x2, y2, dc);*/

		// 새로운 타원을 그린다.
		dc.SetROP2(R2_NOT);
		x2 = point.x;
		y2 = point.y;

		/*DrawFigure(x1, y1, x2, y2, dc);*/
		Invalidate(FALSE);
	}
}
void CJJFINTESTView::OnLButtonDown(UINT nFlags, CPoint point)
{

	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	// 그리기 모드를 시작한다.
	isDraw = TRUE;
	// 좌표를 저장한다.
	x1 = x2 = point.x;
	y1 = y2 = point.y;

}
void CJJFINTESTView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CClientDC dc(this);
	dc.SelectStockObject(NULL_BRUSH);
	// 최종적인 타원을 그린다.
	dc.SetROP2(R2_COPYPEN);
	x2 = point.x;
	y2 = point.y;


	/*DrawFigure(x1, y1, x2, y2, dc);*/


	// 그리기 모드를 끝낸다.
	isDraw = FALSE;

	// SaveData
	figureManager.NextFigure(x1,y1,x2,y2,curColor , curPixel , curButton);

	/*SaveFigure(x1, y1, x2, y2, curButton);*/


}



















void CJJFINTESTView::SaveFigure(int x1, int y1, int x2, int y2, Button figure)
{

	//figurePointes[figureCount][0] = x1;
	//figurePointes[figureCount][1] = y1;
	//figurePointes[figureCount][2] = x2;
	//figurePointes[figureCount][3] = y2;
	//figurePointes[figureCount][4] = figure;
	//++figureCount;


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

void CJJFINTESTView::OnTimer(UINT_PTR nIDEvent)
{
	CView::OnTimer(nIDEvent);
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