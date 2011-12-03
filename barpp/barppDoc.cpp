// barpp
// Dominik Cebula
// dominikcebula@gmail.com
// This file is part of the barpp project,
// licensed under GPLv2

// barppDoc.cpp : implementation of the CbarppDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "barpp.h"
#endif

#include "barppDoc.h"
#include <BarBitmapWin32.h>
#include <BarGeneratorEan13.h>
#include <BarGeneratorEan8.h>
#include <BarGeneratorCode128.h>
#include <BarGeneratorCode93.h>
#include <BarGeneratorCode39.h>
#include <BarGeneratorCode25.h>
#include <BarReaderEan13.h>
#include <BarReaderEan8.h>
#include <BarReaderCode128.h>
#include <BarReaderCode93.h>
#include <BarReaderCode39.h>
#include <BarReaderCode25.h>

#include "InputEan13.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CbarppDoc

IMPLEMENT_DYNCREATE(CbarppDoc, CDocument)

BEGIN_MESSAGE_MAP(CbarppDoc, CDocument)
END_MESSAGE_MAP()


// CbarppDoc construction/destruction

CbarppDoc::CbarppDoc()
{
	img=NULL;
}

CbarppDoc::~CbarppDoc()
{
	if (img!=NULL) {
		delete img;
		img=NULL;
	}
}

BOOL CbarppDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	if (img!=NULL) {
		delete img;
		img=NULL;
	}

	return TRUE;
}

// CbarppDoc serialization

void CbarppDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
	}
	else
	{
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CbarppDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CbarppDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CbarppDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CbarppDoc diagnostics

#ifdef _DEBUG
void CbarppDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CbarppDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CbarppDoc commands

CBarGenerator* CbarppDoc::GetGenFromType(BarType type, CBarBitmap* bmp)
{
	switch(type) {
	case btEAN13:
		return new CBarGeneratorEan13(bmp);
		break;
	case btEAN8:
		return new CBarGeneratorEan8(bmp);
		break;
	case btCode128:
		return new CBarGeneratorCode128(bmp);
		break;
	case btCode93:
		return new CBarGeneratorCode93(bmp);
		break;
	case btCode39:
		return new CBarGeneratorCode39(bmp);
		break;
	case btCode25:
		return new CBarGeneratorCode25(bmp);
		break;
	}
	throw std::exception("Unknow code type");
}

CString CbarppDoc::GetBmpTemp()
{
	CString temp;
	GetTempPath(255, temp.GetBuffer(255));
	temp.ReleaseBuffer();
	temp+="barpp_temp.bmp";
	return temp;
}

void CbarppDoc::GenerateBar(BarType type, void* data)
{
	CString temp=GetBmpTemp();
	
	CBarBitmapWin32 bmp;
	CBarGenerator* gen=NULL;
	try {
		gen=GetGenFromType(type, &bmp);
		if (gen==NULL)
			throw new std::exception("Could not get barcode type");
		gen->Generate(data);
		bmp.Save((char*)(const char*)temp);

		if (img!=NULL) {
			delete img;
			img=NULL;
		}
		img=new CImage();
		img->Load(temp);
	}
	catch (std::exception& exp) {
		AfxMessageBox(exp.what());
	}
	catch (std::exception* exp) {
		AfxMessageBox(exp->what());
		delete exp;
	}
	catch (...) {
		AfxMessageBox("Unknow exception");
	}

	if (gen!=NULL)
		delete gen;
}

CString CbarppDoc::RecognizeBar(BarType type)
{
	if (img==NULL) {
		AfxMessageBox("First you need to have an opened document");
		return "";
	}

	CBarBitmapWin32 bmp;
	CString temp=GetBmpTemp();
	CString ret;
	CBarReaderEan13* ean13=NULL;
	CBarReaderEan8* ean8=NULL;
	CBarReaderCode128* code128=NULL;
	CBarReaderCode93* code93=NULL;
	CBarReaderCode39* code39=NULL;
	CBarReaderCode25* code25=NULL;

	try {
		int firstDigit;
		char* lp;
		lp=(char*)(const char*)temp;
		std::string tmp;	
		img->Save(temp);
		bmp.Load(lp);

		switch (type) {
		case btEAN13:
			ean13=new CBarReaderEan13(&bmp);
			firstDigit=-1;
			{
				CInputEan13 inputEan13(AfxGetMainWnd());
				if (inputEan13.DoModal()==IDOK)
					firstDigit=inputEan13.GetFirstDigit();
				else
					throw std::exception("First digit is required");
			}
			tmp=ean13->read(firstDigit);
			ret=tmp.c_str();
			break;
		case btEAN8:
			ean8=new CBarReaderEan8(&bmp);
			tmp=ean8->read();
			ret=tmp.c_str();
			break;
		case btCode128:
			code128=new CBarReaderCode128(&bmp);
			tmp=code128->read();
			ret=tmp.c_str();
			break;
		case btCode93:
			code93=new CBarReaderCode93(&bmp);
			tmp=code93->read();
			ret=tmp.c_str();
			break;
		case btCode39:
			code39=new CBarReaderCode39(&bmp);
			tmp=code39->read();
			ret=tmp.c_str();
			break;
		case btCode25:
			code25=new CBarReaderCode25(&bmp);
			tmp=code25->read();
			ret=tmp.c_str();
			break;
		default:
			throw std::exception("Code not supported");
		}		
	}
	catch (std::exception& exp) {
		AfxMessageBox(exp.what());
	}
	catch (std::exception* exp) {
		AfxMessageBox(exp->what());
		delete exp;
	}
	catch (...) {
		AfxMessageBox("Unknow exception");
	}

	if (ean13!=NULL) delete ean13;
	if (ean8!=NULL) delete ean8;
	if (code128!=NULL) delete code128;
	if (code93!=NULL) delete code93;
	if (code39!=NULL) delete code39;
	if (code25!=NULL) delete code25;

	return ret;
}

BOOL CbarppDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	if (img!=NULL) {
		img->Save(lpszPathName);
		return TRUE;
	}
	else {
		return FALSE;
	}
}


BOOL CbarppDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	if (img!=NULL)
		delete img;
	img=new CImage;
	img->Load(lpszPathName);
	((CFrameWndEx*)AfxGetMainWnd())->GetActiveView()->RedrawWindow();

	return TRUE;
}
