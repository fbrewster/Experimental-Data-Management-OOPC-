#include "stdafx.h"
#include "dataLoading.h"

double& convertFromString(double& out, const std::string& in) {
	out = stod(in);
	return out;
}

int& convertFromString(int& out, const std::string& in) {
	out = stoi(in);
	return out;
}