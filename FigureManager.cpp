// FigureManager.cpp: 구현 파일
#include "pch.h"
#include "JJ_FIN_TEST.h"
#include "FigureManager.h"

IMPLEMENT_DYNAMIC(FigureManager, CWnd)

FigureManager::FigureManager(){}
FigureManager::~FigureManager(){}

void FigureManager::AllDraw(CDC& pDC)
{

	for (int i = 0; i < FIGURE_PULL; i++)
	{
		figures[i].Show(pDC);
	}

}
void FigureManager:: NextFigure(int x1, int y1, int x2, int y2, COLORREF color, int curPixel, int figure , BOOL isFill)
{

	figures[curPos].SetInit(x1, y1,  x2,  y2,  color,  curPixel,  figure , isFill);
	++curPos;

	// 일정 FIGURE_PULL 이상 증가시 처음도형을 없앱니다.
	if (curPos >= FIGURE_PULL)
	{
		curPos = 0;
	}

}

BEGIN_MESSAGE_MAP(FigureManager, CWnd)
END_MESSAGE_MAP()


