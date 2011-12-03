// barpp
// Dominik Cebula
// dominikcebula@gmail.com
// This file is part of the barpp project,
// licensed under GPLv2

// InputBox.cpp : implementation file
//

#include "stdafx.h"
#include "barpp.h"
#include "InputEan13.h"
#include "afxdialogex.h"


// CInputBox dialog

IMPLEMENT_DYNAMIC(CInputEan13, CDialog)

CInputEan13::CInputEan13(CWnd* pParent /*=NULL*/)
	: CDialog(CInputEan13::IDD, pParent)
{

}

CInputEan13::~CInputEan13()
{
}

void CInputEan13::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInputEan13, CDialog)
	ON_BN_CLICKED(IDOK, &CInputEan13::OnBnClickedOk)
END_MESSAGE_MAP()


// CInputBox message handlers
int CInputEan13::GetFirstDigit()
{
	return val[0]-'0';
}

void CInputEan13::OnBnClickedOk()
{
	CEdit* edit=static_cast<CEdit*>(this->GetDlgItem(IDE_INPUT_EAN13));
	edit->GetWindowText(val);
	if (val.GetLength()!=1 ||
		val[0]<'0' ||
		val[0]>'9') {
		AfxMessageBox("One digit 0-9 is required");
		return;
	}

	CDialog::OnOK();
}
