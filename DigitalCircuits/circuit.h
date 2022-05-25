#pragma once
#include <vector>
#include "components.h"

#ifndef __CIRCUIT__
#define __CIRCUIT__

//Define class for storign circuit with multiple inputs, outputs and update functionality
namespace digitalc {
	class Circuit
	{
	protected:
		//int wire_count = 0;
		//int component_count = 0;
		std::vector<bool> state;
		std::vector<bool> new_state;
		std::vector<component*> components;
	public:
		Circuit();
		Circuit(int number_of_wires);
		Circuit(int number_of_wires, bool default_wire_state);
		~Circuit();
		void debug();
		size_t size();
		void addcomponent(component *c);
		void addwires(int wire_count);
		virtual void deletewires();
		virtual void deletecomponent();
		void reset_state();
		void reset_state(std::vector<bool> default_state);
		void update();
		void printstate();
		void simulate_cli(int steps);
		
	};
}


#endif

