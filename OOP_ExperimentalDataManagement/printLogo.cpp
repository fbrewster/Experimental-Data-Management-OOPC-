#include "stdafx.h"
#include "printLogo.h"

std::string getWholeFile(std::ifstream& file) {
	std::string allLines;
	std::string line;

	while (getline(file, line)) {//add each line to a string
		allLines += line;
		allLines += "\n";//add new line at end of each
	}
	return allLines;
}

void printLogo() {
	std::ifstream file;
	file.open("logo.txt");//file to be printed
	std::string  logoText{ getWholeFile(file) };
	file.close();
	std::cout << logoText;
}