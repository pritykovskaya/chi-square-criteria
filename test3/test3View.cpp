// test3View.cpp : implementation of the Ctest3View class
//

#include "stdafx.h"
#include "test3.h"

#include "test3Doc.h"
#include "test3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ctest3View

IMPLEMENT_DYNCREATE(Ctest3View, CView)

BEGIN_MESSAGE_MAP(Ctest3View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_DRAW_HISTOGRAM, &Ctest3View::OnDrawHistogram)
	ON_COMMAND(ID_DRAW_P, &Ctest3View::OnDrawP)
	ON_COMMAND(ID_DRAW_TABLE, &Ctest3View::OnDrawTable)
END_MESSAGE_MAP()

// Ctest3View construction/destruction

Ctest3View::Ctest3View()
{
	// TODO: add construction code here

}

Ctest3View::~Ctest3View()
{
}

BOOL Ctest3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Ctest3View drawing

void Ctest3View::OnDraw(CDC* pDC)
{
	Ctest3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
//	pDoc->Simulate();
//	pDoc->create_pvalue_array();
	double max;
	double min;
	
	int k = 0;
	if (pDoc->what_on_screen_now != 0 ){
		if ( pDoc->what_on_screen_now == 1){
			FindMaxAndMin(max, min, pDoc->h->getthr(), pDoc->h->getemp(), pDoc->h->getsize());
			DrawRectangles(RGB(242, 89, 0), pDoc->h->getthr(), pDoc->h->getsize(), max, 1);
			DrawRectangles(RGB(255, 251, 0), pDoc->h->getemp(), pDoc->h->getsize(), max, 0);		
			Hist_Discription(pDC);
			DrawMinAndMax_Y(max, min);
			min = 0;
			max = pDoc->h->getsize();
			DrawMinAndMax_X(max, min);
		}
		if ( pDoc->what_on_screen_now == 2){
			Draw_Plevel(pDoc->pval_freq_array);
			Pvalue_Discription(pDC);
			max = 1;
			min = 0;
			DrawMinAndMax_Y(max, min);
			DrawMinAndMax_X(max, min);
		}
		if ( pDoc->what_on_screen_now == 3){
			DrawTable();	
			Table_Discription(pDC);
			FindMaxAndMin(max, min, pDoc->time_array1, pDoc->time_array2, pDoc->numb_of_steps);
			DrawMinAndMax_Y(max, min);
			DrawMinAndMax_X(pDoc->lambda_max, pDoc->lambda_min);
		}
	}

// UDALIT!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//	delete  emp;
	//delete [] theor;
}


// Ctest3View printing

BOOL Ctest3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void Ctest3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Ctest3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// Ctest3View diagnostics

#ifdef _DEBUG
void Ctest3View::AssertValid() const
{
	CView::AssertValid();
}

void Ctest3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Ctest3Doc* Ctest3View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Ctest3Doc)));
	return (Ctest3Doc*)m_pDocument;
}
#endif //_DEBUG


// Ctest3View message handlers
void Ctest3View::FindMaxAndMin(double &max, double &min, double* array1, double* array2, int lenCurrent)
{
	max = array1[0];
	min = array2[0];
	for (int i = 0; i < lenCurrent; ++i) {
		if (min > array1[i]) { min = array1[i];}
		if (min > array2[i]) { min = array2[i];}
		if (max < array1[i]) { max = array1[i];}
		if (max < array2[i]) { max = array2[i];}

	}
	// TODO: Add your command handler code here
}
void Ctest3View::DrawRectangles(int color, double* arrayCurrent, int lenCurrent, double max, int flag)
{
	CClientDC dc(this);
	
	LOGBRUSH logBrush;
	logBrush.lbColor = color;
	logBrush.lbStyle = BS_SOLID;
	logBrush.lbHatch = HS_CROSS;
	
	CBrush brushCurrent;
	brushCurrent.CreateBrushIndirect(&logBrush);
	CBrush* pOldBrush = (CBrush*) dc.SelectObject(&brushCurrent);
	CRect rc;
	GetClientRect(&rc);
	int W=rc.Width();
	int H=rc.Height();
	CPen penCurrent;

	penCurrent.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	CPen* pOldPen = (CPen *) dc.SelectObject( &penCurrent);
	dc.MoveTo(0.1*W, 0.9*H);
	dc.LineTo( 0.1*W, 0.2*H);
	dc.MoveTo(0.1*W, 0.9*H);
	dc.LineTo( 0.9*W, 0.9*H);
	dc.SelectObject(pOldPen);
	penCurrent.DeleteObject();
	
	double between;
	double width;
	if ( flag == 0){
		between = 0.8*W/(4*lenCurrent);
		width = 0.8*W/(2*lenCurrent);
	}
	else{
		between = 0;
		width = 0.8*W/(lenCurrent);
	}

	for (int i = 0; i < lenCurrent; ++i ) {
		dc.Rectangle(between+ i*(width+2*between) + 0.1*W, 0.9*H, between+(i) * (width+2*between)+width + 0.1*W, 0.9*H - 0.7*H/max * arrayCurrent[i]);
	}

	dc.SelectObject(pOldBrush);
	brushCurrent.DeleteObject();

	// TODO: Add your command handler code here

}
void Ctest3View::OnDrawHistogram()
{
	Ctest3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->what_on_screen_now = 1;
	pDoc->Simulate();
	pDoc->create_pvalue_array();

	Invalidate();
}

