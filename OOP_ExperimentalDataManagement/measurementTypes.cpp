/*measurementTypes.cpp
Frank Brewster
Defines the member functions of dateMeas and boolMeas
*/


#include "stdafx.h"
#include "measurementTypes.h"//include header with declarations of classes
#include "baseMeasurement.h"//base class

//----Date Measure----
dateMeas::dateMeas() : measuremnt() { meas_ = difftime(time(0), 0); }

dateMeas::dateMeas(const std::string& name, const time_t& time, const double& measErr, const double& sysErr) :
	measuremnt(name, difftime(time, 0), measErr, sysErr, time) {}//store as time_t and as seconds since epoch

dateMeas::dateMeas(const std::string& name, const std::string& timeStr, const double& measErr, const double& sysErr) : measuremnt(name, 0, measErr, sysErr, 0) {
	/*struct std::tm tm;
	std::istringstream ss(timeStr);
	ss >> std::get_time(&tm, "%d/%m/%Y-%R");
	time_ = mktime(&tm);*/
	time_ = stringToDate(timeStr);
	meas_ = difftime(time_, 0);
}

double dateMeas::getMeas() const { return meas_; }
double dateMeas::getMeasErr() const { return measErr_; }
double dateMeas::getSysErr() const { return sysErr_; }

std::ostream& operator<<(std::ostream& os, const dateMeas& d) {//override insertion operator
	os << "Name: " << d.name_ << std::endl
		<< "Date: " << d.getTimeString() << std::endl
		<< "Date in seconds since epoch = " << d.meas_ << "+-" << d.measErr_ << std::endl
		<< "Systematic error = " << d.sysErr_ << std::endl;
	return os;
}

std::shared_ptr<measuremnt<double>> dateMeas::operator+(const std::shared_ptr<measuremnt<double>> m) const {//override addition with error propagation
	std::string outName{ m->getName() + "+" + name_ };
	time_t outTime = time_ + m->getTime();
	double outMeasErr{ sqrt(pow(measErr_,2) + pow(m->getMeasErr(),2)) };
	double outSysErr{ sysErr_ + m->getSysErr() };
	std::shared_ptr<measuremnt<double>> out(new dateMeas(outName, outTime, outMeasErr, outSysErr));
	return out;
}

std::shared_ptr<measuremnt<double>> dateMeas::operator-(const std::shared_ptr<measuremnt<double>> m) const {//override subtraction with error propagation
	std::string outName{ name_ + "-" + m->getName() };
	time_t outTime = time_ - m->getTime();
	double outMeasErr{ sqrt(pow(measErr_,2) + pow(m->getMeasErr(),2)) };
	double outSysErr{ sysErr_ - m->getSysErr() };
	std::shared_ptr<measuremnt<double>> out(new dateMeas(outName, outTime, outMeasErr, outSysErr));
	return out;
}

std::shared_ptr<measuremnt<double>> dateMeas::operator*(const std::shared_ptr<measuremnt<double>> m) const {
	std::string outName{ name_ + "*" + m->getName() };
	time_t outTime{ time_*m->getTime() };
	double outMeas{ difftime(outTime,0) };
	double outMeasErr{ sqrt(pow(measErr_ / meas_,2) + pow(m->getMeasErr() / m->getMeas(),2)) * outMeas };
	double outSysErr{ meas_*m->getMeasErr() + m->getMeas()*measErr_ + m->getMeasErr()*measErr_ };
	std::shared_ptr<measuremnt<double>> out(new dateMeas(outName, outTime, outMeasErr, outSysErr));
	return out;
}

std::shared_ptr<measuremnt<double>> dateMeas::operator/(const std::shared_ptr<measuremnt<double>> m) const {
	std::string outName{ name_ + "/" + m->getName() };
	time_t outTime{ time_ / m->getTime() };
	double outMeas{ difftime(outTime,0) };
	double outMeasErr{ sqrt(pow(measErr_ / meas_,2) + pow(m->getMeasErr() / m->getMeas(),2)) * outMeas };
	double outSysErr{ (m->getMeas()*measErr_ - meas_*(m->getMeasErr())) / (m->getMeas()*(m->getMeas() + m->getMeasErr())) };
	std::shared_ptr<measuremnt<double>> out(new dateMeas(outName, outTime, outMeasErr, outSysErr));
	return out;
}

