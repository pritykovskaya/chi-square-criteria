#pragma once
#include "afxwin.h"


// диалоговое окно Settings


#pragma once


// диалоговое окно Settings

class Settings : public CDialog
{
	DECLARE_DYNAMIC(Settings)

public:
	Settings(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~Settings();

// Данные диалогового окна
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	
	int Method;
	int lam1;
	int lam2;
	int len1;
	int len2;
public:
	afx_msg void OnBnClickedRadio2();
};
