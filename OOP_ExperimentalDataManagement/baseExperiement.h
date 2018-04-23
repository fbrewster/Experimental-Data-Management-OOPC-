#pragma once
#ifndef BASE_EXPERIMENT
#define BASE_EXPERIMENT

#include "baseMeasurement.h"

class experiment {
	friend std::ostream& operator<<(std::ostream& os, const experiment& e);
private:
	std::vector<std::vector<std::shared_ptr<Imeasuremnt>>> measurements_;
public:
	experiment() : measurements_{ 0 } {}
	experiment(const std::vector<std::vector<std::shared_ptr<Imeasuremnt>>> measurements) : measurements_{ measurements } {}
	void addCol(const std::vector<std::shared_ptr<Imeasuremnt>>);
	std::string getColName(const std::size_t&) const;
};

#endif // !BASE_EXPERIMENT
