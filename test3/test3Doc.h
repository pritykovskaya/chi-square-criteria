// test3Doc.h : interface of the Ctest3Doc class
//


#pragma once
#include "Distribution.h"
#include "Sample.h"
#include "Histogram.h"
#include "Settings.h"
#include "ParametrsDlg.h"


class Ctest3Doc : public CDocument
{
protected: // create from serialization only
	Ctest3Doc();
	DECLARE_DYNCREATE(Ctest3Doc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~Ctest3Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

public:
	Sample* s;
	Distribution d0, d1;
	Histogram* h;
	double *time_array1;
	double *time_array2;
	double *time_array3;

	void Simulate(void);
	int method;
	int pvalvol;
	double *pval_freq_array;
	afx_msg void OnSettings();
	
	// parametr-tiem link;

	int tsample_size;
	int tsample_amount;
	double lambda_min;
	double lambda_max;
	int numb_of_steps;
//	int tmethod;

	void create_pvalue_array(void);
	void set_time_array(void);
public:
	int what_on_screen_now;
public:
	afx_msg void OnTime();
};


