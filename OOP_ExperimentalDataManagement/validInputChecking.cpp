#include "stdafx.h"
#include "measurementTypes.h"
#include "validInputChecking.h"

char getValidIn(const std::vector<char> validChars) {
	char out;
	bool valid{ true };
	do {//keep asking until valid
		try {
			valid = false;
			std::string input;
			std::getline(std::cin, input);
			if (input.size() != 1) {//check if char
				throw std::invalid_argument(" input must be a single character");
			}
			out = input[0];
			for (auto c : validChars) {//check if is one of the valid elements
				if (out == c) { valid = true; }
			}
			if (!valid) { throw std::invalid_argument(" enter one of the options"); }//throw exception if not found
		}
		catch (std::exception& e) {
			valid = false;//ask again
			std::cout << "Invalid input," << e.what() << ". Please try again: ";//print message
		}

	} while (!valid);
	return out;
}

std::string getValidIn(const std::vector<std::string> validStrings) {
	std::string out;
	bool valid{ false };//ask again unless found
	do {//keep asking until valid
		try {
			valid = false;
			std::getline(std::cin, out);
			for (auto s : validStrings) {//check input matches one of the valid elements
				if (out == s) { valid = true; }
			}
			if (!valid) { throw std::invalid_argument(" enter one of the options"); }//throw exception if not found
		}
		catch (std::exception& e) {
			valid = false;//ask again
			std::cout << "Invalid input," << e.what() << ". Please try again: ";//print message
		}

	} while (!valid);
	return out;
}

double getValidIn(const double& max, const double& min) {
	double out;
	bool valid{ true };//valid unless problem found
	do {
		try {
			valid = true;
			std::string input;
			std::getline(std::cin, input);
			if (input.find_first_not_of("e-.0123456789") != std::string::npos) {//check for non numeric characters
				throw std::invalid_argument(" input is not a number");
			}
			out = stod(input);//try converting to double
			if (out > max || out < min) {//check is in range
				throw std::out_of_range(" input is out of range");
			}
		}
		catch (std::exception& e) {
			valid = false;
			std::cout << "Invalid input," << e.what() << ". Please try again: ";//print error message
		}
	} while (!valid);
	return out;
}

int getValidIn(const int& max, const int& min) {
	int out;
	bool valid{ true };//valid unless problem found
	do {//keep asking until valid
		try {
			valid = true;
			std::string input;
			std::getline(std::cin, input);
			if (input.find_first_not_of("e-0123456789") != std::string::npos) {//check for non-numeric characters
				throw std::invalid_argument(" input is not a number");
			}
			out = stoi(input);
			if (out > max || out < min) {//check is in range
				throw std::out_of_range(" input is out of range");
			}
		}
		catch (std::exception& e) {
			valid = false;
			std::cout << "Invalid input," << e.what() << ". Please try again: ";//print error message
		}
	} while (!valid);
	return out;
}

time_t& getValidIn(time_t& t) {
	bool valid{ true };
	do {
		try {
			valid = true;
			std::string input;
			std::getline(std::cin, input);
			t = stringToDate(input);//returns -1 if not successful
			if (t == -1) {//throw exception if not successful 
				throw std::invalid_argument(" input could not be converted to a time-stamp");
			}
		}
		catch (std::exception& e) {
			valid = false;
			std::cout << "Invalid input," << e.what() << ". Please try again: ";//print error message
		}

	} while (!valid);
	return t;
}