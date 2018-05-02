/*useData.h
Frank Brewster
Declares functions for manipulating data stored in program
*/

#pragma once
#ifndef USE_DATA
#define USE_DATA

typedef std::map <std::string, std::tuple<experiment<double>, experiment<int>>> expHolder;
extern expHolder experiments;//forward declare global experiment holder
extern const size_t outPrecision;//forward declare global output precision

void useDataMenu();//Menu system for manipulating data

std::shared_ptr<const std::tuple<experiment<double>, experiment<int>>> getExperiment(const std::string& name);//Get pointer to experiment tuple name

void calcMenu(std::shared_ptr<const std::tuple<experiment<double>, experiment<int>>>);//Menu system for calculating experiment properties

#endif // !USE_DATA
