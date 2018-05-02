/*baseExperiment.tpp
Frank Brewster
Defines the member functions for baseExperiment.h
*/

template<class T> std::ostream& operator<<(std::ostream& os, const experiment<T>& e) {//Friend insertion. Apply print() to each measuremnt in measurements_
	for (auto m : e.measurements_) {
		m->print(os);
	}
	return os;
}

template<class T> void experiment<T>::addMeas(const std::shared_ptr<measuremnt<T>> m) { measurements_.push_back(m); }//Add a measuremnt pointer to measurements_

template<class T> void experiment<T>::concat(experiment<T> e) {//Joins 2 experiments
	for (auto m : e.measurements_) {//add each element of e to this
		this->addMeas(m);
	}
}

template<class T> std::string experiment<T>::getName() const { return (measurements_.size()>0) ? measurements_[0]->getName():""; }//Return name of first measurement as name or empty string if experiment is empty

template<class T> size_t experiment<T>::nOfMeas() const { return measurements_.size(); }

template<class T> std::string experiment<T>::toString() const {//Compact form of all measurements_
	std::stringstream ss;
	ss.precision(outPrecision);
	for (auto m : measurements_) {//output in different forms for different measurements
		if (typeid(*m) == typeid(dateMeas)){//add each element to stream as time-stamp +- error in s(sys error in s)
			ss << m->getTimeString() << " +- " << m->getMeasErr() << "s"
				<< "(" << m->getSysErr() << "s), ";
		}
		else if (typeid(*m) == typeid(boolMeas)){//add each element to stream as bool(%uuncertainty)
			std::string boolString{ (m->getMeas() == 0) ? "False" : "True" };
			ss << boolString
				<< "(" << m->getMeasErr() * 100 << "%), ";
		}
		else{
			ss << m->getMeas() << "+-" << m->getMeasErr()//add each element to stream as meas_+-measErr_(sysErr_)
				<< "(" << m->getSysErr() << "), ";
		}
	}
	std::string out{ ss.str() };//extract from string stream
	out.pop_back();//get rid of ',' and ' ' from end of text
	out.pop_back();
	out.push_back('.');
	return out;
}

template<class T> void experiment<T>::removeEntry(const size_t& n) { measurements_.erase(measurements_.begin() + (n - 1)); }//Erase the nth element by using begin iterator

template<class T> std::shared_ptr<measuremnt<T>> experiment<T>::mean() const {//Return calculated mean. Errors are formed from normal propagation through basic operators
	bool first{ true };
	std::shared_ptr<measuremnt<T>> out(measurements_[0]);;//Get correct memory allocation by just copying first element
	for (auto m : measurements_) {
		if (!first) {
			out = *out + m; 
		}//first entry already included
		first = false;
	}
	out = *out / measurements_.size();
	std::string name{ "Mean of " + this->getName() };
	out->setName(name);
	return out;
}

template<class T> std::shared_ptr<measuremnt<T>> experiment<T>::median() const {//Return middle measuremnt or average of middle 2. Errors are formed from normal propagation through basic operators and so are not accurate
	const size_t len{ measurements_.size() };
	std::shared_ptr<measuremnt<T>> midMeas;
	if (len % 2 != 0) {//if there is a middle 
		midMeas = measurements_[len / 2];
	}
	else {
		midMeas = *(*measurements_[(len-1)/2] + measurements_[(len+1) / 2]) / 2;
	}
	std::string name{ "Median of " + this->getName() };
	midMeas->setName(name);
	return midMeas;
}

template<class T> std::shared_ptr<measuremnt<T>> experiment<T>::max() const {//returns measurement with the max meas_
	std::shared_ptr<measuremnt<T>> max(measurements_[0]);
	for (auto m : measurements_) {
		if (m->getMeas() > max->getMeas()) { max = m; }
	}
	return max;
}

template<class T> std::shared_ptr<measuremnt<T>> experiment<T>::min() const {//returns measurement with the min meas_
	std::shared_ptr<measuremnt<T>> min(measurements_[0]);
	for (auto m : measurements_) {
		if (m->getMeas() < min->getMeas()) { min = m; }
	}
	return min;
}

template<class T> void experiment<T>::writeToFile(const std::string &fileName) const {//writes experiments to csv named fileName
	std::ofstream file;
	file.open(fileName);
	file << std::setprecision(7);
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

template<class T> std::string experiment<T>::report() const {//Returns the name, number of measurements, range and mean experiment formatted
	std::stringstream ss;
	ss << "Experiment Name: " << this->getName() << "\n"
		<< "Number of entries: " << measurements_.size() << "\n"
		<< "Range: " << (this->min())->getMeas() << " - " << (this->max())->getMeas() << "\n"
		<< "Mean Entry = " << (this->mean())->getMeas() << "\n";
	return ss.str();
}