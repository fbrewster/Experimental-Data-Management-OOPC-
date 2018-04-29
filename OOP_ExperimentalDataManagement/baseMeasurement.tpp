/*baseMeasurement.tpp
Frank Brewster
Defines the member functions of abstract template base class, measuremnt
*/

template <class T> measuremnt<T>::measuremnt() : name_{ "No Name" }, meas_{ 0 }, measErr_{ 0 }, sysErr_{ 0 }, time_{ 0 } {}

template <class T> measuremnt<T>::measuremnt(const std::string &name, const T &meas, const T &measErr, const T &sysErr, const time_t &time) :
	name_{ name }, meas_{ meas }, measErr_{ measErr }, sysErr_{ sysErr }, time_{ time } {}

template <class T> std::string measuremnt<T>::getName() const { return name_; }
template <class T> time_t measuremnt<T>::getTime() const { return time_; }
template <class T> std::string measuremnt<T>::getTimeString() const {//get time-stamp as string
	char str[26];
	struct std::tm tm;
	gmtime_s(&tm,&time_);
	strftime(str,sizeof(str),"%H:%M:%S %d/%m/%y",&tm); 
	std::string out{ str };
	return out;
}
template <class T> bool measuremnt<T>::getMeasBool() const { return (meas_==0) ? false : true; }//returns false if meas_=0, true otherwise
template <class T> void measuremnt<T>::print(std::ostream& os) const { os << *this; }

template <class T> std::ostream& operator<<(std::ostream& os, const measuremnt<T>& m) {//override insertion operator
	std::string outTime;
	os << "Name: " << m.name_ << std::endl << "Time-stamp: ";
	if (m.time_ == 0) {//if time is epoch, display as not set
		os << "Not Set" << std::endl;
	}
	else {
		os << m.getTimeString() << std::endl;
	}
	os << "Measurement = " << m.meas_ << "+-" << m.measErr_ << std::endl
		<< "Systematic error = " << m.sysErr_ << std::endl;
	return os;
}

/*template<class T> std::shared_ptr<measuremnt<T>> measeurmnt<T>::operator/(const double d) const {
	T outMeas{ meas_ / d };
	T outMeasErr{ measErr_ / d };
	T outSysErr{ sysErr_ / d };
	std::shared_ptr<measuremnt<T>> out
}*/


/*template <class T> void measuremnt<T>::operator+=(const numM& m) {
	*this = *this + m;
}*/


//--------------Obsolete--------------

//template <class T> measuremnt<T>::~measuremnt() {}

/*template <class T> measuremnt<T>* measuremnt<T>::operator+(const measuremnt<T>* m) const {
measuremnt<T>* mOut = &this;
mOut->meas_ = this->meas_ + m->meas_;
mOut->measErr_ =
return mOut;
}*/

/*template <class T,class D> D measuremnt<T>::operator+(const D &m) const {
	std::string outName{ m.name_ + "+" + name_ };
	T outMeas{ m.meas_ + meas_ };
	T outMeasErr{ sqrt(pow(measErr_,2) + pow(m.measErr_,2)) };
	T outSysErr{ sysErr_ + m.sysErr_ };
	D out(outName, outMeas, outMeasErrm, outSysErr, 0);
	return out;
}*/