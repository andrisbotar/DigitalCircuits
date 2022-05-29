#pragma once
#include <vector>
#include <memory>
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
		std::vector<std::unique_ptr<component>> components;
	public:
		Circuit();
		Circuit(int number_of_wires, bool default_wire_state=false);
		~Circuit();
		//Circuit& operator=(Circuit other);
		void reset_state();
		void reset_state(std::vector<bool> default_state);
		void addwires(int wire_count);
		virtual void deletewires();
		bool get_wire_state(int n);
		void set_wire_state(int n, bool value);
		void addcomponent(std::unique_ptr<component> new_component);
		virtual void deletecomponent();
		void replacecomponent(int n, std::unique_ptr<component> new_component);
		std::wstring component_info(int n);
		void set_invert(int n,bool inverted);
		size_t size();
		void printstate();
		void update();
		void simulate_cli(int steps);
		void debug(int n);
	};
}


#endif

