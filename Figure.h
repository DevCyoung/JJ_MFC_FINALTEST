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
	BOOL isAlive = false;

	COLORREF color;
	int pixel;
	int figure;
	

public:
	void SetInit(int x1, int y1, int x2, int y2, COLORREF color, int curPixel  ,int figure)
	{
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
		this->color = color;
		this->pixel = curPixel;
		this->figure = figure;
		this->isAlive = true;

	}
	void SetPosition(int x1, int y1, int x2, int y2)
	{
		if (isAlive == false)
			return;

		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
	}
	void Show(CDC& pDC)
	{
		if (isAlive == false)
			return;

		CPen pen;
		pen.CreatePen(PS_DOT, pixel, color);    // ª°∞£ªˆ ∆Ê¿ª ª˝º∫
		CPen* oldPen = pDC.SelectObject(&pen);
		CBrush brush;
		CBrush* oldBrush = pDC.SelectObject(&brush);
		pDC.SelectStockObject(NULL_BRUSH);
		if (figure == CIRCLE)
		{
			pDC.Ellipse(x1, y1, x2, y2);
		}
		else if (figure == RECTANGLE)
		{
			pDC.Rectangle(x1, y1, x2, y2);
		}

		pDC.SelectObject(oldBrush);
		pDC.SelectObject(oldPen);     // Ω√Ω∫≈€ ∆Ê ∞¥√º∏¶ µπ∑¡¡‹
		pDC.SelectObject(oldBrush);    // Ω√Ω∫≈€ ∫Í∑ØΩ√ ∞¥√º∏¶ µπ∑¡¡‹

	}


protected:
	DECLARE_MESSAGE_MAP()
};


