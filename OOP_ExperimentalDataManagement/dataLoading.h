/*TODO:
- time conversion DONE
- implement functions DONE
- get working for date DONE
- Menu function
*/

#pragma once
#ifndef DATA_LOADING
#define DATA_LOADING

double& convertFromString(double& out, const std::string& in);//overloaded to switch between stoi and stod

int& convertFromString(int& out, const std::string& in);

extern std::vector<experiment<double>> Dexperiments;
extern std::vector<experiment<int>> Iexperiments;
extern std::vector <std::tuple<experiment<double>, experiment<int>>> experiments;


experiment<double> loadFromFile(const std::string& fileName, const double& tplate, const char& type = 'n');

experiment<int> loadFromFile(const std::string& fileName, const int& tplate);

experiment<double> loadFromConsole(const double& tplate, const char& type = 'n');//get data from the console. tplate is dummy to set measurement type, type given num bool or date

experiment<int> loadFromConsole(const int& tplate);//get data from the console. tplate is dummy to set measurement type, type given num bool or date

experiment<double> loadRealTime(const double& tplate, const char& type = 'n');//takes data input from the console, stored the measurements time-stamp as the current system time


experiment<int> loadRealTime(const int& tplate);//takes data input from the console, stored the measurements time-stamp as the current system time

void loadDataMenu();

void addExperiment(experiment<double>);
void addExperiment(experiment<int>);

#endif // !DATA_LOADING
