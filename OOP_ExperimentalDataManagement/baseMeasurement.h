/*baseMeasurement.h
Frank Brewster
Define an abstract base class for the storage of an experimental measurement, its uncertainty, its systematic error and its timestamp
*/

//Header Guards
#pragma once
#ifndef BASE_MEASUREMNT
#define BASE_MEASUREMNT

#include "stdafx.h"//precompiled headers

template <typename T> class measuremnt;//forward decleration of class
template <typename T> std::ostream& operator<<(std::ostream& os, const measuremnt<T>& m);//forward decleration of friend function

template <typename T> class measuremnt {//abstract template base class for sotring experimental measurements
	friend std::ostream& operator<< <>(std::ostream& os, const measuremnt<T>& m);//declare insertion operator as friend
protected:
	std::string name_;//name of measurement
	T meas_, measErr_, sysErr_;//measurement and errors
	time_t time_;//timestamp
	measuremnt();//abstract base class contructors only accessible from derived classes
	measuremnt(const std::string &name, const T &meas, const T &measErr, const T &sysErr, const time_t &time = 0);
public:
	std::string getName() const;//return name_
	void setName(const std::string& name) { name_ = name; }//set name_
	virtual T getMeas() const = 0;//return meas_
	virtual T getMeasErr() const = 0;//retunr measErr_
	virtual T getSysErr() const = 0;//return sysErr_
	time_t getTime() const;//return timestamp
	std::string getTimeString() const;//get timestamp as string
	virtual bool getMeasBool() const;//return meas_ as bool
	//virtual measuremnt<T> operator+(const measuremnt<T>* m) const = 0;
};

#include "baseMeasurement.tpp"//Definitions of member functions

#endif