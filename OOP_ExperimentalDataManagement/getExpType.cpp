#include "stdafx.h"
#include "getExpType.h"
#include "validInputChecking.h"

std::tuple<char, char> getExpType() {
	std::cout << "Would you like a numeric(n), date(d) or boolean(b) measure?: ";
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
	else {
		tplateChar = 'd';
	}
	std::tuple<char, char> out = { type,tplateChar };
	return out;
}