std::shared_ptr<measuremnt<double>> dateMeas::operator/(const double& d) const {
	std::stringstream outNameSS;
	outNameSS << name_ << "/" << d;
	std::string outName{ outNameSS.str() };
	double outMeas{ meas_ / d };
	//time_t outTime(outMeas);
	double outMeasErr{ measErr_ / d };
	double outSysErr{ sysErr_ / d };
	std::shared_ptr<measuremnt<double>> out(new dateMeas(outName, (time_t)(outMeas), outMeasErr, outSysErr));
	return out;
}

void dateMeas::print(std::ostream& os) const { os << *this; }
//--------

time_t stringToDate(const std::string& s) {
	std::tm tm = { 0 };
	std::stringstream ss(s);
	ss >> std::get_time(&tm, "%H:%M:%S %d/%m/%y");
	return mktime(&tm);
}


//----Boolean Measure----
boolMeas::boolMeas() : measuremnt() {}

boolMeas::boolMeas(const std::string& name, const bool& b, const double& measErr, const time_t& time) : measuremnt(name, 0, 0, 0, time) {
	if (measErr >= 1 || measErr < 0) {
		throw std::invalid_argument(" error for a boolMeas should be given as a fraction");
	}
	else {
		measErr_ = measErr;
	}
	if (b) {
		meas_ = 1;
	}
}

double boolMeas::getMeas() const { return meas_; }
//bool boolMeas::getMeasBool() const { return (meas_ == 1) ? true : false; }
double boolMeas::getMeasErr() const { return measErr_; }

std::shared_ptr<measuremnt<double>> boolMeas::operator+(const std::shared_ptr<measuremnt<double>> m) const {
	std::string outName{ m->getName() + "+" + name_ };
	time_t outTime = time(0);
	bool outMeas = this->getMeasBool() || m->getMeasBool();
	double outMeasErr{ measErr_ + m->getMeasErr() };
	std::shared_ptr<measuremnt<double>> out(new boolMeas(outName, outMeas, outMeasErr, outTime));
	return out;
}//override addition

std::shared_ptr<measuremnt<double>> boolMeas::operator-(const std::shared_ptr<measuremnt<double>> m) const {
	std::string outName{ name_ + "-" + m->getName() };
	time_t outTime = time(0);
	double outMeasErr{ measErr_ - m->getMeasErr() };
	std::shared_ptr<measuremnt<double>> out(new boolMeas(outName, false, outMeasErr, outTime));
	return out;
}

std::shared_ptr<measuremnt<double>> boolMeas::operator*(const std::shared_ptr<measuremnt<double>> m) const {
	std::string outName{ m->getName() + "*" + name_ };
	time_t outTime = time(0);
	bool outMeas = this->getMeasBool() ^ m->getMeasBool();
	double outMeasErr{ measErr_ * m->getMeasErr() };
	std::shared_ptr<measuremnt<double>> out(new boolMeas(outName, outMeas, outMeasErr, outTime));
	return out;
}

std::shared_ptr<measuremnt<double>> boolMeas::operator/(const std::shared_ptr<measuremnt<double>> m) const {
	std::string outName{ m->getName() + "/" + name_ };
	time_t outTime = time(0);
	bool outMeas = this->getMeasBool() && m->getMeasBool();
	double outMeasErr{ measErr_ * m->getMeasErr() };
	std::shared_ptr<measuremnt<double>> out(new boolMeas(outName, outMeas, outMeasErr, outTime));
	return out;
}

std::shared_ptr<measuremnt<double>> boolMeas::operator/(const double& d) const {
	throw std::invalid_argument(" function boolMeas/double is not defined");
}

std::ostream& operator<<(std::ostream& os, const boolMeas& b) {//override insertion operator
	os << "Name: " << b.name_ << std::endl
		<< "Time-stamp: " << b.getTimeString() << std::endl
		<< "Measurement = " << b.meas_ << std::endl
		<< "Uncertainty = " << b.measErr_ * 100 << "%" << std::endl;
	return os;
}

void boolMeas::print(std::ostream& os) const { os << *this; }

/*boolMeas boolMeas::operator=(const measuremnt<double>& m) {
	boolMeas out;
	out.name_ = m.getName();
	out.meas_ = m.getMeas();
	out.measErr_ = m.getMeasErr();
	out.sysErr_ = m.getSysErr();
	out.time_ = m.getTime();
	return out;
}*/
//--------