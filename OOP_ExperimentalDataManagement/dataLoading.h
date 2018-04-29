/*TODO:
- time conversion DONE
- implement functions
- get working for date 
*/

#pragma once
#ifndef DATA_LOADING
#define DATA_LOADING

#include "stdafx.h"
#include "baseExperiment.h"
#include "validInputChecking.h"
#include <limits>

double& convertFromString(double& out, const std::string& in);

int& convertFromString(int& out, const std::string& in);

template <class T> experiment<T> loadFromFile(const std::string& fileName, const T& tplate, const char& type = 'n') {
	std::ifstream file;
	file.open(fileName);
	if (!file) {
		throw std::invalid_argument(" file could not be opened");
	}
	std::string line;
	std::getline(file, line);
	std::stringstream headerSS(line);
	std::string headers[4];
	size_t i{ 0 };
	while (getline(headerSS, headers[i], ',')) { i++; }
	i = 0;
	headerSS.clear();
	std::string name{ headers[0] };
	if (headers[1] != "error" || headers[2] != "systematic error" || headers[3] != "time") {
		throw std::invalid_argument(" that file is not in the correct format");
	}

	experiment<T> e;

	while (std::getline(file, line)) {
		std::string lineSplit[4];
		std::stringstream lineSS(line);
		size_t c{ 0 };
		while (getline(lineSS, lineSplit[c], ',')) { c++; }
		T meas{ 0 }, measErr{ 0 }, sysErr{ 0 };
		convertFromString(meas, lineSplit[0]);
		convertFromString(measErr, lineSplit[1]);
		convertFromString(sysErr, lineSplit[2]);
		time_t time{ stringToDate(lineSplit[3]) };
		if (type == 'n') {
			e.addMeas(std::make_shared<numMeas<T>>(numMeas<T>(name, meas, measErr, sysErr, time)));
		}
		else if (type == 'd') {
			e.addMeas(std::make_shared<dateMeas>(dateMeas(name, time, measErr, sysErr)));
		}
		else if (type == 'b') {
			bool bMeas{(meas == 0) ? false : true};
			e.addMeas(std::make_shared<boolMeas>(boolMeas(name, bMeas, measErr, time)));
		}
		else {
			throw std::invalid_argument(" that is not a valid type");
		}
	}
	std::cout << "Data stored!" << std::endl;
	return e;
}

template<class T> experiment<T> loadFromConsole(const T& tplate, const char& type='n') {
	T meas, measErr, sysErr;
	time_t time;
	std::string name;
	experiment<T> e;
	std::cout << "Enter a name for this experiment: ";
	std::cin >> name;
	bool more{ true };
	do {
		if (type == 'n') {
			std::cout << "Enter the measurement: ";
			meas = getValidIn(std::numeric_limits<T>::max());
			std::cout << "Enter the error on this measurement: ";
			T dummy{ 0 };
			measErr = getValidIn(std::numeric_limits<T>::max(),dummy);
			std::cout << "Enter the systematic error: ";
			sysErr = getValidIn(std::numeric_limits<T>::max());
			std::cout << "Enter the time-stamp in the form hour:min:sec day/month/2 digit year: ";
			getValidIn(time);
			e.addMeas(std::make_shared<numMeas<T>>(numMeas<T>(name, meas, measErr, sysErr, time)));
		}
		else if (type == 'd') {
			std::cout << "Enter the time-stamp in the form hour:min:sec day/month/2 digit year: ";
			getValidIn(time);
			std::cout << "Enter the error on this measurement in seconds: ";
			double dummy{ 0 };
			measErr = getValidIn(dummy);
			std::cout << "Enter the systematic error: ";
			sysErr = getValidIn(std::numeric_limits<double>::max());
			e.addMeas(std::make_shared<dateMeas>(dateMeas(name, time, measErr, sysErr)));
		}
		else if (type == 'b') {
			std::cout << "Enter true(1) or false(0): ";
			int max{ 1 }, min{ 0 };
			meas = getValidIn(max, min);
			bool bMeas{ (meas == 0) ? false : true };
			std::cout << "Enter the percentage certainty on this measurement: ";
			double maxD{ 1 }, minD{ 0 };
			measErr = getValidIn(maxD, minD);
			std::cout << "Enter the time-stamp in the form hour:min:sec day/month/2 digit year: ";
			getValidIn(time);
			e.addMeas(std::make_shared<boolMeas>(boolMeas(name, bMeas, measErr, time)));
		}

		cout << "Would you like to add another? (y/n): ";
		std::vector<char> yn; yn.push_back('y'); yn.push_back('n');
		char moreChar{ getValidIn(yn) };
		if (moreChar == 'n') { more = false; }
	} while (more);
	std::cout << "Data stored!" << std::endl;
	return e;
}

template<class T> experiment<T> loadRealTime();

#endif // !DATA_LOADING
