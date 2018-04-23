#pragma once
#ifndef REPEATED_MEAS
#define REPEATED_MEAS

#include "stdafx.h"
#include "baseMeasurement.h"

template <typename T> class repeatedMeas {
private:
	std::vector<std::unique_ptr<measuremnt<T>>> measS_;
};

#endif // !REPEATED_MEAS
