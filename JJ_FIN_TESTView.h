
// JJ_FIN_TESTView.h: CJJFINTESTView 클래스의 인터페이스
//

#pragma once

#include "FigureManager.h"


enum Button
{
	NONE = 0,
	CIRCLE = 1,
	RECTANGLE = 2,
	PRINT = 3,
};


class CJJFINTESTView : public CView
{
protected: // serialization에서만 만들어집니다.
	CJJFINTESTView() noexcept;
	DECLARE_DYNCREATE(CJJFINTESTView)

// 특성입니다.
public:
	CJJFINTESTDoc* GetDocument() const;

// 작업입니다.
public:

	const int fixels[3] = { 1 , 5 , 10 };
	const COLORREF colors[3] = { RGB(255, 0, 0)  , RGB(0, 0, 255) , RGB(0, 255, 0) };

	COLORREF curColor = RGB(255, 0, 0);
	int curPixel = 1;

	BOOL isDraw; 
	int x1, y1, x2, y2; 

	CButton circle;
	CButton rectangle;
	CButton print;
	CButton clear;

	Button curButton = NONE;

	FigureManager figureManager;

	
	int figureCount = 0;
	
	void DrawFigure(int x1, int y1, int x2, int y2, CDC& dc);
	


	void SetColor(int sel);
	void SetPixel(int sel);
	



// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
//	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CJJFINTESTView();
#ifdef _DEBUG
//	virtual void AssertValid() const;
//	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

public:
	

public:
	
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	// 사용자 정의입니다.

	afx_msg void OnClickCircle();
	afx_msg void OnClickRECTANGLE();

	afx_msg void OnClickPreViewPrint();

	// MFC 정의
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);


	


//	afx_msg void OnPaint();
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // JJ_FIN_TESTView.cpp의 디버그 버전
inline CJJFINTESTDoc* CJJFINTESTView::GetDocument() const
   { return reinterpret_cast<CJJFINTESTDoc*>(m_pDocument); }
#endif

