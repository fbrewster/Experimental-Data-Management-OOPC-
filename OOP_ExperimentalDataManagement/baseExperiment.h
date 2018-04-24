#pragma once
#ifndef BASE_EXPERIMENT
#define BASE_EXPERIMENT

#include "baseMeasurement.h"
#include "measurementTypes.h"

template<typename T> class experiment {
	friend std::ostream& operator<<(std::ostream& os, const experiment& e);
private:
	std::vector<std::shared_ptr<measuremnt<T>>> measurements_;
public:
	experiment() : measurements_{ 0 } {}
	experiment(const std::vector<std::shared_ptr<measuremnt<T>>> measurements) : measurements_{ measurements } {}
	void addMeas(const std::shared_ptr<measuremnt<T >>);
	std::string getName() const;
	std::string toString() const;
	std::shared_ptr<measuremnt<T>> mean() const;
	//std::shared_ptr<Imeasuremnt> median() const;
};

#include "baseExperiment.tpp"

#endif // !BASE_EXPERIMENT
