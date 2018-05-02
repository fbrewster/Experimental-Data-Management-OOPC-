/*useData.cpp
Frank Brewster
Defines function for manipulating data.
*/


#include "stdafx.h"
#include "baseExperiment.h"
#include "useData.h"
#include "validInputChecking.h"
#include "getExpType.h"

std::shared_ptr<const std::tuple<experiment<double>, experiment<int>>> getExperiment(const std::string& name) {
	std::shared_ptr<std::tuple<experiment<double>, experiment<int>>> out;
	expHolder::iterator it{ experiments.find(name) };//find experiment with that name 
	if (it == experiments.end()) {//throw exception if it can't be found
		throw std::out_of_range(" an error occurred finding that experiment");
	}
	out = std::make_shared<std::tuple<experiment<double>, experiment<int>>>(std::get<1>(*it));
	return out;
}

void useDataMenu() {//Menu system for manipulating data
	const size_t nOfExp{ experiments.size() };
	if (nOfExp == 0) {//throw exception if there aren't any to use
		throw std::domain_error(" there are no experiments stored to use");
	}
	std::vector<std::string> expNames;
	std::cout << "There are " << nOfExp << " experiments stored named: " << std::endl;
	size_t i{ 1 };
	for (auto eT : experiments) {//print list of experiment names and make vector for valid input checking
		//Difficult to iterate over a tuple, only 2 elements so do it manually
		std::string tempName;
		if (std::get<0>(std::get<1>(eT)).nOfMeas() > 0) {
			tempName = std::get<0>(std::get<1>(eT)).getName();
			expNames.push_back(tempName);
			std::cout << tempName;
		}
		
		if (std::get<1>(std::get<1>(eT)).nOfMeas() > 0) {
			tempName = std::get<1>(std::get<1>(eT)).getName();
			expNames.push_back(tempName);
			std::cout << tempName;
		}
		std::cout << ((i < nOfExp) ? ", " : ".");//print full stop if at the end, comma and space if not
		i++;
	}
	std::cout << std::endl << "Please enter the name of the experiment you want to use: ";
	const std::string useExpName{ getValidIn(expNames) };
	std::shared_ptr<const std::tuple<experiment<double>, experiment<int>>> eTp{ getExperiment(useExpName) };
	
	std::cout << "Would you like to view a report on the experiment(r), save a report to file(f), view it's contents (v), save it's contents(s), calculate a property(c), or delete an exerpiment(d)?: ";
	std::vector<char> validUseOps; validUseOps.push_back('r'); validUseOps.push_back('v'); validUseOps.push_back('s'); validUseOps.push_back('c'); validUseOps.push_back('d'); validUseOps.push_back('f');
	const char useOp{ getValidIn(validUseOps) };

	std::string fileName;//predeclared so switch doesn't get confused
	std::string report;
	std::ofstream file;
	file.precision(outPrecision);//set file writing precision to global
	switch (useOp) {
	case 'r'://view report
		if (std::get<1>(*eTp).nOfMeas() > 0) { std::cout << std::get<1>(*eTp).report(); }
		else { std::cout << std::get<0>(*eTp).report(); }
		break;
	case 'f'://report to file
		std::cout << "Please enter a filename/path: ";
		std::getline(std::cin, fileName);
		if (std::get<1>(*eTp).nOfMeas() > 0) { report = std::get<1>(*eTp).report(); }
		else { report = std::get<0>(*eTp).report(); }
		file.open(fileName);
		if (file) {
			file << report;
			file.close();
		}
		else {//throw exception if the file can't be opening
			throw std::invalid_argument(" that file could be opened for writing");
		}
		break;
	case 'v'://view data
		if (std::get<1>(*eTp).nOfMeas() > 0) { std::cout << std::get<1>(*eTp).toString(); }
		else { std::cout << std::get<0>(*eTp).toString(); }
		break;
	case 's'://data to file
		std::cout << "Please enter a filename/path: ";
		std::getline(std::cin,fileName);
		if (std::get<1>(*eTp).nOfMeas() > 0) { std::get<1>(*eTp).writeToFile(fileName); }
		else { std::get<0>(*eTp).writeToFile(fileName); }
		break;
	case 'c'://calculate
		calcMenu(eTp);
		break;
	case 'd'://delete
		experiments.erase(useExpName);
	}
}

void calcMenu(std::shared_ptr<const std::tuple<experiment<double>, experiment<int>>> eTp) {//Menu system for calculating experiment properties
	std::cout << "Would you like to calculate the mean(1), median(2), max(3) or min(4)?: ";
	const int min{ 1 }, max{ 4 };
	const int calcOp{ getValidIn(max, min) };
	switch (calcOp) {
	case 1://Mean
		std::cout << "Mean of measurements: " << std::endl;
		if (std::get<1>(*eTp).nOfMeas() > 0) { std::cout << *std::get<1>(*eTp).mean(); }
		else { std::cout << *((std::get<0>(*eTp).mean())); }
		break;
	case 2://Median
		std::cout << "Median of measurements: " << std::endl;
		if (std::get<1>(*eTp).nOfMeas() > 0) { std::cout << *std::get<1>(*eTp).median(); }
		else { std::cout << *std::get<0>(*eTp).median(); }
		break;
	case 3://Max
		std::cout << "Maximum measurement: " << std::endl;
		if (std::get<1>(*eTp).nOfMeas() > 0) { std::cout << *std::get<1>(*eTp).max(); }
		else { std::cout << *std::get<0>(*eTp).max(); }
		break;
	case 4://Min
		std::cout << "Minimum measurement: " << std::endl;
		if (std::get<1>(*eTp).nOfMeas() > 0) { std::cout << *std::get<1>(*eTp).min(); }
		else { std::cout << *std::get<0>(*eTp).min(); }
		break;
	}
}