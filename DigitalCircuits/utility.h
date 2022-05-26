#pragma once
#ifndef __UTILITY__
#define __UTILITY__

#include <vector>
#include "components.h"

namespace digitalc {
	std::wstring BoolToString(bool b);
	std::vector<bool> int_to_bool_vector(int number, int len);
	std::vector<bool> truth_table(LogicGate& comp, int n);
	void printtable(std::vector<bool> table, int width);

	void printstate(std::vector<bool> circuitstate);
	void print_int_vector(std::vector<int> circuitstate);
	std::wstring int_vector_to_string(std::vector<int> circuitstate);
}

#endif