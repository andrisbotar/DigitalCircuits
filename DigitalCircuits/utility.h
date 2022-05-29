#pragma once
#ifndef __UTILITY__
#define __UTILITY__

#include <vector>
#include "components.h"

namespace digitalc {
	//template to check if some element is in a vector
	template <typename T, typename U> //has to be in header for linking to wokr
	bool vector_contains(T element, U v)
	{
		if (std::find(v.begin(), v.end(), element) != v.end())
		{
			return true;
		}
		return false;
	}

	std::wstring BoolToString(bool b);
	std::wstring int_vector_to_string(std::vector<int> circuitstate);
	//bool StringToBool(std::wstring);
	std::vector<bool> int_to_bool_vector(int number, int len);
	std::vector<bool> truth_table(logic_gate& comp, int n);
	void printtable(std::vector<bool> table, int width, bool indecies=true, bool frame=true);
	void printstate(std::vector<bool> circuitstate);

	//void print_int_vector(std::vector<int> circuitstate);
	template<typename S> //template function to print out vector of some templated type
	void printvector(std::vector<S> circuitstate)
	{
		for (S i : circuitstate) {
			std::wcout << i << " ";
		}
		std::wcout << " \n";
	}
}

#endif