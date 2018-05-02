// OOPExperimentalDataManagement.cpp : Defines the entry point for the console application.
/*Frank Brewster
This programmed can be used to store and manipulate data. A base measuremnt class is defined that contains a templated measurement, measurement error, systematic error and a time-stamp as a time-t.
The program only allows the int and double versions of the template.
3 class are derived from this. 
dateMeas derives from measuremnt<double> and allows for the storage of a measure of a time-stamp.
boolMeas derives from measuremnt<double> and allows for a true or false measurment. Errors 
numMeas is a template and derives from measurent. It allows for an int or double numerical measurement.
Files are included that describe a menu system for the loading of data and its use as well as for getting a valid input from the keyboard. 
There is also a function for the printing of ascii art from file.
*/

/*TODO: 
- Implement UI
	- Headers for getting valid input DONE (29/04)
	- Output to file DONE (28/4)
	- Read file DONE (29/4)
	- Get keyboard input DONE (30/4)
	- Get keyboard input in real time DONE (30/4)
	- Output to console DONE (28/4)
	- Report to file or console DONE (28/4)
	- Menu system DONE (30/4)
- Experiment class member functions
	- Delete entry - done (24/4)
	- mean of experiment - done (24/4)
	- median of experiment - done errors might need improving (24/4)
	- range of experiment - done (24/4)
	- generate a report on an experiment DONE (29/4)
	- linear fit NOT NEEDED?

- Experiment 1D or 2D? - 2D? No 1D (23/4)
- Convert to smart pointers - DONE (22/4)
*/

#include "stdafx.h"
#include "measurementTypes.h"
#include "baseExperiment.h"
#include "validInputChecking.h"
#include "dataLoading.h"
#include "printLogo.h"
#include "useData.h"

using namespace std;

expHolder experiments;//Map of experiment name to tuple of double and int experiment. One part of tuple is always empty but allows for easier passing around regardless of experiment template specialization
const size_t outPrecision{ 7 };


int main() {

	try {
		printLogo();//Print acsii art logo found in file. See printLogo.cpp
	}
	catch (exception&){//incase logo file can't be loaded
		cout << "Logo could not be loaded" << endl;
	}

	cout << "This program can be used to store and manipulate experimental data" << endl;

	std::cout.precision(outPrecision);//Set cout to global precision

	bool continueProgram{ true };//Flag for exit. Currently always true but could be used in future.

	do {
		try {
			cout << std::endl;
			cout << "Would you like to load data (l), use data already stored (s) or exit (x): ";
			vector<char> validLoadOp; validLoadOp.push_back('l'); validLoadOp.push_back('s'); validLoadOp.push_back('x');//valid input options
			char loadOp{ getValidIn(validLoadOp) };

			if (loadOp == 'x') { return 0; }
			else if (loadOp == 'l') {
				loadDataMenu();
			}
			else {
				useDataMenu();
			}
		}
		catch (exception& e) {//Catches error if not caught in function
			cerr << "Sorry there was an error," << e.what() << "." << endl//print error message
				<< "You will now be returned to the main screen" << endl;
		}
	} while (continueProgram);

	return 0;
}