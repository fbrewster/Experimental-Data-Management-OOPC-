#include "stdafx.h"
#include "printLogo.h"

std::string getWholeFile(std::ifstream& file) {
	std::string allLines;
	std::string line;

	while (getline(file, line)) {
		allLines += line;
		allLines += "\n";
	}
	return allLines;
}

void printLogo() {
	std::ifstream file;
	file.open("logo.txt");
	std::string  logoText{ getWholeFile(file) };
	file.close();
	std::cout << logoText;
}