// barpp
// Dominik Cebula
// dominikcebula@gmail.com
// This file is part of the barpp project,
// licensed under GPLv2

#pragma once


// CInputBox dialog

class CInputEan13 : public CDialog
{
	DECLARE_DYNAMIC(CInputEan13)

private:
	CString val;
public:
	CInputEan13(CWnd* pParent = NULL);   // standard constructor
	virtual ~CInputEan13();

// Dialog Data
	enum { IDD = IDD_INPUTEAN13 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

	int GetFirstDigit();
};
