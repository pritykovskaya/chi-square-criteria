// Settings.cpp: файл реализации
//

#include "stdafx.h"
#include "test3.h"
#include "Settings.h"


// диалоговое окно Settings

IMPLEMENT_DYNAMIC(Settings, CDialog)

Settings::Settings(CWnd* pParent /*=NULL*/)
	: CDialog(Settings::IDD, pParent)
	, Method(0)
	, lam1(0)
	, lam2(0)
	, len1(0)
	, len2(0)
{

}

Settings::~Settings()
{
}

void Settings::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);


	DDX_Radio(pDX, IDC_RADIO1, Method);
	DDX_Text(pDX, IDC_LAMBDA1, lam1);
	DDX_Text(pDX, IDC_LAMBDA2, lam2);
	DDX_Text(pDX, IDC_N1, len1);
	DDX_Text(pDX, IDC_N2, len2);
}


BEGIN_MESSAGE_MAP(Settings, CDialog)
	ON_BN_CLICKED(IDC_RADIO2, &Settings::OnBnClickedRadio2)
END_MESSAGE_MAP()


// обработчики сообщений Settings

void Settings::OnBnClickedRadio2()
{
	// TODO: Add your control notification handler code here
}
