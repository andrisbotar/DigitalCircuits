


#include "drawing.h"
#include "circuit.h"
#include <iostream>
#include <sstream>  
using namespace digital_circuits;

namespace digital_circuits
{
bool check_diagdraw()
{

	//IF

	if (true) {
		std::wcout << L"Blockdiag installation not detected, unable to draw circuit diagram.\n" <<
			"Please isntall it using 'sudo dnf install Bloackdiag'. ";
		return false;
	}
	return true;
}

void circuit_to_diag(circuit circ)
{

}

void write_diag_file(circuit circ)
{
	std::stringstream ss;

	ss << "{\n";
	for (int i = 0; i < circ.size(); ++i) {
		ss << "gate"<<i<<" [label="<<circ.com
	}
	// gN [label="LABEL" shape=flowachart.SHAPETYPE];     //numbered="N"?
	// gA -> gB [label="N"];    //Direction!
	ss << "\n}";

	//ss >> file
	//grouping?
}




}



