#include "stdafx.h"
#include "baseExperiment.h"
#include "validInputChecking.h"
#include <limits>
#include "dataLoading.h"
#include "getExpType.h"

double& convertFromString(double& out, const std::string& in) {
	out = stod(in);
	return out;
}

int& convertFromString(int& out, const std::string& in) {
	out = stoi(in);
	return out;
}

//std::vector<experiment<double>> Dexperiments;
//std::vector<experiment<int>> Iexperiments;

 experiment<double> loadFromFile(const std::string& fileName, const double& tplate, const char& type) {//reads in data from a file. tplate is a dummy to template the function, type gives num date or bool
	std::ifstream file;
	file.open(fileName);
	if (!file) {//check file is open
		throw std::invalid_argument(" file could not be opened");
	}
	std::string line;
	std::getline(file, line);//get headers
	std::stringstream headerSS(line);//put line into string stream for getline
	std::string headers[4];
	size_t i{ 0 };
	while (getline(headerSS, headers[i], ',')) { i++; }//split line into headers[] by commas
	i = 0;
	headerSS.clear();
	std::string name{ headers[0] };//get name for experiment
	if (headers[1] != "error" || headers[2] != "systematic error" || headers[3] != "time") {//check headers are the same as given in output
		throw std::invalid_argument(" that file is not in the correct format");
	}

	experiment<double> e;

	while (std::getline(file, line)) {
		std::string lineSplit[4];
		std::stringstream lineSS(line);
		size_t c{ 0 };
		while (getline(lineSS, lineSplit[c], ',')) { c++; }//split line by commas
		double meas{ 0 }, measErr{ 0 }, sysErr{ 0 };
		convertFromString(meas, lineSplit[0]);//convert into meas, overloaded by meas type
		convertFromString(measErr, lineSplit[1]);
		convertFromString(sysErr, lineSplit[2]);
		time_t time{ stringToDate(lineSplit[3]) };
		if (type == 'n') {//make measurements and add to experiment e
			e.addMeas(std::make_shared<numMeas<double>>(numMeas<double>(name, meas, measErr, sysErr, time)));
		}
		else if (type == 'd' && typeid(tplate) == typeid(double)) {
			e.addMeas(std::make_shared<dateMeas>(dateMeas(name, time, measErr, sysErr)));
		}
		else if (type == 'b' && typeid(tplate) == typeid(double)) {
			bool bMeas{ (meas == 0) ? false : true };
			e.addMeas(std::make_shared<boolMeas>(boolMeas(name, bMeas, measErr, time)));
		}
		else {
			throw std::invalid_argument(" that is not a valid type");
		}
	}
	std::cout << "Data stored!" << std::endl;
	return e;
}

experiment<int> loadFromFile(const std::string& fileName, const int& tplate) {//reads in data from a file. tplate is a dummy to template the function, type gives num date or bool
	std::ifstream file;
	file.open(fileName);
	if (!file) {//check file is open
		throw std::invalid_argument(" file could not be opened");
	}
	std::string line;
	std::getline(file, line);//get headers
	std::stringstream headerSS(line);//put line into string stream for getline
	std::string headers[4];
	size_t i{ 0 };
	while (getline(headerSS, headers[i], ',')) { i++; }//split line into headers[] by commas
	i = 0;
	headerSS.clear();
	std::string name{ headers[0] };//get name for experiment
	if (headers[1] != "error" || headers[2] != "systematic error" || headers[3] != "time") {//check headers are the same as given in output
		throw std::invalid_argument(" that file is not in the correct format");
	}

	experiment<int> e;

	while (std::getline(file, line)) {
		std::string lineSplit[4];
		std::stringstream lineSS(line);
		size_t c{ 0 };
		while (getline(lineSS, lineSplit[c], ',')) { c++; }//split line by commas
		int meas{ 0 }, measErr{ 0 }, sysErr{ 0 };
		convertFromString(meas, lineSplit[0]);//convert into meas, overloaded by meas type
		convertFromString(measErr, lineSplit[1]);
		convertFromString(sysErr, lineSplit[2]);
		time_t time{ stringToDate(lineSplit[3]) };
		e.addMeas(std::make_shared<numMeas<int>>(numMeas<int>(name, meas, measErr, sysErr, time)));
	}
	std::cout << "Data stored!" << std::endl;
	return e;
}

