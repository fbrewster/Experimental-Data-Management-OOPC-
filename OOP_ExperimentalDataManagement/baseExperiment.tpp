template<class T> std::ostream& operator<<(std::ostream& os, const experiment<T>& e) {
	for (auto m : e.measurements_) {
		m->print(os);
	}
	return os;
}

/*experiment::experiment(const std::vector<std::vector<std::shared_ptr<Imeasuremnt>>> measurements) : measurements_{ measurements } {
for (auto m : measurements) {
colNames_.push_back(m[0]->getName());
}
}*/

template<class T> void experiment<T>::addMeas(const std::shared_ptr<measuremnt<T>> m) { measurements_.push_back(m); }

template<class T> std::string experiment<T>::getName() const { return measurements_[0]->getName(); }

template<class T> std::string experiment<T>::toString() const {
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

template<class T> void experiment<T>::removeEntry(const size_t& n) { measurements_.erase(measurements_.begin() + (n - 1)); }

template<class T> std::shared_ptr<measuremnt<T>> experiment<T>::mean() const {
	bool first{ true };
	std::shared_ptr<measuremnt<T>> out(measurements_[0]);//Get correct memory allocation
	for (auto m : measurements_) {
		if (!first) { out = *out + m; }//first entry already included
		first = false;
	}
	out = *out / measurements_.size();
	return out;
}

template<class T> std::shared_ptr<measuremnt<T>> experiment<T>::median() const {
	const size_t len{ measurements_.size() };
	std::shared_ptr<measuremnt<T>> midMeas;
	if (len % 2 != 0) { 
		midMeas = measurements_[len / 2];
	}
	else {
		midMeas = *(*measurements_[(len-1)/2] + measurements_[(len+1) / 2]) / 2;
	}
	return midMeas;
}

template<class T> std::shared_ptr<measuremnt<T>> experiment<T>::max() const {
	std::shared_ptr<measuremnt<T>> max(measurements_[0]);
	for (auto m : measurements_) {
		if (m->getMeas() > max->getMeas()) { max = m; }
	}
	return max;
}

template<class T> std::shared_ptr<measuremnt<T>> experiment<T>::min() const {
	std::shared_ptr<measuremnt<T>> min(measurements_[0]);
	for (auto m : measurements_) {
		if (m->getMeas() < min->getMeas()) { min = m; }
	}
	return min;
}

template<class T> void experiment<T>::writeToFile(const std::string &fileName) const {
	std::ofstream file;
	file.open(fileName);
	if (!file) { throw std::invalid_argument(" that file could not be opened"); }
	file << this->getName() << ",error,systematic error,time";
	for (auto m : measurements_) {
		file  << "\n" << m->getMeas() << ","
			<< m->getMeasErr() << ","
			<< m->getSysErr() << ","
			<< m->getTimeString();
	}
	file.close();
}

template<class T> std::string experiment<T>::report() const {
	std::stringstream ss;
	ss << "Experiment Name: " << this->getName() << "\n"
		<< "Number of entries: " << measurements_.size() << "\n"
		<< "Range: " << (this->min())->getMeas() << " - " << (this->max())->getMeas() << "\n"
		<< "Mean Entry = " << (this->mean())->getMeas() << "\n";
	return ss.str();
}