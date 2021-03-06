/*baseMeasurement.h
Frank Brewster
Define an abstract base class for the storage of an experimental measurement, its uncertainty, its systematic error and its time-stamp
*/

//Header Guards
#pragma once
#ifndef BASE_MEASUREMNT
#define BASE_MEASUREMNT

#include "stdafx.h"//precompiled headers

template <typename T> class measuremnt;//forward declaration of class

class Imeasuremnt {
public:
	virtual std::string getName() const = 0;
	virtual void print(std::ostream& os) const = 0;
	virtual void setName(const std::string& name) = 0;//set name_
	virtual time_t getTime() const = 0;//return timestamps
	virtual std::string getTimeString() const = 0;//get time stamp as string
	virtual bool getMeasBool() const = 0;//return meas_ as bool
	virtual void getMeas() const = 0;
	virtual double getMeasErr() const = 0;
	virtual double getSysErr() const = 0;
	//virtual void operator+=(std::shared_ptr<Imeasuremnt>) const = 0;
};


template <typename T> std::ostream& operator<<(std::ostream& os, const measuremnt<T>& m);//forward declaration of friend function

template <typename T> class measuremnt: public Imeasuremnt {//abstract template base class for storing experimental measurements
	friend std::ostream& operator<< <>(std::ostream& os, const measuremnt<T>& m);//declare insertion operator as friend
protected:
	std::string name_;//name of measurement
	T meas_, measErr_, sysErr_;//measurement and errors
	time_t time_;//time-stamp
	measuremnt();//abstract base class constructors only accessible from derived classes
	measuremnt(const std::string &name, const T &meas, const T &measErr, const T &sysErr, const time_t &time = 0);
public:
	std::string getName() const;//return name_
	void setName(const std::string& name) { name_ = name; }//set name_
	virtual T getMeas() const = 0;//return meas_
	virtual T getMeasErr() const = 0;//return measErr_
	virtual T getSysErr() const = 0;//return sysErr_
	time_t getTime() const;//return timestamps
	std::string getTimeString() const;//get time stamp as string
	virtual bool getMeasBool() const;//return meas_ as bool
	//virtual measuremnt<T> operator+(const measuremnt<T>* m) const = 0;
	void print(std::ostream& os) const;
	//virtual void operator+=(std::shared_ptr<Imeasuremnt>) const = 0;
};

#include "baseMeasurement.tpp"//Definitions of member functions

#endif