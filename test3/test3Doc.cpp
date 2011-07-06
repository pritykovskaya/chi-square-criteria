// test3Doc.cpp : implementation of the Ctest3Doc class
//

#include "stdafx.h"
#include "test3.h"
#include "R32M.h"

#include "test3Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ctest3Doc

IMPLEMENT_DYNCREATE(Ctest3Doc, CDocument)

BEGIN_MESSAGE_MAP(Ctest3Doc, CDocument)
	ON_COMMAND(ID_SETTINGS, &Ctest3Doc::OnSettings)
	
	ON_COMMAND(ID_TIME, &Ctest3Doc::OnTime)
END_MESSAGE_MAP()


// Ctest3Doc construction/destruction

Ctest3Doc::Ctest3Doc():d0(5)
, d1(5)
, method(0)
, pvalvol(100)
, what_on_screen_now(0)
, tsample_size(100)
, tsample_amount(1000)
, lambda_min(1)
, lambda_max(20)
, numb_of_steps(20)
//, tmethod(0)
{
	// TODO: add one-time construction code here
	s = new Inverse_function(5 ,100); 
	pval_freq_array = 0;
	time_array1 = 0;
	time_array2 = 0;
	time_array3 = 0;
	rninit(1);
	h = 0;

}

Ctest3Doc::~Ctest3Doc()
{
	delete h;
	delete s;
	delete [] pval_freq_array;
	delete [] time_array1;
	delete [] time_array2;
	delete [] time_array3;
}

BOOL Ctest3Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// Ctest3Doc serialization

void Ctest3Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// Ctest3Doc diagnostics

#ifdef _DEBUG
void Ctest3Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void Ctest3Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Ctest3Doc commands
void Ctest3Doc::Simulate(void)
{
	s->Simulate();
	delete h;
	h =  new Histogram(d0,s);
}


void Ctest3Doc::OnSettings()
{
	// TODO: добавьте свой код обработчика команд
	Settings c;
	c.lam1 = d0.lambda;
	c.lam2 = d1.lambda;
	c.len1 = s->getsize();
	c.len2 = pvalvol;
	if (c.DoModal() == IDOK){
		
		switch(c.Method){
			case 0: 
				method = 0;
				break;
			case 1:
				method = 1;
				break;
		}
		pvalvol = c.len2;
		d0.lambda = c.lam1;
		d1.lambda = c.lam2;
		delete s;
		if ( method == 0){
			s = new Inverse_function(c.lam2, c.len1);
		}
		if ( method == 1){
			s = new Table(c.lam2, c.len1);
		}
		// redo!!!
		Simulate();
		what_on_screen_now = 1;
		UpdateAllViews(0);
	}
}


void Ctest3Doc::create_pvalue_array()
{	
	Histogram* h1 = 0;
	double *pval_array = new double[pvalvol];

	for(int i = 0; i < pvalvol; ++i){
		delete h1;
		int size = s -> getsize();
		delete s;
		if ( method == 0){
			s = new Inverse_function(d1.lambda, size);
		}
		if ( method == 1){
			s = new Table(d1.lambda, size);
		}
		s -> Simulate();
		h1 = new Histogram(d0, s);
		h1->CalcChi();
		pval_array[i] = h1->getplevel();
	}
	delete[] pval_freq_array;
	pval_freq_array = new double[20];

	for ( int i = 0; i < 20; ++i){
		pval_freq_array[i] = 0;
	}

	for(int i = 0; i < pvalvol; ++i){
		pval_array[i] *= 20;
		pval_freq_array[int(pval_array[i])]++;
	}

	for ( int i = 1; i < 20; ++i){
		pval_freq_array[i] += pval_freq_array[i-1];

	}
	for ( int i = 0; i < 20; ++i){
		pval_freq_array[i] /= double(pvalvol);
	}
	
	delete [] pval_array;
	delete h1;
}	

void Ctest3Doc::set_time_array(void)
{	
	Sample *s1 = 0;
	double step = (lambda_max - lambda_min)/ double(numb_of_steps);
	delete [] time_array1;
	delete [] time_array2;
	delete [] time_array3;
	time_array1 = new double [numb_of_steps + 1];
	time_array2 = new double [numb_of_steps + 1];
	time_array3 = new double [numb_of_steps + 1];
	double lambda_cur = lambda_min;
	int j = 0;
	double t1 = 0, t2 = 0, t3 = 0;
	while (lambda_cur <= lambda_max) {
		for (int i = 0; i < tsample_amount; i++) {
			
			delete s1;
			s1 = new Inverse_function(lambda_cur, tsample_size);
			t1 += (s1 -> Simulate());

			delete s1;
			s1 = new Table(lambda_cur, tsample_size);
			t2 += (s1 -> Simulate());

			delete s1;
			s1 = new Table(lambda_cur, tsample_size);
			t3 += (s1 -> Simulate());
		}
		time_array1[j] = t1 / double(tsample_amount);
		time_array2[j] = t2 / double(tsample_amount);
		time_array3[j] = t3 / double(tsample_amount);
		j++;
		lambda_cur += step;
		t1 = 0;
		t2 = 0;
		t3 = 0;
	}
	
	delete s1;
}
void Ctest3Doc::OnTime()
{	
	CParametrsDlg d;
	d.tsample_size = tsample_size;
	d.tsample_amount = tsample_amount;
	d.lambda_min = lambda_min;
	d.lambda_max = lambda_max;
	d.numb_of_steps = numb_of_steps;


	if (d.DoModal() == IDOK){
		tsample_size = d.tsample_size;
		tsample_amount = d.tsample_amount;
		lambda_min = d.lambda_min;
		lambda_max = d.lambda_max;
		numb_of_steps = d.numb_of_steps;

		what_on_screen_now = 3;
//		Simulate();
		set_time_array();
		UpdateAllViews(0);
	}

	//// TODO: Add your command handler code here
}
