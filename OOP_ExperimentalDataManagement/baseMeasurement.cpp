#include "stdafx.h"
#include "baseMeasurement.h"

measuremnt::measuremnt(const std::string &name, const long double &meas, const long double &measErr, const long double &sysErr, const time_t &time) :
	name_{ name }, meas_{ meas }, measErr_{ measErr }, sysErr_{ sysErr }, time_{ time } {}

measuremnt::~measuremnt() {}

std::string measuremnt::getName() const { return name_; }
long double measuremnt::getMeas() const { return meas_; }
long double measuremnt::getMeasErr() const { return measErr_; }
long double measuremnt::getSysErr() const { return sysErr_; }
time_t measuremnt::getTime() const { return time_; }
std::string measuremnt::getTimeString() const { return ctime(time_); }

std::ostream& operator<<(std::ostream& os, const measuremnt& m) {
	os << "Name: " << m.name_ << std::endl
		<< "Measurement = " << m.meas_ << "+-" << m.measErr_ << std::endl
		<< "Systematic error = " << m.sysErr_ << std::endl;
	return os;
}