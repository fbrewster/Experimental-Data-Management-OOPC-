// OOPExperimentalDataManagement.cpp : Defines the entry point for the console application.
//

/*TODO: 
- Implement UI
- Experiment class member functions
	- Delete col
	- mean of col
	- median of col
	- range of col

- Experiment 1D or 2D?
- Convert to smart pointers
*/

#include "stdafx.h"
#include "measurementTypes.h"
#include "baseExperiement.h"

typedef std::vector<std::shared_ptr<Imeasuremnt>> measVec;

int main()
{

	measVec mv;
	std::shared_ptr<Imeasuremnt> nm1p = new numMeas<double>("nm1", 5, 0.2);

	mv.push_back(new numMeas<double>("nm1", 5, 0.2));
	mv.push_back(new numMeas<double>("nm2", 4, 0.3));

	experiment e1(mv);
	std::cout << e1;

	mv.pop_back();
	std::cout << "Experiment after pop back" << e1;
    
	return 0;
}