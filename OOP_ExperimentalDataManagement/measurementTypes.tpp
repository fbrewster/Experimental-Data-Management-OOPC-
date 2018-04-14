/*measurementTypes.tpp
Frank Brewster
Defines member functions for template classes in measurementTypes.tpp
*/


//----Numeric Measure----
template <typename T> numMeas<T>::numMeas() : measuremnt() {}

template <typename T> numMeas<T>::numMeas(const std::string &name, const T &meas, const T &measErr, const T &sysErr, const time_t &time) :
	measuremnt<T>(name, meas, measErr, sysErr, time) {}

template <typename T> T numMeas<T>::getMeas() const { return meas_; }
template <typename T> T numMeas<T>::getMeasErr() const { return measErr_; }
template <typename T> T numMeas<T>::getSysErr() const { return sysErr_; }

template <typename T> numMeas<T> numMeas<T>::operator+(const numMeas<T>& m) const {//override addition with error propagation
	std::string outName{ m.name_ + "+" + name_ };
	T outMeas{ m.meas_ + meas_ };
	T outMeasErr{ sqrt(pow(measErr_,2) + pow(m.measErr_,2)) };
	T outSysErr{ sysErr_ + m.sysErr_ };
	numMeas out(outName, outMeas, outMeasErr, outSysErr, 0);
	return out;
}

template <typename T> numMeas<T> numMeas<T>::operator-(const numMeas<T>& m) const {//override subtraction with error propagation
	std::string outName{ name_ + "-" + m.name_ };
	T outMeas{ meas_ - m.meas_ };
	T outMeasErr{ sqrt(pow(measErr_,2) + pow(m.measErr_,2)) };
	T outSysErr{ sysErr_ - m.sysErr_ };
	numMeas out(outName, outMeas, outMeasErr, outSysErr, 0);
	return out;
}

template <typename T> numMeas<T> numMeas<T>::operator*(const numMeas<T>& m) const {//override multiplication with error propagation
	std::string outName{ name_ + "*" + m.name_ };
	T outMeas{ meas_*m.meas_ };
	T outMeasErr{ sqrt(pow(measErr_/meas_,2) + pow(m.measErr_/m.meas_,2)) * outMeas };
	T outSysErr{ meas_*m.measErr_ + m.meas_*measErr_ + m.measErr_*measErr_ };
	numMeas out(outName, outMeas, outMeasErr, outSysErr, 0);
	return out;
}

template <typename T> numMeas<T> numMeas<T>::operator/(const numMeas<T>& m) const {//override division with error propagation
	std::string outName{ name_ + "/" + m.name_ };
	T outMeas{ meas_/m.meas_ };
	T outMeasErr{ sqrt(pow(measErr_ / meas_,2) + pow(m.measErr_ / m.meas_,2)) * outMeas };
	T outSysErr{ (m.meas_*measErr_ - meas_*m.measErr_) / (m.meas_*(m.meas_ + m.measErr_)) };
	numMeas out(outName, outMeas, outMeasErr, outSysErr, 0);
	return out;
}
//--------