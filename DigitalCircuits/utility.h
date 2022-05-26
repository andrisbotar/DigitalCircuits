#pragma once
#ifndef __UTILITY__
#define __UTILITY__

#include <vector>
#include "components.h"

namespace digitalc {
	std::string BoolToString(bool b);
	std::vector<bool> int_to_bool_vector(int n);
	std::vector<bool> truth_table(LogicGate& comp, int n);

	void printstate(std::vector<bool> circuitstate);
	void print_int_vector(std::vector<int> circuitstate);
	std::string int_vector_to_string(std::vector<int> circuitstate);
}

#endif