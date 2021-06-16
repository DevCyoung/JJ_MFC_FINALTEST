// Figure.cpp: 구현 파일
#include "pch.h"
#include "JJ_FIN_TEST.h"
#include "Figure.h"

IMPLEMENT_DYNAMIC(Figure, CWnd)

Figure::Figure(){}
Figure::~Figure(){}

void Figure::SetInit(int x1, int y1, int x2, int y2, COLORREF color, int curPixel, int figure ,BOOL isFill)
{

	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
	this->color = color;
	this->pixel = curPixel;
	this->figure = figure;
	this->isFill = isFill;
	this->isAlive = true;

}
void Figure::SetPosition(int x1, int y1, int x2, int y2)
{
	if (isAlive == false)
		return;

	this->x1 = x1;
	this->y1 = y1;
	this->x2 = x2;
	this->y2 = y2;
}
void Figure::Show(CDC& pDC)
{
	if (isAlive == false)
		return;

	CPen pen;
	CBrush brush;

	pen.CreatePen(PS_DOT, pixel, color);    
	CPen* oldPen = pDC.SelectObject(&pen);
	

	if (isFill == FALSE)
	{
		pDC.SelectStockObject(NULL_BRUSH);
	}
	else
	{
		brush.CreateSolidBrush( color );
	}

	CBrush* oldBrush = pDC.SelectObject(&brush);


	if (figure == CIRCLE)
	{
		pDC.Ellipse(x1, y1, x2, y2);
	}
	else if (figure == RECTANGLE)
	{
		pDC.Rectangle(x1, y1, x2, y2);
	}

	pDC.SelectObject(oldBrush);
	pDC.SelectObject(oldPen);     // 시스템 펜 객체를 돌려줌
	
}

BEGIN_MESSAGE_MAP(Figure, CWnd)
END_MESSAGE_MAP()