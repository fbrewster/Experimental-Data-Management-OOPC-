// OOPExperimentalDataManagement.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "baseMeasurement.h"
#include "measurementTypes.h"


int main()
{

	numMeas<double> n1("n1", 5, 0.2, -0.001, time(0)), n2("n2", 3, 0.5, 0.003, 0);
	numMeas<double> n3 = n1 * n2;

	std::cout << n3;

    return 0;
}