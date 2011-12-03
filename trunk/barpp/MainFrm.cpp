// barpp
// Dominik Cebula
// dominikcebula@gmail.com
// This file is part of the libbarpp project,
// licensed under GPLv2

// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "barpp.h"

#include "MainFrm.h"

#include <BarGeneratorEan13.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_COMBO_GENERATE, &CMainFrame::OnUpdateEnable)
	ON_UPDATE_COMMAND_UI(ID_EDIT_GENERATE, &CMainFrame::OnUpdateEnable)
	ON_UPDATE_COMMAND_UI(ID_COMBO_RECOGNIZE, &CMainFrame::OnUpdateEnable)
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	//BOOL bNameValid;

	// set the visual manager used to draw all user interface elements
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);
	m_wndRibbonBar.EnableKeyTips(0);

	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);
	
	dynamic_cast<CMFCRibbonComboBox*>(m_wndRibbonBar.FindByID(ID_COMBO_GENERATE))->SelectItem(0);
	dynamic_cast<CMFCRibbonComboBox*>(m_wndRibbonBar.FindByID(ID_COMBO_RECOGNIZE))->SelectItem(0);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers

void CMainFrame::OnUpdateEnable(CCmdUI *pCmdUI)
{
	pCmdUI->Enable();
}
