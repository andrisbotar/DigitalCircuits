//File to contain other miscelaneous classes

#include <iostream>
#include "circuit.h"
#include "utility.h"
using namespace digital_circuits;

namespace digital_circuits {

	//give a simple example for boolean functions, to be used as default value for functional variables
	bool simplest_boolean_fn(std::vector<bool> x) {
		return x[0];
	}

}