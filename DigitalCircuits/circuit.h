#pragma once
#include <vector>
#include <memory>
#include "components.h"
#include "otherclasses.h"

#ifndef __CIRCUIT__
#define __CIRCUIT__

//Define class for storign circuit with multiple inputs, outputs and update functionality
namespace digitalc {
	class Circuit:public digital_object
	{
	protected:
		//int wire_count = 0;
		//int component_count = 0;
		std::vector<bool> state;
		std::vector<bool> new_state;
		std::vector<int> hidden{0};
		std::vector<std::unique_ptr<component>> components;
	public:
		Circuit();
		Circuit(int number_of_wires, bool default_wire_state=false);
		~Circuit();
		//Circuit& operator=(Circuit other);
		void update();
		void printstate();
		void reset_state();
		void reset_state(std::vector<bool> default_state);

		void addwires(int wire_count);
		virtual void deletewire(int n);
		virtual void deletewires(std::vector<int> v);
		bool get_wire_state(int n);
		void set_wire_state(int n, bool value);

		void addcomponent(std::unique_ptr<component> new_component);
		void replacecomponent(int n, std::unique_ptr<component> new_component);
		virtual void deletecomponent();
		std::wstring component_info(int n);
		void set_invert(int n,bool inverted);

		size_t size();
		size_t componentcount();
		void print_info();

		void simulate_cli(int steps);
		void debug();
	};
}


#endif

