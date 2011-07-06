#ifndef _DISTRIBUTION_
#define _DISTRIBUTION_
#include "stdafx.h"
#include <math.h>
double const EPSILON = 1e-12;

class Distribution{
public:
	int lambda;
    int sample_size;
    double* prob;

	Distribution(int lambda);
	
    void findprob();
	~Distribution(){delete[] prob;};
};

#endif