void Ctest3View::OnDrawP()
{
	Ctest3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->what_on_screen_now = 2;
	pDoc->Simulate();
	pDoc->create_pvalue_array();
	Invalidate();

}

void Ctest3View::OnDrawTable()
{
	Ctest3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->what_on_screen_now = 3;

	pDoc->set_time_array();
	Invalidate();
	// TODO: Add your command handler code here
}

void Ctest3View::Draw_Plevel(double *p_array)
{
	CClientDC dc(this);
	
	//LOGBRUSH logBrush;
	//logBrush.lbColor = RGB(0, 0, 0);
	//logBrush.lbStyle = BS_SOLID;
	//logBrush.lbHatch = HS_CROSS;
	//
	//CBrush brushCurrent;
	//brushCurrent.CreateBrushIndirect(&logBrush);
	//CBrush* pOldBrush = (CBrush*) dc.SelectObject(&brushCurrent);

	CRect rc;
	GetClientRect(&rc);
	int W=rc.Width();
	int H=rc.Height();

	CPen penCurrent;
	penCurrent.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	CPen* pOldPen = (CPen *) dc.SelectObject( &penCurrent);
	dc.MoveTo(0.1*W, 0.9*H);
	dc.LineTo( 0.1*W, 0.2*H);
	dc.MoveTo(0.1*W, 0.9*H);
	dc.LineTo( 0.9*W, 0.9*H);
	dc.MoveTo(0.1*W, 0.9*H);
	dc.SelectObject(pOldPen);
	penCurrent.DeleteObject();


	
	// change color!
	
	penCurrent.CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	pOldPen = (CPen *) dc.SelectObject( &penCurrent);
	dc.LineTo(0.9*W, 0.2*H);
	dc.MoveTo(0.1*W, 0.9*H);
	dc.SelectObject(pOldPen);
	penCurrent.DeleteObject();

	// change color again!

	penCurrent.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	pOldPen = (CPen *) dc.SelectObject( &penCurrent);
	for (int i = 0; i < 20; ++i) {
		dc.LineTo((0.8*W)/20*(i+1) + 0.1*W, 0.9*H - p_array[i]*0.7*H);
	}
	dc.SelectObject(pOldPen);
	penCurrent.DeleteObject();
	
}

void Ctest3View::DrawByPen(void)
{
	
}