experiment<double> loadFromConsole(const double& tplate, const char& type) {//get data from the console. tplate is dummy to set measurement type, type given num bool or date
	double meas, measErr, sysErr;
	time_t time;
	std::string name;
	experiment<double> e;
	std::cout << "Enter a name for this experiment: ";//get name
	std::cin >> name;
	bool more{ true };
	do {//keep asking until 'n' given
		if (type == 'n') {//get measurements, errors and time-stamps
			std::cout << "Enter the measurement: ";
			meas = getValidIn(std::numeric_limits<double>::max());
			std::cout << "Enter the error on this measurement: ";
			double dummy{ 0 };
			measErr = getValidIn(std::numeric_limits<double>::max(), dummy);
			std::cout << "Enter the systematic error: ";
			sysErr = getValidIn(std::numeric_limits<double>::max());
			std::cout << "Enter the time-stamp in the form hour:min:sec day/month/2 digit year: ";
			getValidIn(time);
			e.addMeas(std::make_shared<numMeas<double>>(numMeas<double>(name, meas, measErr, sysErr, time)));
		}
		else if (type == 'd') {
			std::cout << "Enter the time-stamp in the form hour:min:sec day/month/2 digit year: ";
			getValidIn(time);
			std::cout << "Enter the error on this measurement in seconds: ";
			double dummy{ 0 };
			measErr = getValidIn(std::numeric_limits<double>::max(), dummy);
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

		std::cout << "Would you like to add another? (y/n): ";//get if need to run again
		std::vector<char> yn; yn.push_back('y'); yn.push_back('n');//valid answers
		char moreChar{ getValidIn(yn) };
		if (moreChar == 'n') { more = false; }
	} while (more);
	std::cout << "Data stored!" << std::endl;
	return e;
}

experiment<int> loadFromConsole(const int& tplate) {//get data from the console. tplate is dummy to set measurement type, type given num bool or date
	int meas, measErr, sysErr;
	time_t time;
	std::string name;
	experiment<int> e;
	std::cout << "Enter a name for this experiment: ";//get name
	std::cin >> name;
	bool more{ true };
	do {//keep asking until 'n' given
		std::cout << "Enter the measurement: ";
		meas = getValidIn(std::numeric_limits<int>::max());
		std::cout << "Enter the error on this measurement: ";
		int dummy{ 0 };
		measErr = getValidIn(std::numeric_limits<int>::max(), dummy);
		std::cout << "Enter the systematic error: ";
		sysErr = getValidIn(std::numeric_limits<int>::max());
		std::cout << "Enter the time-stamp in the form hour:min:sec day/month/2 digit year: ";
		getValidIn(time);
		e.addMeas(std::make_shared<numMeas<int>>(numMeas<int>(name, meas, measErr, sysErr, time)));
		std::cout << "Would you like to add another? (y/n): ";//get if need to run again
		std::vector<char> yn; yn.push_back('y'); yn.push_back('n');//valid answers
		char moreChar{ getValidIn(yn) };
		if (moreChar == 'n') { more = false; }
	} while (more);
	std::cout << "Data stored!" << std::endl;
	return e;
}

experiment<double> loadRealTime(const double& tplate, const char& type) {//takes data input from the console, stored the measurements time-stamp as the current system time
	std::cout << "You will not be asked to input measurements and their errors. Time-stamps will be set as the system clock time when you enter the actual measurement" << std::endl;
	double meas, measErr, sysErr;
	time_t timer;
	std::string name;
	experiment<double> e;
	std::cout << "Enter a name for this experiment: ";//get name
	std::cin >> name;
	bool more{ true };
	do {//keep asking until 'n' given
		if (type == 'n') {//get measurements, errors and time-stamps
			std::cout << "Enter the measurement: ";
			meas = getValidIn(std::numeric_limits<double>::max());
			timer = time(0);
			std::cout << "Enter the error on this measurement: ";
			double dummy{ 0 };
			measErr = getValidIn(std::numeric_limits<double>::max(), dummy);
			std::cout << "Enter the systematic error: ";
			sysErr = getValidIn(std::numeric_limits<double>::max());
			e.addMeas(std::make_shared<numMeas<double>>(numMeas<double>(name, meas, measErr, sysErr, timer)));
		}
		else if (type == 'd') {
			std::cout << "Press a key to record the time-stamp" << std::endl;
			//std::string dummyString
			//std::cin >> dummyString;
			std::cin.get();
			system("pause");
			timer = time(0);
			std::cout << "Enter the error on this measurement in seconds: ";
			double minErr{ 0 };
			measErr = getValidIn(std::numeric_limits<double>::max(), minErr);
			std::cout << "Enter the systematic error: ";
			sysErr = getValidIn(std::numeric_limits<double>::max());
			e.addMeas(std::make_shared<dateMeas>(dateMeas(name, timer, measErr, sysErr)));
		}
		else if (type == 'b') {
			std::cout << "Enter true(1) or false(0): ";
			int max{ 1 }, min{ 0 };
			meas = getValidIn(max, min);
			timer = time(0);;
			bool bMeas{ (meas == 0) ? false : true };
			std::cout << "Enter the percentage certainty on this measurement: ";
			double maxD{ 1 }, minD{ 0 };
			measErr = getValidIn(maxD, minD);
			e.addMeas(std::make_shared<boolMeas>(boolMeas(name, bMeas, measErr, timer)));
		}

		std::cout << "Would you like to add another? (y/n): ";//get if need to run again
		std::vector<char> yn; yn.push_back('y'); yn.push_back('n');//valid answers
		char moreChar{ getValidIn(yn) };
		if (moreChar == 'n') { more = false; }
	} while (more);
	std::cout << "Data stored!" << std::endl;
	return e;
}

experiment<int> loadRealTime(const int& tplate) {//takes data input from the console, stored the measurements time-stamp as the current system time
	std::cout << "You will not be asked to input measurements and their errors. Time-stamps will be set as the system clock time when you enter the actual measurement" << std::endl;
	int meas, measErr, sysErr;
	time_t timer;
	std::string name;
	experiment<int> e;
	std::cout << "Enter a name for this experiment: ";//get name
	std::cin >> name;
	bool more{ true };
	do {//keep asking until 'n' given
		std::cout << "Enter the measurement: ";
		meas = getValidIn(std::numeric_limits<int>::max());
		timer = time(0);
		std::cout << "Enter the error on this measurement: ";
		int dummy{ 0 };
		measErr = getValidIn(std::numeric_limits<int>::max(), dummy);
		std::cout << "Enter the systematic error: ";
		sysErr = getValidIn(std::numeric_limits<int>::max());
		e.addMeas(std::make_shared<numMeas<int>>(numMeas<int>(name, meas, measErr, sysErr, timer)));

		std::cout << "Would you like to add another? (y/n): ";//get if need to run again
		std::vector<char> yn; yn.push_back('y'); yn.push_back('n');//valid answers
		char moreChar{ getValidIn(yn) };
		if (moreChar == 'n') { more = false; }
	} while (more);
	std::cout << "Data stored!" << std::endl;
	return e;
}

void loadDataMenu() {
	std::cout << "Would you like to load a numeric(n), date(d) or boolean(b) measure?: ";
	std::vector<char> validTypes; validTypes.push_back('n'); validTypes.push_back('d'); validTypes.push_back('b');
	char type = getValidIn(validTypes);
	int Idummy;
	double Ddummy;
	char tplateChar;
	if (type == 'n') {
		std::cout << "Would you like an integer(i) or non-integer(d) numeric?: ";
		std::vector<char> validTplate; validTplate.push_back('i'); validTplate.push_back('d');
		tplateChar = getValidIn(validTplate);
	}
	else { tplateChar = 'd'; }
	std::cout << "Would you like to load from file(f), console with time-stamps entered manually(m) or console in real time(r)?: ";
	std::vector<char> validInputTypes; validInputTypes.push_back('f'); validInputTypes.push_back('m'); validInputTypes.push_back('r');
	char inputType = getValidIn(validInputTypes);
	if (inputType == 'f') {
		std::cout << "Please enter the filename/path: ";
		std::string fileName;
		std::cin >> fileName;
		if (tplateChar == 'i') {
			addExperiment(loadFromFile(fileName, Idummy));
		}
		else {
			addExperiment(loadFromFile(fileName, Ddummy, type));
		}
	}
	else if (inputType == 'c') {
		if (tplateChar == 'i') {
			addExperiment(loadFromConsole(Idummy));
		}
		else {
			addExperiment(loadFromConsole(Ddummy, type));
		}
	}
	else {
		if (tplateChar == 'i') {
			addExperiment(loadRealTime(Idummy));
		}
		else {
			addExperiment(loadRealTime(Ddummy, type));
		};
	}
}

void addExperiment(experiment<double> eNew) {
	bool match{ false };
	size_t i{ 0 }, matchIndex;
	for (auto e : experiments) {
		auto eType{ std::get<experiment<double>>(e) };
		if (eNew.getName() == eType.getName()) {
			match = true;
			matchIndex = i;
		}
		i++;
	}
	i--;

	if (match) {
		std::get<experiment<double>>(experiments[i]).concat(eNew);
	}
	else {
		experiment<int> dummyE;
		experiments.push_back(std::make_tuple<experiment<double>, experiment<int>>(std::move(eNew), std::move(dummyE)));
	}
}

void addExperiment(experiment<int> eNew) {
	bool match{ false };
	size_t i{ 0 }, matchIndex;
	for (auto e : experiments) {
		auto eType{ std::get<experiment<int>>(e) };
		if (eNew.getName() == eType.getName()) {
			match = true;
			matchIndex = i;
		}
		i++;
	}
	i--;

	if (match) {
		std::get<experiment<int>>(experiments[i]).concat(eNew);
	}
	else {
		experiment<double> dummyE;
		experiments.push_back(std::make_tuple<experiment<double>, experiment<int>>(std::move(dummyE), std::move(eNew)));
	}
}