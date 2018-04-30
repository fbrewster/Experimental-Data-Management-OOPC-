/*measurementTypes.tpp
Frank Brewster
Defines member functions for template classes in measurementTypes.tpp
*/


//----Numeric Measure----
template <class T> numMeas<T>::numMeas() : measuremnt() {}

template <class T> numMeas<T>::numMeas(const std::string &name, const T &meas, const T &measErr, const T &sysErr, const time_t &time) :
	measuremnt<T>(name, meas, measErr, sysErr, time) {}

template <class T> T numMeas<T>::getMeas() const { return meas_; }
template <class T> T numMeas<T>::getMeasErr() const { return measErr_; }
template <class T> T numMeas<T>::getSysErr() const { return sysErr_; }

template <class T> std::shared_ptr<measuremnt<T>> numMeas<T>::operator+(const std::shared_ptr<measuremnt<T>> m) const {//override addition with error propagation
	std::string outName{ m->getName() + "+" + name_ };
	T outMeas{ m->getMeas() + meas_ };
	T outMeasErr{ sqrt(pow(measErr_,2) + pow(m->getMeasErr(),2)) };
	T outSysErr{ sysErr_ + m->getSysErr() };
	std::shared_ptr<measuremnt<T>> out(new numMeas(outName, outMeas, outMeasErr, outSysErr, 0));
	//numMeas out(outName, outMeas, outMeasErr, outSysErr, 0);
	return out;
}

template <class T> std::shared_ptr<measuremnt<T>> numMeas<T>::operator-(const std::shared_ptr<measuremnt<T>> m) const {//override subtraction with error propagation
	std::string outName{ name_ + "-" + m->getName() };
	T outMeas{ meas_ - m->getMeas() };
	T outMeasErr{ sqrt(pow(measErr_,2) + pow(m->getMeasErr(),2)) };
	T outSysErr{ sysErr_ - m->getSysErr() };
	std::shared_ptr<measuremnt<T>> out(new numMeas(outName, outMeas, outMeasErr, outSysErr, 0));
	return out;
}

template <class T> std::shared_ptr<measuremnt<T>> numMeas<T>::operator*(const std::shared_ptr<measuremnt<T>> m) const {//override multiplication with error propagation
	std::string outName{ name_ + "*" + m->getName() };
	T outMeas{ meas_*m->getMeas() };
	T outMeasErr{ sqrt(pow(measErr_/meas_,2) + pow(m->getMeasErr()/m->getMeas(),2)) * outMeas };
	T outSysErr{ meas_*m->getMeasErr() + m->getMeas()*measErr_ + m->getMeasErr()*measErr_ };
	std::shared_ptr<measuremnt<T>> out(new numMeas(outName, outMeas, outMeasErr, outSysErr, 0));
	return out;
}

template <class T> std::shared_ptr<measuremnt<T>> numMeas<T>::operator/(const std::shared_ptr<measuremnt<T>> m) const {//override division with error propagation
	std::string outName{ name_ + "/" + m->getName() };
	T outMeas{ meas_/m->getMeas() };
	T outMeasErr{ sqrt(pow(measErr_ / meas_,2) + pow(m->getMeasErr() / m->getMeas(),2)) * outMeas };
	T outSysErr{ (m->getMeas()*measErr_ - meas_*(m->getMeasErr())) / (m->getMeas()*(m->getMeas() + m->getMeasErr())) };
	std::shared_ptr<measuremnt<T>> out(new numMeas(outName, outMeas, outMeasErr, outSysErr, 0));
	return out;
}

template<class T> std::shared_ptr<measuremnt<T>> numMeas<T>::operator/(const double& d) const {
	std::ostringstream outNameSS;
	outNameSS << name_ << "/" << d;
	T outMeas{ meas_ / d };
	T outMeasErr{ measErr_ / d };
	T outSysErr{ sysErr_ / d };
	std::shared_ptr<measuremnt<T>> out(new numMeas<T>(outNameSS.str(), outMeas, outMeasErr, outSysErr, 0));
	return out;
}

template<class T> void numMeas<T>::print(std::ostream& os) const { os << *this; }

//--------