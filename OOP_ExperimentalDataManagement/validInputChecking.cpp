#include "stdafx.h"
#include "measurementTypes.h"
#include "validInputChecking.h"

char getValidIn(const std::vector<char> validChars) {
	char out;
	bool valid{ true };
	do {
		try {
			valid = false;
			std::string input;
			std::cin >> input;
			if (input.size() != 1) {
				throw std::invalid_argument(" input must be a single character");
			}
			out = input[0];
			for (auto c : validChars) {
				if (out == c) { valid = true; }
			}
			if (!valid) { throw std::invalid_argument(" enter one of the options"); }
		}
		catch (std::exception& e) {
			valid = false;
			std::cout << "Invalid input," << e.what() << ". Please try again: ";
		}

	} while (!valid);
	return out;
}

std::string getValidIn(const std::vector<std::string> validStrings) {
	std::string out;
	bool valid{ false };
	do {
		try {
			valid = false;
			std::cin >> out;
			for (auto s : validStrings) {
				if (out == s) { valid = true; }
			}
			if (!valid) { throw std::invalid_argument(" enter one of the options"); }
		}
		catch (std::exception& e) {
			valid = false;
			std::cout << "Invalid input," << e.what() << ". Please try again: ";
		}

	} while (!valid);
	return out;
}

double getValidIn(const double& max, const double& min) {
	double out;
	bool valid{ true };
	do {
		try {
			valid = true;
			std::string input;
			std::cin >> input;
			if (input.find_first_not_of("-.0123456789") != std::string::npos) {
				throw std::invalid_argument(" input is not a number");
			}
			out = stod(input);
			if (out > max || out < min) {
				throw std::out_of_range(" input is out of range");
			}
		}
		catch (std::exception& e) {
			valid = false;
			std::cout << "Invalid input," << e.what() << ". Please try again: ";
		}
	} while (!valid);
	return out;
}

int getValidIn(const int& max, const int& min) {
	int out;
	bool valid{ true };
	do {
		try {
			valid = true;
			std::string input;
			std::cin >> input;
			if (input.find_first_not_of("-0123456789") != std::string::npos) {
				throw std::invalid_argument(" input is not a number");
			}
			out = stoi(input);
			if (out > max || out < min) {
				throw std::out_of_range(" input is out of range");
			}
		}
		catch (std::exception& e) {
			valid = false;
			std::cout << "Invalid input," << e.what() << ". Please try again: ";
		}
	} while (!valid);
	return out;
}

time_t& getValidIn(time_t& t) {
	std::string dummy;
	getline(std::cin, dummy);
	bool valid{ true };
	do {
		try {
			valid = true;
			std::string input;
			std::getline(std::cin, input);
			t = stringToDate(input);
			if (t == -1) {
				throw std::invalid_argument(" input could not be converted to a time-stamp");
			}
		}
		catch (std::exception& e) {
			valid = false;
			std::cout << "Invalid input," << e.what() << ". Please try again: ";
		}

	} while (!valid);
}