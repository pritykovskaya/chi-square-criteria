#include "stdafx.h"
#include "Distribution.h"
#include "Sample.h"
#include "Histogram.h"
#include <stdio.h>
#include "R32M.h"
#include "PROBDIST.h"

Histogram::Histogram(Distribution& d, Sample* s){
	d.findprob();
	int thrlen = d.sample_size;
	thr = new double [thrlen];

	for ( int i = 0; i < thrlen; ++i){
		thr[i] = d.prob[i] * (s -> getsize());
	}
	
	int emplen = s->getrange();

	emp = new double [emplen];
	for ( int i = 0; i < emplen; ++i){
		emp[i] = s->getelement(i) ;
	}
	if ( emplen > thrlen){ //neverojatno, no fakt
		double* temp = new double[emplen];
		for ( int i = 0; i < thrlen; ++i){
			temp[i] = thr[i];

		}
		delete[] thr;
		thr = temp;
		for ( int i = thrlen; i < emplen; ++i){
			thr[i] = 0;
		}
		thrlen = emplen;
	}
	else {
		double* temp = new double[thrlen];
		for ( int i = 0; i < emplen; ++i){
			temp[i] = emp[i];
		}
		delete[] emp;
		emp = temp;
		for ( int i = emplen; i < thrlen; ++i){
			emp[i] = 0;
		}
		emplen = thrlen;
	}
	size = emplen;
	plevel =0;
	df = 0;
	chi = 0;
}


Histogram::~Histogram(){
		delete[] emp; 
		delete[] thr;
}


int connection( double *thr, double *emp, double *con_thr, int range) {
    int* temp2 = new int[range];
    for (int i = 0; i < range; i++) {
        con_thr[i] = 0;
        temp2[i] = 0;
    }
    int j = 0;
    for (int i = 0; i < range; i++) {
        con_thr[j] += thr[i];
        temp2[j] += emp[i];
        if (con_thr[j] > 5) j++;
    }
    con_thr[j - 1] += con_thr[j];
    temp2[j - 1] += temp2[j];
    for (int i = 0; i < j; i++) {
        emp[i] = temp2[i];
    }
	delete [] temp2;
    return j;
}

double t_count( int range, double* con_thr, double* emp) {
    double t = 0;
    for (int i = 0; i < range; ++i) {
        t += (emp[i]-con_thr[i])*(emp[i]-con_thr[i])/(con_thr[i]);
    }
    return t;
}


double Histogram::pvalue_sample_produce(double* emp, double *thr, int range) {
	
    // connecting
    double* z = new double[range];
    int con = connection(thr, emp, z, range);
	double t = t_count(con, z, emp);
	double pvalue = 1 - pChi(t, con - 1);
	df = con-1;
	chi = 1 - pvalue;
    delete []z;
	return pvalue;
	
} 
void Histogram::CalcChi(){

	double* emp_for_con = new double[size];
	for(int i = 0; i < size; ++i) {
		emp_for_con[i] = emp[i];
	}

	double* thr_for_con = new double[size];
	for(int i = 0; i < size; ++i) {
		thr_for_con[i] = thr[i];
	}

	plevel = pvalue_sample_produce(emp_for_con, thr_for_con, size) ;
	delete [] emp_for_con;
	delete [] thr_for_con;
}
