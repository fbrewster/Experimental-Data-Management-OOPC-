/*baseMeasurement.tpp
Frank Brewster
Defines the member functions of abstract template base class, measuremnt
*/

template <class T> measuremnt<T>::measuremnt() : name_( "No Name" ), meas_{ 0 }, measErr_{ 0 }, sysErr_{ 0 }, time_{ 0 } {}//default constructor

template <class T> measuremnt<T>::measuremnt(const std::string &name, const T &meas, const T &measErr, const T &sysErr, const time_t &time) ://parameterized constructor
	name_( name ), meas_{ meas }, measErr_{ measErr }, sysErr_{ sysErr }, time_{ time } {}

template <class T> std::string measuremnt<T>::getName() const { return name_; }
template <class T> time_t measuremnt<T>::getTime() const { return time_; }
template <class T> std::string measuremnt<T>::getTimeString() const {//get time-stamp as string
	char str[26];//pre allocate c-style string
	std::tm tm;
	gmtime_s(&tm,&time_);//convert time_t member variable to a tm struct
	strftime(str,sizeof(str),"%H:%M:%S %d/%m/%y",&tm); //convert to string given by formatting (hour:min:sec day/month/2 dig year
	std::string out{ str };//convert char array to c++ string
	return out;
}
template <class T> bool measuremnt<T>::getMeasBool() const { return (meas_==0) ? false : true; }//returns false if meas_=0, true otherwise
template <class T> void measuremnt<T>::print(std::ostream& os) const { os << *this; }//public templated interface to <<

template <class T> std::ostream& operator<<(std::ostream& os, const measuremnt<T>& m) {//override insertion operator
	std::string outTime;
	os.precision(outPrecision);//set precision to global
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