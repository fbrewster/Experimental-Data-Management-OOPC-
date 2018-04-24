// OOPExperimentalDataManagement.cpp : Defines the entry point for the console application.
//

/*TODO: 
- Implement UI
- Experiment class member functions
	- Delete entry - done (24/4)
	- mean of experiment - done (24/4)
	- median of experiment - done errors might need improving (24/4)
	- range of experiment

- Experiment 1D or 2D? - 2D? No 1D? (23/4)
- Convert to smart pointers - DONE? (22/4)
*/

#include "stdafx.h"
#include "measurementTypes.h"
#include "baseExperiment.h"

typedef std::vector<std::shared_ptr<measuremnt<double>>> measVec;


int main()
{

	measVec mv;
	std::shared_ptr<measuremnt<double>> nm1p(new numMeas<double>("nm", 5, 0.2));
	std::shared_ptr<measuremnt<double>> nm2p(new numMeas<double>("nm", 4, 0.3));

	mv.push_back(nm1p);
	mv.push_back(nm2p);


	experiment<double> e1(mv);

	std::shared_ptr<measuremnt<double>> mean(e1.mean());

	std::cout << e1.toString() << std::endl;

	e1.removeEntry(1);

	std::cout << e1.toString();

	return 0;
}