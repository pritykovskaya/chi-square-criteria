#pragma once
#include "afxwin.h"


// ���������� ���� Settings


#pragma once


// ���������� ���� Settings

class Settings : public CDialog
{
	DECLARE_DYNAMIC(Settings)

public:
	Settings(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~Settings();

// ������ ����������� ����
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

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
