#include "stdafx.h"
#include "Sample.h"
#include "Distribution.h"
#include <stdio.h>
#include "R32M.h"
#include "PROBDIST.h"

Sample::Sample(int lambda1, int size1):sample_size(size1),par(lambda1),time(0){
	emp = NULL;

}


int Inverse_function::oneSimulate(){
	int k = 0;
    double t = exp(double((-1)*par.lambda));
    double s = t;
    double alfa = rnunif();
    while (alfa >= s) {
        ++k;
        t = par.lambda*t/k;
        s += t;
    }
    return k;
}

double Inverse_function::Simulate(){

	double t1 = clock(), t2 = 0;
	// tupo sozdali viborku
	delete[]emp;
	emp = new int [sample_size];
	for ( int i = 0; i < sample_size; ++i) {
		emp[i] = oneSimulate();
	
	}
	// nashli v nej maksimum
	int max = emp[0];
	for ( int i = 0; i < sample_size; i++){
		if ( emp [i] > max){
			max = emp[i];
		}
	}
	++max;
	//
	int* temp = new int [max];
	for ( int i = 0; i < max; ++i){
		temp[i] = 0;
	}
	for ( int i = 0; i < sample_size; ++i){
		temp[emp[i]]++;
	}
	delete[]emp;
	emp = temp;
	range = max;

	t2 = clock();
	time = t2 - t1;
	return (t2 - t1);
}
	

int Table::oneSimulate(){
	
	double al = rnunif();
	int k = 0;
	while ( al >= par.prob[k]){
		++k;
	}
	return k;
}

double Table::Simulate(){
	
	par.findprob();
	for ( int i = 1; i < par.sample_size; ++i){
		par.prob[i] += par.prob[i-1];
	}

	double t1 = clock(), t2 = 0;
	
	delete[] emp;
	emp = new int [sample_size];
	for ( int i = 0; i < sample_size; ++i){
		emp[i] = oneSimulate();
	}
	int max = emp[0];
	for ( int i = 0; i <sample_size; i++){
		if ( emp[i] > max){
			max = emp[i];
		}
	}
	++max;
	int* temp = new int [max];
	for ( int i = 0; i< max; ++i){
		temp[i] = 0;
	}
	for ( int i = 0; i < sample_size; ++i){
		temp[emp[i]]++;
	}
	delete[]emp;
	emp= temp;
	range = max;
	t2 = clock();
	time = t2 - t1;
	return (t2 - t1);
}

int Exponential::oneSimulate(){

	int i = 0;
	double q = exp(double((-1)*par.lambda));
	double t = 1;
	double alfa = rnunif();
	t *= alfa;
	while (t <= q) {
		alfa = rnunif();
		t *= alfa;
		++i;
	}
	return i;
}

double Exponential::Simulate(){
	double t1 = clock(), t2 = 0;
	// tupo sozdali viborku
	delete[]emp;
	emp = new int [sample_size];
	for ( int i = 0; i < sample_size; ++i) {
		emp[i] = oneSimulate();
	
	}
	// nashli v nej maksimum
	int max = emp[0];
	for ( int i = 0; i < sample_size; i++){
		if ( emp [i] > max){
			max = emp[i];
		}
	}
	++max;
	//
	int* temp = new int [max];
	for ( int i = 0; i < max; ++i){
		temp[i] = 0;
	}
	for ( int i = 0; i < sample_size; ++i){
		temp[emp[i]]++;
	}
	delete[]emp;
	emp = temp;
	range = max;

	t2 = clock();
	time = t2 - t1;
	return (t2 - t1);
}

