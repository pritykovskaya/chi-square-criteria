#pragma once


// CParametrsDlg dialog

class CParametrsDlg : public CDialog
{
	DECLARE_DYNAMIC(CParametrsDlg)

public:
	CParametrsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CParametrsDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int tsample_size;
public:
	int tsample_amount;
public:
	double lambda_min;
public:
	double lambda_max;
public:
	int numb_of_steps;
};
