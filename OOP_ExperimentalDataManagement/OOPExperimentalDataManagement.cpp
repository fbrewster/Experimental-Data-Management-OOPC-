// OOPExperimentalDataManagement.cpp : Defines the entry point for the console application.
//

/*TODO: 
- Implement UI
	- Headers for getting valid input
	- Output to file DONE (28/4)
	- Read file DONE (29/4)
	- Get keyboard input
	- Get keyboard input in real time
	- Output to console DONE (28/4)
	- Report to file or console DONE (28/4)
- Experiment class member functions
	- Delete entry - done (24/4)
	- mean of experiment - done (24/4)
	- median of experiment - done errors might need improving (24/4)
	- range of experiment - done (24/4)
	- generate a report on an experiment
	- linear fit

- Experiment 1D or 2D? - 2D? No 1D? (23/4)
- Convert to smart pointers - DONE? (22/4)
*/

#include "stdafx.h"
#include "measurementTypes.h"
#include "baseExperiment.h"
#include "validInputChecking.h"
#include "dataLoading.h"

typedef std::vector<std::shared_ptr<measuremnt<double>>> measVec;

using namespace std;

int main()
{

	/*measVec mv;
	std::shared_ptr<measuremnt<double>> nm1p(new numMeas<double>("nm", 5, 0.2,0,time(0)));
	std::shared_ptr<measuremnt<double>> nm2p(new numMeas<double>("nm", 4, 0.3,0,time(0)));

	mv.push_back(nm1p);
	mv.push_back(nm2p);


	experiment<double> e1(mv);

	std::shared_ptr<measuremnt<double>> nm3p(new numMeas<double>("nm", 7.5, 0.4,0,stringToDate("14:53:03 04/28/17")));
	e1.addMeas(nm3p);

	e1.writeToFile("D:\\expTest.csv");*/

	double dummy{ 0 };

	experiment<double> e1(loadFromConsole(dummy));
	cout << e1;

	cout << "This program can be used to store and manipulate experimental data" << endl;

	bool continueProgram{ true };

	do {
		cout << "Would you like to load data (l) or use data already stored (s): ";
		vector<char> validLoadOp;
		validLoadOp.push_back('l'); validLoadOp.push_back('s');
		char loadOp{ getValidIn(validLoadOp) };
		if (loadOp == 'l') {
			cout << "you done a l" << endl;
		}
		else {
			cout << "you done a s" << endl;
		}
		cout << "do something";
	} while (continueProgram);

	return 0;
}