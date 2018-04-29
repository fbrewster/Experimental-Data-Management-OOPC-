#pragma once
#ifndef VALID_IN
#define VALID_IN

#include "stdafx.h"
#include "measurementTypes.h"

char getValidIn(const std::vector<char>);//gets one of the chars in the vector from the console

std::string getValidIn(const std::vector<std::string>);//gets one of the strings in the vector from the console

double getValidIn(const double& max, const double& min = -std::numeric_limits<double>::max());//gets a valid double from the console between min and max

int getValidIn(const int& max, const int& min = -std::numeric_limits<int>::max());//gets a valid int from the console between min and max

time_t& getValidIn(time_t&);//gets valid time-stamp from the console

#endif // !

