#pragma once
#ifndef BASE_MEASUREMNT
#define BASE_MEASUREMNT

#include<string>
#include<ctime>
#include<iostream>

//std::ostream& operator<<(std::ostream& os, const measuremnt& m);

class measuremnt {
	friend std::ostream& operator<<(std::ostream& os, const measuremnt& m);
private:
	std::string name_;
	long double meas_, measErr_, sysErr_;
	time_t time_;
public:
	measuremnt(const std::string &name, const long double &meas, const long double &measErr, const long double &sysErr = 0, const time_t &time = time(0));
	virtual ~measuremnt();
	std::string getName() const;
	long double getMeas() const;
	long double getMeasErr() const;
	long double getSysErr() const;
	time_t getTime() const;
	std::string getTimeString() const;
};

#endif