#pragma once
#ifndef BASE_EXPERIMENT
#define BASE_EXPERIMENT

#include "baseMeasurement.h"
#include "measurementTypes.h"

template<class T> class experiment;
template<class T> std::ostream& operator<<(std::ostream& os, const experiment<T>& e);

/*class Iexperiment {
	//experiment() : measurements_() {}
	//experiment(const std::vector<std::shared_ptr<measuremnt<T>>> measurements) : measurements_{ measurements } {}
	virtual void addMeas(const std::shared_ptr<measuremnt<T>>) = 0;
	virtual std::string getName() const = 0;
	virtual std::string toString() const = 0;
	virtual void removeEntry(const size_t&) = 0;
	virtual std::shared_ptr<Imeasuremnt> mean() const = 0;
	virtual std::shared_ptr<Imeasuremnt> median() const = 0;
	virtual std::shared_ptr<Imeasuremnt> max() const = 0;
	virtual std::shared_ptr<Imeasuremnt> min() const = 0;
	virtual void writeToFile(const std::string&) const = 0;
	virtual std::string report() const = 0;
};*/

template<class T> class experiment {
	friend std::ostream& operator<< <>(std::ostream& os, const experiment<T>& e);
private:
	std::vector<std::shared_ptr<measuremnt<T>>> measurements_;
public:
	experiment() : measurements_() {}
	experiment(const std::vector<std::shared_ptr<measuremnt<T>>> measurements) : measurements_{ measurements } {}
	void addMeas(const std::shared_ptr<measuremnt<T>>);
	std::string getName() const;
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
