#include "stdafx.h"
#include "baseExperiement.h"

std::ostream& operator<<(std::ostream& os, const experiment& e) {
	for (auto m: e.measurements_) {
		m->print(os);
	}
	return os;
}

/*experiment::experiment(const std::vector<std::vector<std::shared_ptr<Imeasuremnt>>> measurements) : measurements_{ measurements } {
	for (auto m : measurements) {
		colNames_.push_back(m[0]->getName());
	}
}*/

void experiment::addMeas(const std::shared_ptr<Imeasuremnt> m) { measurements_.push_back(m); }

std::string experiment::getName() const { return measurements_[0]->getName(); }

std::string experiment::toString() const {
	std::stringstream ss;
	for (auto m : measurements_) {
		ss << m->getMeas() << "+-" << m->getMeasErr()
			<< "(" << m->getSysErr() << "), ";
	}
	std::string out{ ss.str() };
	out.pop_back();
	out.pop_back();
	out.push_back('.');
	return out;
}