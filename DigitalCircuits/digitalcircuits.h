#pragma once

#ifndef __MAIN__
#define __MAIN__




//Import required libraries and namespaces
#include <iostream>
#include <string>
#include <vector>
#include <sstream> 
#include <io.h>
#include <fcntl.h>
#include "components.h" //Contains AND Gates, XOR gates, buffers...
#include "circuit.h" //Contains circuit class to collect and simualte components
#include "utility.h" //A few miscelaneous utility functions
#include "common.h" //Other shared varaibles inclued in every other file
#include "drawing.h" //For exporting images of circuits in graphical formats -	REQURIES "SUDO DNF INSTALL BLOCKDIAG"!
using namespace digital_circuits; //namespace for own code



//Define global variables
namespace digital_circuits {
	bool verbose{false};
	bool draw_symbols{false};
	bool draw_names{ true };
	bool draw_labels{ false };

}




#endif // !__MAIN__
