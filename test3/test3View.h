// test3View.h : interface of the Ctest3View class
//


#pragma once


class Ctest3View : public CView
{
protected: // create from serialization only
	Ctest3View();
	DECLARE_DYNCREATE(Ctest3View)

// Attributes
public:
	Ctest3Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~Ctest3View();
	void FindMaxAndMin(double &max, double &min, double* theor, double* emp, int lenCurrent);
	void DrawRectangles(int color, double* arrayCurrent, int lenCurrent, double max, int flag);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDrawHistogram();
	afx_msg void OnDrawP();
public:
	void Draw_Plevel(double* p_array);
public:
	void DrawByPen(void);
public:
	void Hist_Discription(CDC* pDC);
public:
	void Pvalue_Discription(CDC* pDC);
public:
	void DrawMinAndMax_Y(double max, double min);
	void DrawMinAndMax_X(double max, double min);
public:
	void DrawTable(void);
public:
	afx_msg void OnDrawTable();
public:
	void Table_Discription(CDC* pDC);
};

#ifndef _DEBUG  // debug version in test3View.cpp
inline Ctest3Doc* Ctest3View::GetDocument() const
   { return reinterpret_cast<Ctest3Doc*>(m_pDocument); }
#endif

