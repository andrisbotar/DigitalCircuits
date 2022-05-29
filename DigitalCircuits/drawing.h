//File containing visual drawing functions
#pragma once
#ifndef __DRAWING__
#define __DRAWING__

#include "common.h"
#include "circuit.h"
using namespace digital_circuits;

namespace digital_circuits {

	
	bool check_diagdraw();
	void circuit_to_diag(circuit circ);
	void write_diag_file(circuit circ);








}
#endif