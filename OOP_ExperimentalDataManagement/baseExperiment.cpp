#include "stdafx.h"
#include "baseExperiement.h"

std::ostream& operator<<(std::ostream& os, const experiment& e) {
	for (auto m : e.measurements_) {
		for (auto m2 : m) {
			m2->print(os);
		}
		if (&os == &std::cout) { os << std::endl; }
	}
	return os;
}

/*experiment::experiment(const std::vector<std::vector<std::shared_ptr<Imeasuremnt>>> measurements) : measurements_{ measurements } {
	for (auto m : measurements) {
		colNames_.push_back(m[0]->getName());
	}
}*/

void experiment::addCol(const std::vector<std::shared_ptr<Imeasuremnt>> m) { measurements_.push_back(m); }

std::string experiment::getColName(const std::size_t& c) const {
	std::vector<std::shared_ptr<Imeasuremnt>> thisCol{ measurements_[c] };
	return thisCol[0]->getName();
}

