/*measuremntTypes.h
Frank Brewster
Defines 3 main types of measurements as classes derived from measurmnt: dates, booleans and numerics. All 3 have a measurement, some form of error and an identifier.
- dateMeas stores a time-stamp as a time_t as well as a time since epoch. Measurement and systematic errors in seconds are stored.
- boolMeas stores a boolean measurement as meas_= 1 or 0. Uncertainty is stored as a fraction.
- numMeas is a template class to store any class T as well as measurement and systematic errors of the same type
*/


//Header Guards
#pragma once
#ifndef MEASUREMENT_TYPES
#define MEASUREMENT_TYPES

#include "stdafx.h"
#include "baseMeasurement.h"//include base class


class dateMeas : public measuremnt<double> {//class for storing dates/times
public:
	friend std::ostream& operator<<(std::ostream& os, const dateMeas& d);//declare insertion operator as friend
	dateMeas();
	dateMeas(const std::string& name, const time_t& time, const double& measErr = 0, const double& sysErr = 0);
	dateMeas(const std::string& name, const std::string& timeStr, const double& measErr = 0, const double& sysErr = 0);
	double getMeas() const;
	double getMeasErr() const;
	double getSysErr() const;
	std::shared_ptr<measuremnt<double>> operator+(const std::shared_ptr<measuremnt<double>>) const;//override addition
	std::shared_ptr<measuremnt<double>> operator-(const std::shared_ptr<measuremnt<double>>) const;//override subtraction
	std::shared_ptr<measuremnt<double>> operator*(const std::shared_ptr<measuremnt<double>>) const;
	std::shared_ptr<measuremnt<double>> operator/(const std::shared_ptr<measuremnt<double>>) const;
	std::shared_ptr<measuremnt<double>> operator/(const double&) const;
};

time_t stringToDate(const std::string&);

class boolMeas : public measuremnt<double> {//class for storing boolean measurements
public:
	friend std::ostream& operator<<(std::ostream& os, const boolMeas& b);//declare insertion operator as friend
	boolMeas();
	boolMeas(const std::string& name, const bool& b, const double& measErr = 0, const time_t& time = 0);
	double getMeas() const;
	//bool getMeasBool() const;
	double getMeasErr() const;
	double getSysErr() const { return 0; }
	std::shared_ptr<measuremnt<double>> operator+(const std::shared_ptr<measuremnt<double>>) const;//override addition
	std::shared_ptr<measuremnt<double>> operator-(const std::shared_ptr<measuremnt<double>>) const;//override subtraction
	std::shared_ptr<measuremnt<double>> operator*(const std::shared_ptr<measuremnt<double>>) const;
	std::shared_ptr<measuremnt<double>> operator/(const std::shared_ptr<measuremnt<double>>) const;
	std::shared_ptr<measuremnt<double>> operator/(const double&) const;
};

template <class T> class numMeas : public measuremnt<T> {//template class for storing values of type T
public:
	numMeas();
	numMeas(const std::string &name, const T &meas, const T &measErr, const T &sysErr = 0, const time_t &time = 0);
	T getMeas() const;
	T getMeasErr() const;
	T getSysErr() const;
	std::shared_ptr<measuremnt<T>> operator+(const std::shared_ptr<measuremnt<T>>) const;//override addition
	std::shared_ptr<measuremnt<T>> operator-(const std::shared_ptr<measuremnt<T>>) const;//override subtraction
	std::shared_ptr<measuremnt<T>> operator*(const std::shared_ptr<measuremnt<T>>) const;//override multiplication
	std::shared_ptr<measuremnt<T>> operator/(const std::shared_ptr<measuremnt<T>>) const;//override division
	std::shared_ptr<measuremnt<T>> operator/(const double&) const;
};

#include "measurementTypes.tpp"//Defines member functions of numMeas<T>

#endif // !MEASUREMENT_TYPES