void Ctest3View::Hist_Discription(CDC* pDC)
{
	Ctest3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CFont font;
	LOGFONT lf;
	memset( &lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 20;
	strcpy(lf.lfFaceName, "Tahoma");
	font.CreateFontIndirect(&lf);
	CFont* def_font = pDC->SelectObject(&font);

	char str[1000];
	pDoc->h->CalcChi();
	if (pDoc->method == 0) {
		sprintf(str, "Inverse_function, lambda =%d, sample size = %d, Chi^2 = %-8.4f, freedom degree= %d, P-value = %-8.4f .", pDoc->d0.lambda,pDoc->s->getsize(),pDoc->h->getchi(),pDoc->h->getdf(),pDoc->h->getplevel());
	}
	if (pDoc->method == 1) {
		sprintf(str,"Table, lambda =%d, sample size = %d, Chi^2 = %-8.4f, freedom degree= %d, P-value = %-8.4f .", pDoc->d0.lambda,pDoc->s->getsize(),pDoc->h->getchi(),pDoc->h->getdf(),pDoc->h->getplevel());
	}
	
	CRect rc;
	GetClientRect(&rc);
	int W=rc.Width();
	int H=rc.Height();

	pDC->TextOut(0.1*W, 0.05*H, str);
	pDC->SelectObject(def_font);
	font.DeleteObject();
}

void Ctest3View::Pvalue_Discription(CDC* pDC)
{
	Ctest3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CFont font;
	LOGFONT lf;
	memset( &lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 20;
	strcpy(lf.lfFaceName, "Tahoma");
	font.CreateFontIndirect(&lf);
	CFont* def_font = pDC->SelectObject(&font);

	char str[1000];
	pDoc->h->CalcChi();
	if (pDoc->method == 0) {
		sprintf(str, "Inverse_function, pvalue array size = %d, lambda0 = %d, lambda1 = %d", pDoc->pvalvol, pDoc->d0.lambda, pDoc->d1.lambda);
	}
	if (pDoc->method == 1) {
		sprintf(str,"Table, pvalue array size = %d, lambda0 = %d, lambda1 = %d", pDoc->pvalvol, pDoc->d0.lambda, pDoc->d1.lambda);
	}
	
	CRect rc;
	GetClientRect(&rc);
	int W=rc.Width();
	int H=rc.Height();

	pDC->TextOut(0.1*W, 0.05*H, str);
	pDC->SelectObject(def_font);
	font.DeleteObject();
}

void Ctest3View::DrawMinAndMax_Y(double max, double min)
{
	CClientDC dc(this);
	char str[40];
	
	
	CRect rc;
	GetClientRect(&rc);
	int W=rc.Width();
	int H=rc.Height();

	sprintf(str, "%4.2lf", max);
	dc.TextOut(0.1*W - 30, 0.2*H, str);

	sprintf(str, "%4.2lf", min);
	dc.TextOut(0.1*W - 30, 0.9*H - 15, str);

}

void Ctest3View::DrawMinAndMax_X(double max, double min)
{
	CClientDC dc(this);
	char str[40];
	
	
	CRect rc;
	GetClientRect(&rc);
	int W=rc.Width();
	int H=rc.Height();

	sprintf(str, "%4.2lf", max);
	dc.TextOut(0.9*W + 30, 0.9*H + 15, str);

	sprintf(str, "%4.2lf", min);
	dc.TextOut(0.1*W + 15, 0.9*H + 15, str);

}

void Ctest3View::DrawTable(void)
{

	Ctest3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//pDoc->set_time_array();

	CClientDC dc(this);	
	CRect rc;
	GetClientRect(&rc);
	int W=rc.Width();
	int H=rc.Height();
	CPen penCurrent;
	penCurrent.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	CPen* pOldPen = (CPen *) dc.SelectObject( &penCurrent);
	dc.MoveTo(0.1*W, 0.9*H);
	dc.LineTo( 0.1*W, 0.2*H);
	dc.MoveTo(0.1*W, 0.9*H);
	dc.LineTo( 0.9*W, 0.9*H);
	
	double max = pDoc -> time_array1[0];
	for ( int i = 0; i <= pDoc -> numb_of_steps; ++i){
		if ( pDoc -> time_array1[i] > max){
			max = pDoc -> time_array1[i];
		}
	}
	dc.SelectObject(pOldPen);
	penCurrent.DeleteObject();

	// change color again!

	dc.MoveTo((pDoc->lambda_min)*0.8*W/(pDoc->lambda_max) + 0.1*W, 0.9*H - 0.7*H*(pDoc->time_array1[0]/max));
	penCurrent.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	pOldPen = (CPen *) dc.SelectObject( &penCurrent);
	
	//dc.LineTo((0.8*W/(pDoc->lambda_max))*(pDoc->lambda_max - pDoc->lambda_min)/(pDoc->numb_of_steps)*(1)+0.1*W, 0.9*H - 0.7*H*5*(pDoc->time_array[1]));
	
	for (int i = 1; i <= pDoc->numb_of_steps; ++i) {
		dc.LineTo(((((0.8*W)/(pDoc->lambda_max))*(pDoc->lambda_max - pDoc->lambda_min))/pDoc->numb_of_steps)*i + 0.1*W + (pDoc->lambda_min)*0.8*W/(pDoc->lambda_max), 0.9*H - 0.7*H/max*(pDoc->time_array1[i]));
	}
	
	dc.SelectObject(pOldPen);
	penCurrent.DeleteObject();
	
		max = pDoc -> time_array2[0];
	for ( int i = 0; i <= pDoc -> numb_of_steps; ++i){
		if ( pDoc -> time_array2[i] > max){
			max = pDoc -> time_array2[i];
		}
	}

	dc.MoveTo((pDoc->lambda_min)*0.8*W/(pDoc->lambda_max) + 0.1*W, 0.9*H - 0.7*H/max*(pDoc->time_array2[0]));
	penCurrent.CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	pOldPen = (CPen *) dc.SelectObject( &penCurrent);
	
	//dc.LineTo((0.8*W/(pDoc->lambda_max))*(pDoc->lambda_max - pDoc->lambda_min)/(pDoc->numb_of_steps)*(1)+0.1*W, 0.9*H - 0.7*H*5*(pDoc->time_array[1]));
	
	for (int i = 1; i <= pDoc->numb_of_steps; ++i) {
		dc.LineTo(((((0.8*W)/(pDoc->lambda_max))*(pDoc->lambda_max - pDoc->lambda_min))/pDoc->numb_of_steps)*i + 0.1*W + (pDoc->lambda_min)*0.8*W/(pDoc->lambda_max), 0.9*H - 0.7*H/max*(pDoc->time_array2[i]));
	}
	
	dc.SelectObject(pOldPen);
	penCurrent.DeleteObject();



	max = pDoc -> time_array3[0];
	for ( int i = 0; i <= pDoc -> numb_of_steps; ++i){
		if ( pDoc -> time_array3[i] > max){
			max = pDoc -> time_array3[i];
		}
	}

	dc.MoveTo((pDoc->lambda_min)*0.8*W/(pDoc->lambda_max) + 0.1*W, 0.9*H - 0.7*H/max*(pDoc->time_array3[0]));
	penCurrent.CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	pOldPen = (CPen *) dc.SelectObject( &penCurrent);
	
	//dc.LineTo((0.8*W/(pDoc->lambda_max))*(pDoc->lambda_max - pDoc->lambda_min)/(pDoc->numb_of_steps)*(1)+0.1*W, 0.9*H - 0.7*H*5*(pDoc->time_array[1]));
	
	for (int i = 1; i <= pDoc->numb_of_steps; ++i) {
		dc.LineTo(((((0.8*W)/(pDoc->lambda_max))*(pDoc->lambda_max - pDoc->lambda_min))/pDoc->numb_of_steps)*i + 0.1*W + (pDoc->lambda_min)*0.8*W/(pDoc->lambda_max), 0.9*H - 0.7*H/max*(pDoc->time_array3[i]));
	}
	
	dc.SelectObject(pOldPen);
	penCurrent.DeleteObject();

}



void Ctest3View::Table_Discription(CDC* pDC)
{
	Ctest3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CFont font;
	LOGFONT lf;
	memset( &lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 20;
	strcpy(lf.lfFaceName, "Tahoma");
	font.CreateFontIndirect(&lf);
	CFont* def_font = pDC->SelectObject(&font);

	char str[1000];
	sprintf(str, "sample size = %d, number of generations = %d, lambda [%-6.3f : %-6.3f], number of steps = %d", pDoc->tsample_size, pDoc ->tsample_amount, pDoc->lambda_min, pDoc->lambda_max, pDoc->numb_of_steps);
	
	char str2[1000];
	sprintf(str2, "Red - Inverse_function, Green - Table");

	CRect rc;
	GetClientRect(&rc);
	int W=rc.Width();
	int H=rc.Height();

	pDC->TextOut(0.1*W, 0.05*H, str);
	pDC->TextOut(0.1*W, 0.1*H, str2);
	pDC->SelectObject(def_font);
	font.DeleteObject();
}
