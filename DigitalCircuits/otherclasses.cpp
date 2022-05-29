//File to contain other miscelaneous classes

#include <iostream>
#include <functional>
#include <vector>
#include "circuit.h"
#include "utility.h"
using namespace digital_circuits;

namespace digital_circuits {

	//give a simple example for boolean functions, to be used as default value for functional variables
	bool simplest_boolean_fn(std::vector<bool> x) {
		return x[0];
	}

	//bool_fn  simple_bolean_fn1 = [](std::vector<bool>) {return true; };
	//bool_fn simple_bolean_fn = [](auto x) {return true; };
	//bool_fn  simple_bolean_fn = [](std::vector<int>) {return true; };
}