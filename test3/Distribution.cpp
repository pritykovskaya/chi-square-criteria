#include "stdafx.h"
#include "Distribution.h"
#include <math.h>
#include <stdio.h>
Distribution::Distribution(int lambda1){
	lambda = lambda1;
    sample_size = 0;
	prob = 0;
}



void Distribution::findprob(){
    int len = 1;
	double temp = 1/exp((double)lambda);
	double sum = temp;
	int j = 0;
	while ( sum < 1 - EPSILON){
		++j;
		len++;
		temp = temp*lambda/(j);
		sum += temp;
	}
	++len;
	delete[] prob;
	prob = new double[len];
	temp = 1/exp((double)lambda);
	prob[0] = temp;
	for ( int i = 1; i < (len-1); ++i){
		temp = temp*lambda/(i);
		prob[i] = temp;
	}
	prob[len - 1] = 1 - sum; 
	sample_size = len;
}
