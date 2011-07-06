#ifndef _HISTOGRAM_
#define _HISTOGRAM_
#include "Distribution.h"
#include "Sample.h"
class Histogram{
	double* emp;
	double* thr;
	int size;
	double plevel;
	int df;
	double chi;

public:
	void CalcChi();
	void allpvalue();

	Histogram(){emp = 0; thr = 0;};
	Histogram(Distribution& d, Sample* s);
	
	~Histogram();
	double getplevel(){return plevel;};
	int getdf(){return df;};
	double getchi(){return chi;};

	double* getemp(){return emp;};
	double* getthr(){return thr;};
	int getsize(){return size;};

	double pvalue_sample_produce(double* emp, double *thr, int range) ;
};

#endif

