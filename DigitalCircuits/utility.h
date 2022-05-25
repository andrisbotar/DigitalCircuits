#pragma once
#ifndef __UTILITY__
#define __UTILITY__

#include <vector>
namespace digitalc {
	void printstate(std::vector<bool> circuitstate);
	void print_int_vector(std::vector<int> circuitstate);
	std::string int_vector_to_string(std::vector<int> circuitstate);
}

#endif