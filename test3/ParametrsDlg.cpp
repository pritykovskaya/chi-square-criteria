// ParametrsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "test3.h"
#include "ParametrsDlg.h"


// CParametrsDlg dialog

IMPLEMENT_DYNAMIC(CParametrsDlg, CDialog)

CParametrsDlg::CParametrsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CParametrsDlg::IDD, pParent)
	, tsample_size(100)
	, tsample_amount(1000)
	, lambda_min(1)
	, lambda_max(20)
	, numb_of_steps(20)
{

}

CParametrsDlg::~CParametrsDlg()
{
}

void CParametrsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, tsample_size);
	DDV_MinMaxInt(pDX, tsample_size, 0, 100000);
	DDX_Text(pDX, IDC_EDIT3, tsample_amount);
	DDV_MinMaxInt(pDX, tsample_amount, 0, 100000);
	DDX_Text(pDX, IDC_EDIT2, lambda_min);
	DDV_MinMaxDouble(pDX, lambda_min, 0, 1000);
	DDX_Text(pDX, IDC_EDIT4, lambda_max);
	DDV_MinMaxDouble(pDX, lambda_max, 0, 1000);
	DDX_Text(pDX, IDC_EDIT5, numb_of_steps);
	
}


BEGIN_MESSAGE_MAP(CParametrsDlg, CDialog)
END_MESSAGE_MAP()


// CParametrsDlg message handlers
