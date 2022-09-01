//various utility functions
#pragma once
#ifndef __UTILITY__
#define __UTILITY__

#include <vector>
#include <iostream>
#include "components.h"
#include "common.h"

namespace digital_circuits {
	//Template to check if some element is in a vector
	//Has to be in header for linking to wokr
	template <typename T, typename U> 
	bool vector_contains(T element, U v)
	{
		if (std::find(v.begin(), v.end(), element) != v.end())
		{
			return true;
		}
		return false;
	}
	
	//Template function to print out vector of some templated type
	template<typename S> 
	void print_vector(std::vector<S> circuit_state)
	{
		for (S i : circuit_state) {
			std::wcout << i << " ";
		}
		std::wcout << " \n";
	}

	std::wstring bool_to_string(bool b);
	std::wstring int_vector_to_string(std::vector<int> circuit_state);
	//bool StringToBool(std::wstring);
	std::vector<bool> int_to_bool_vector(int number, int len);
	std::vector<bool> truth_table(logic_gate& comp, int n);
	void print_table(std::vector<bool> table, int width, bool indecies=true, bool frame=true);
	void print_truth_table(logic_gate& comp, int n, int width, bool indecies = true, bool frame = true);
	void print_state(std::vector<bool> circuit_state);
	//void print_int_vector(std::vector<int> circuit_state);
}

#endif