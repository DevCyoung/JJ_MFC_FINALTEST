
// MainFrm.h: CMainFrame 클래스의 인터페이스
//

#pragma once

#include "JJ_FIN_TESTDoc.h"


class CMainFrame : public CFrameWnd
{
	
protected: // serialization에서만 만들어집니다.
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// 특성입니다.
public:

// 작업입니다.
public:
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;


	CComboBox colorBox;
	CComboBox pixelBox;
	
	

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 컨트롤 모음이 포함된 멤버입니다.

	

	BOOL CMainFrame::AddCombo(CToolBar* pToolBar, CComboBox* pComboBox, int nIndex, int cx, int cy, DWORD dwStyle, UINT nID);


// 생성된 메시지 맵 함수
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	afx_msg void OnSelectClorBox();
	afx_msg void OnSelectPixelBox();


	DECLARE_MESSAGE_MAP()

};


