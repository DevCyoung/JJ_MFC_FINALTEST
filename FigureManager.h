#pragma once
#include "Figure.h"
// FigureManager
#define FIGURE_PULL 10000

class FigureManager : public CWnd
{
	DECLARE_DYNAMIC(FigureManager)

public:
	FigureManager();
	virtual ~FigureManager();

public:
	Figure figures[FIGURE_PULL];
	int curPos = 0;

public:
	void AllDraw(CDC &pDC);
	void NextFigure(int x1, int y1, int x2, int y2, COLORREF color, int curPixel, int figure);


protected:
	DECLARE_MESSAGE_MAP()
};


