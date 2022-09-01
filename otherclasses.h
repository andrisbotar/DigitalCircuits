#pragma once

#ifndef __OTHERCLASSES__
#define __OTHERCLASSES__

#include <vector>
#include <string>
//#include "utility.h"

namespace digital_circuits {

	bool simplest_boolean_fn(std::vector<bool> x);

	class digital_object {
	protected:
		
	public:
		virtual std::wstring get_label()=0;
		~digital_object() {};
	};

}
#endif