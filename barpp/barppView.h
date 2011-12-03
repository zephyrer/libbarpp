// barpp
// Dominik Cebula
// dominikcebula@gmail.com
// This file is part of the barpp project,
// licensed under GPLv2

// barppView.h : interface of the CbarppView class
//

#pragma once

enum ActionType {
	atGenerate,
	atRecognize
};

class CbarppView : public CView
{
protected: // create from serialization only
	CbarppView();
	DECLARE_DYNCREATE(CbarppView)

// Attributes
public:
	CbarppDoc* GetDocument() const;

// Operations
private:
	void HandleAction(CString in_data, BarType type, ActionType action);
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CbarppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnButtonGenerate();
	afx_msg void OnButtonRecognize();
};

#ifndef _DEBUG  // debug version in barppView.cpp
inline CbarppDoc* CbarppView::GetDocument() const
   { return reinterpret_cast<CbarppDoc*>(m_pDocument); }
#endif

