#include "stdafx.h"
#include "baseExperiment.h"


//---------OBSOLETE---------

/*std::ostream& operator<<(std::ostream& os, const experiment& e) {
	for (auto m: e.measurements_) {
		m->print(os);
	}
	return os;
}*/

/*experiment::experiment(const std::vector<std::vector<std::shared_ptr<Imeasuremnt>>> measurements) : measurements_{ measurements } {
	for (auto m : measurements) {
		colNames_.push_back(m[0]->getName());
	}
}*/

/*template<typename T> void experiment<T>:addMeas(const std::shared_ptr<measuremnt<T>> m) { measurements_.push_back(m); }

template<typename T> std::string experiment<T>::getName() const { return measurements_[0]->getName(); }

template<typename T> std::string experiment<T>::toString() const {
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
}*/

/*std::shared_ptr<Imeasuremnt> experiment::mean() const {
	std::shared_ptr<Imeasuremnt> tot;
	for (auto m : measurements_) {
		tot = tot + m;
	}
}*/