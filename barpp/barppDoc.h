// barpp
// Dominik Cebula
// dominikcebula@gmail.com
// This file is part of the barpp project,
// licensed under GPLv2

// barppDoc.h : interface of the CbarppDoc class
//

#include <BarGenerator.h>
#include <BarReader.h>

#pragma once

enum BarType {
	btEAN13=0,
	btEAN8=1,
	btCode128=2,
	btCode93=3,
	btCode39=4,
	btCode25=5
};

class CbarppDoc : public CDocument
{
protected: // create from serialization only
	CbarppDoc();
	DECLARE_DYNCREATE(CbarppDoc)

// Attributes
public:
	CImage* img;

// Operations
private:
	CString GetBmpTemp();
	CBarGenerator* GetGenFromType(BarType type, CBarBitmap* bmp);
public:
	void GenerateBar(BarType type, void* data);
	CString RecognizeBar(BarType type);

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CbarppDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:	
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
};
