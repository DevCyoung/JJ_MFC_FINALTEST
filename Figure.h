#pragma once

// Figure
class Figure : public CWnd
{
	DECLARE_DYNAMIC(Figure)

public:
	Figure();
	virtual ~Figure();

public:

	int const CIRCLE = 1;
	int const RECTANGLE = 2;

	int x1, y1, x2, y2;
	BOOL isAlive = FALSE;

	COLORREF color;
	int pixel;
	int figure;
	
public:
	void SetInit(int x1, int y1, int x2, int y2, COLORREF color, int curPixel, int figure);
	void SetPosition(int x1, int y1, int x2, int y2);
	void Show(CDC& pDC);
		

protected:
	DECLARE_MESSAGE_MAP()
};


