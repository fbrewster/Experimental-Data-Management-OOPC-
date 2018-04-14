#pragma once
#ifndef MEASUREMENT_TYPES
#define MEASUREMENT_TYPES

#include "stdafx.h"
#include "baseMeasurement.h"


class dateMeas : public measuremnt<double> {//class for storing dates/times
public:
	friend std::ostream& operator<<(std::ostream& os, const dateMeas& d);
	dateMeas();
	dateMeas(const std::string& name, const time_t& time, const double& measErr = 0, const double& sysErr = 0);
	double getMeas() const;
	double getMeasErr() const;
	double getSysErr() const;
	dateMeas operator+(const dateMeas&) const;
};

class boolMeas : public measuremnt<double> {
public:
	friend std::ostream& operator<<(std::ostream& os, const boolMeas& b);
	boolMeas();
	boolMeas(const std::string& name, const bool& b, const double& measErr = 0, const time_t& time = 0);
	double getMeas() const;
	bool getMeasBool() const;
	double getMeasErr() const;
	double getSysErr() const { return 0; }
	//boolMeas operator=(const measuremnt& m);
};

template <typename T> class numMeas : public measuremnt<T> {
public:
	numMeas();
	numMeas(const std::string &name, const T &meas, const T &measErr, const T &sysErr, const time_t &time = 0);
	T getMeas() const;
	T getMeasErr() const;
	T getSysErr() const;
	numMeas<T> operator+(const numMeas<T>&) const;
	numMeas<T> operator-(const numMeas<T>&) const;
	numMeas<T> operator*(const numMeas<T>&) const;
};

#include "measurementTypes.tpp"

#endif // !MEASUREMENT_TYPES
