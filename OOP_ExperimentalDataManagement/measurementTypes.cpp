#include "stdafx.h"
#include "measurementTypes.h"
#include "baseMeasurement.h"

//----Date Measure----
dateMeas::dateMeas() : measuremnt() { meas_ = difftime(time(0), 0); }

dateMeas::dateMeas(const std::string& name, const time_t& time, const double& measErr, const double& sysErr) :
	measuremnt(name, difftime(time, 0), measErr, sysErr, time) {}//store as time_t and as seconds since epoch

double dateMeas::getMeas() const { return meas_; }
double dateMeas::getMeasErr() const { return measErr_; }
double dateMeas::getSysErr() const { return sysErr_; }

std::ostream& operator<<(std::ostream& os, const dateMeas& d) {
	os << "Name: " << d.name_ << std::endl
		<< "Date: " << d.getTimeString()
		<< "Date in seconds since epoch = " << d.meas_ << "+-" << d.measErr_ << std::endl
		<< "Systematic error = " << d.sysErr_ << std::endl;
	return os;
}

dateMeas dateMeas::operator+(const dateMeas& m) const {
	std::string outName{ m.name_ + "+" + name_ };
	time_t outTime = time_ + m.time_;
	double outMeasErr{ sqrt(pow(measErr_,2) + pow(m.measErr_,2)) };
	double outSysErr{ sysErr_ + m.sysErr_ };
	dateMeas out(outName, outTime, outMeasErr, outSysErr);
	return out;
}
//--------


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
bool boolMeas::getMeasBool() const { return (meas_ == 1) ? true : false; }
double boolMeas::getMeasErr() const { return measErr_; }

std::ostream& operator<<(std::ostream& os, const boolMeas& b) {
	os << "Name: " << b.name_ << std::endl
		<< "Timestamp: " << b.getTimeString()
		<< "Measurement = " << b.meas_ << std::endl
		<< "Uncertainty = " << b.measErr_ * 100 << "%" << std::endl;
	return os;
}

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