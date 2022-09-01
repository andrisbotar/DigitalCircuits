//File containing visual drawing functions
#pragma once
#ifndef __DRAWING__
#define __DRAWING__

#include "common.h"
#include "circuit.h"
using namespace digital_circuits;

namespace digital_circuits {

	void circuit_to_diag(circuit circ);
	bool check_blockdiag();
	void write_diag_file(circuit circ, bool show_labels=false);
	//std::wstring get_backgrdound(std::wstring);







}
#endif