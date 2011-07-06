#ifndef _SAMPLE_
#define _SAMPLE_
#include "stdafx.h"
#include "Distribution.h"

class Sample{
protected:
	Distribution par;
    int sample_size;
	int range;
    int* emp;
	
public:
	double time;
	Sample(int lambda1, int sample_size1);
	Distribution getDistribution()const{return par;};
	int getsize(){return sample_size;};
	int getrange(){return range;};
	int* getemp(){return emp;};
	int getelement(int i) {return emp[i];};
	virtual double Simulate() = 0;
	virtual ~Sample(){delete[] emp;};
};

class Inverse_function:public Sample{
public:
	Inverse_function(int lambda1, int size1):Sample(lambda1, size1){};
	int oneSimulate();
	double Simulate();
	~Inverse_function(){};
};

class Table:public Sample{
public:
	Table(int lambda1, int size1):Sample(lambda1, size1){};
	int oneSimulate();
	double Simulate();
	~Table(){};


};

class Exponential:public Sample{
public:
	Exponential(int lambda1, int size1):Sample(lambda1, size1){};
	int oneSimulate();
	double Simulate();
	~Exponential(){};


};
#endif