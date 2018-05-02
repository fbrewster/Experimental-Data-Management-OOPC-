/*baseExperiment.h
Frank Brewster
Defines an experiment class for storing a vector of measurmnt smart pointers
-getName gets the name of the experiment
-nOfMeas gets the size of the measuremnt vector
-concat joins two experiments
-addMeas adds a measuremnt
-toString gives a compact read out of the measurements
-removeEntry removes a measurement by index
-writeToFile writes out the info to a csv file
-report generates a string containing a summary of the measurements
-others are self explanatory
*/


#pragma once
#ifndef BASE_EXPERIMENT
#define BASE_EXPERIMENT

#include "baseMeasurement.h"
#include "measurementTypes.h"

extern const size_t outPrecision;

template<class T> class experiment;//forward declare for insertion
template<class T> std::ostream& operator<<(std::ostream& os, const experiment<T>& e);

template<class T> class experiment {
	friend std::ostream& operator<< <>(std::ostream& os, const experiment<T>& e);//insertion is friend
private:
	std::vector<std::shared_ptr<measuremnt<T>>> measurements_;
public:
	experiment() : measurements_() {}
	experiment(const std::vector<std::shared_ptr<measuremnt<T>>> measurements) : measurements_{ measurements } {}
	void addMeas(const std::shared_ptr<measuremnt<T>>);
	void concat(experiment<T>);
	std::string getName() const;
	size_t nOfMeas() const;
	std::string toString() const;
	void removeEntry(const size_t&);
	std::shared_ptr<measuremnt<T>> mean() const;
	std::shared_ptr<measuremnt<T>> median() const;
	std::shared_ptr<measuremnt<T>> max() const;
	std::shared_ptr<measuremnt<T>> min() const;
	void writeToFile(const std::string&) const;
	std::string report() const;
};

#include "baseExperiment.tpp"

#endif // !BASE_EXPERIMENT
