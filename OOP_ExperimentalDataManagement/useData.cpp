#include "stdafx.h"
#include "baseExperiment.h"
#include "useData.h"
#include "validInputChecking.h"
#include "getExpType.h"

void useDataMenu() {
	std::tuple<char, char> type{ getExpType() };

}