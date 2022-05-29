#pragma once

#ifndef __OTHERCLASSES__
#define __OTHERCLASSES__

#include <vector>
#include <string>
//#include "utility.h"

namespace digitalc {

	//init global variables for keepign track of total counts
	int COMPONENTCOUNT{ 0 };
	int CIRCUITCOUNT{ 0 };


	class digital_object {
	protected:
		std::wstring label;
	public:
		~digital_object() {};
	};

}
#endif