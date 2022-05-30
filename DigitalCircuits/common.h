//header for declaring shared variables and common classes used in other .cpp files

#pragma once
#ifndef __COMMON__
#define __COMMON__

namespace digital_circuits {
	//declare global variables used as settings
	extern bool verbose;
	extern bool draw_symbols;
	extern bool draw_names;
	extern bool draw_labels;
	extern std::string diagram_format; //svg, png or pdf
	extern bool print_indecies;
	extern bool print_frame;
	extern bool math_symbols;
}

#endif