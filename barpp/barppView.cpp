// barpp
// Dominik Cebula
// dominikcebula@gmail.com
// This file is part of the barpp project,
// licensed under GPLv2

// barppView.cpp : implementation of the CbarppView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "barpp.h"
#endif

#include "barppDoc.h"
#include "barppView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CbarppView

IMPLEMENT_DYNCREATE(CbarppView, CView)

BEGIN_MESSAGE_MAP(CbarppView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTON_GENERATE, &CbarppView::OnButtonGenerate)
	ON_COMMAND(ID_BUTTON_RECOGNIZE, &CbarppView::OnButtonRecognize)
END_MESSAGE_MAP()

// CbarppView construction/destruction

CbarppView::CbarppView()
{
	// TODO: add construction code here

}

CbarppView::~CbarppView()
{
}

BOOL CbarppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CbarppView drawing

void CbarppView::OnDraw(CDC* pDC)
{
	CbarppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CImage* img=pDoc->img;
	if (img!=NULL) {
		RECT rect;
		this->GetClientRect(&rect);
		
		img->Draw(*pDC, 
			      rect.right/2-img->GetWidth()/2, 
				  rect.bottom/2-img->GetHeight()/2);
	}
}

void CbarppView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	//ClientToScreen(&point);
	//OnContextMenu(this, point);
}

void CbarppView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CbarppView diagnostics

#ifdef _DEBUG
void CbarppView::AssertValid() const
{
	CView::AssertValid();
}

void CbarppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CbarppDoc* CbarppView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CbarppDoc)));
	return (CbarppDoc*)m_pDocument;
}
#endif //_DEBUG


// CbarppView message handlers

void CbarppView::HandleAction(CString in_data, BarType type, ActionType action)
{
	bool freeData=false;
	void* data=NULL;
	unsigned long long int code=0;
	if (action==atGenerate) {
		if (type>btEAN8) {
			data=new char[in_data.GetLength()+1];
			freeData=true;
			strncpy_s(static_cast<char*>(data),
					  in_data.GetLength()+1, 
					  in_data,
					  in_data.GetLength());
		}
		else {
			for (int i=0;i<in_data.GetLength();i++) {
				code+=in_data[i]-'0';
				code*=10;
			}
			code/=10;
			data=&code;
		}
	}

	try {
		if (action==atGenerate)
			this->GetDocument()->GenerateBar(type, data);
		else {
			CString recognize=this->GetDocument()->RecognizeBar(type);
			CFrameWndEx* frame=dynamic_cast<CFrameWndEx*>(this->GetParentFrame());
			CMFCRibbonEdit* edit=dynamic_cast<CMFCRibbonEdit*>(frame->GetRibbonBar()->FindByID(ID_EDIT_RECOGNIZE));
			edit->SetEditText(recognize);
		}
		this->RedrawWindow();
	}
	catch (std::exception& exp) {
		AfxMessageBox(exp.what());
	}
	catch(...) {
		AfxMessageBox("Unknow exception");
	}

	if (data!=NULL && freeData)
		delete[] data;
}

void CbarppView::OnButtonGenerate()
{
	CFrameWndEx* frame=dynamic_cast<CFrameWndEx*>(this->GetParentFrame());
	ASSERT(frame!=NULL);
	
	CMFCRibbonEdit* edit=dynamic_cast<CMFCRibbonEdit*>(frame->GetRibbonBar()->FindByID(ID_EDIT_GENERATE));
	ASSERT(edit!=NULL);

	CMFCRibbonComboBox* comboBox=dynamic_cast<CMFCRibbonComboBox*>(frame->GetRibbonBar()->FindByID(ID_COMBO_GENERATE));	
	ASSERT(comboBox!=NULL);
	BarType type=static_cast<BarType>(comboBox->GetCurSel());

	if (edit->GetEditText().GetLength()==0) {
		AfxMessageBox("Empty barcode is not allowed");
		return;
	}

	this->HandleAction(edit->GetEditText(),
					   type,
					   atGenerate);
}


void CbarppView::OnButtonRecognize()
{
	CFrameWndEx* frame=dynamic_cast<CFrameWndEx*>(this->GetParentFrame());
	ASSERT(frame!=NULL);
	
	CMFCRibbonEdit* edit=dynamic_cast<CMFCRibbonEdit*>(frame->GetRibbonBar()->FindByID(ID_EDIT_RECOGNIZE));
	ASSERT(edit!=NULL);

	CMFCRibbonComboBox* comboBox=dynamic_cast<CMFCRibbonComboBox*>(frame->GetRibbonBar()->FindByID(ID_COMBO_RECOGNIZE));
	ASSERT(comboBox!=NULL);
	BarType type=static_cast<BarType>(comboBox->GetCurSel());

	this->HandleAction(edit->GetEditText(),
					   type,
					   atRecognize);
}
