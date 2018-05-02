/*dataLoading.h
Frank Brewster
Declares functions for loading data and a menu function
*/


/*TODO:
- time conversion DONE
- implement functions DONE
- get working for date DONE
- Menu function DONE
*/

#pragma once
#ifndef DATA_LOADING
#define DATA_LOADING

double& convertFromString(double& out, const std::string& in);//overloaded to switch between stoi and stod
int& convertFromString(int& out, const std::string& in);

typedef std::map <std::string, std::tuple<experiment<double>, experiment<int>>> expHolder;

extern expHolder experiments;//forward declare global experiment holder


//Only 2 types so manual writing is better than template. tplate allows for overriding
experiment<double> loadFromFile(const std::string& fileName, const double& tplate, const char& type = 'n');//load a csv file of the same format as is written out by experiment::writeToFile().

experiment<int> loadFromFile(const std::string& fileName, const int& tplate);

experiment<double> loadFromConsole(const double& tplate, const char& type = 'n');//get data from the console. tplate is dummy to set measurement type, type given num bool or date

experiment<int> loadFromConsole(const int& tplate);//get data from the console. tplate is dummy to set measurement type, type given num bool or date

experiment<double> loadRealTime(const double& tplate, const char& type = 'n');//takes data input from the console, stored the measurements time-stamp as the current system time


experiment<int> loadRealTime(const int& tplate);//takes data input from the console, stored the measurements time-stamp as the current system time

void loadDataMenu();//menu to call other functions

void addExperiment(experiment<double>);//checks for duplication in global experiment holder and either joins or adds a new entry
void addExperiment(experiment<int>);

#endif // !DATA_LOADING
