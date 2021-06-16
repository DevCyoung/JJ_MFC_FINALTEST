
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

	//추가할 콤보박스
	CComboBox colorBox;
	CComboBox pixelBox;
	
// 재정의입니다.
public:

public:
	virtual ~CMainFrame();
#ifdef _DEBUG

#endif

protected: 
	//콤보박스 추가
	BOOL CMainFrame::AddCombo(CToolBar* pToolBar, CComboBox* pComboBox, int nIndex, int cx, int cy, DWORD dwStyle, UINT nID);


// 생성된 메시지 맵 함수
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	//콤보박스 선택시 호출
	afx_msg void OnClorCheckBox();
	afx_msg void OnPixelCheckBox();


	DECLARE_MESSAGE_MAP()

};


