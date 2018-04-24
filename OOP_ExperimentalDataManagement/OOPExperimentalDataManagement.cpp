// OOPExperimentalDataManagement.cpp : Defines the entry point for the console application.
//

/*TODO: 
- Implement UI
- Experiment class member functions
	- Delete entry	
	- mean of experiment
	- median of experiment
	- range of experiment

- Experiment 1D or 2D? - 2D? No 1D? (23/4)
- Convert to smart pointers - DONE? (22/4)
*/

#include "stdafx.h"
#include "measurementTypes.h"
#include "baseExperiement.h"

typedef std::vector<std::shared_ptr<Imeasuremnt>> measVec;


int main()
{

	measVec mv;
	std::shared_ptr<Imeasuremnt> nm1p(new numMeas<double>("nm", 5, 0.2));
	std::shared_ptr<Imeasuremnt> nm2p(new numMeas<double>("nm", 4, 0.3));

	mv.push_back(nm1p);
	mv.push_back(nm2p);


	experiment e1(mv);

	std::cout << e1.toString() << std::endl;

	return 0;
}