#pragma once
#include <vector>
#include <memory>
#include "components.h"
#include "otherclasses.h"

#ifndef __CIRCUIT__
#define __CIRCUIT__

//Define class for storign circuit with multiple inputs, outputs and update functionality
namespace digital_circuits {
	class circuit:public digital_object
	{
	protected:
		//int wire_count = 0;
		//int component_count = 0;
		std::vector<bool> state;
		std::vector<bool> new_state;
		std::vector<int> hidden{0};
		std::vector<std::unique_ptr<component>> components;
	public:
		circuit();
		circuit(int number_of_wires, bool default_wire_state=false);
		circuit(int number_of_wires, bool default_wire_state, std::wstring label);
		~circuit();
		//circuit& operator=(circuit other);
		void update();

		void print_state();
		std::vector<bool> get_state();
		void set_state(std::vector<bool> default_state);
		void reset_state();
		

		void add_wires(int wire_count);
		virtual void delete_wire(int n);
		virtual void delete_wires(std::vector<int> v);
		bool get_wire_state(int n);
		void set_wire_state(int n, bool value);
		void hide_wire(int n);
		void un_hide_all_wires();

		void add_component(std::unique_ptr<component> new_component);
		void replace_component(int n, std::unique_ptr<component> new_component);
		virtual void delete_component();
		std::wstring component_info(int n);
		void set_invert(int n, bool inverted);

		size_t size();
		size_t component_count();
		void print_info();
		bool acyclic();

		auto lambda_update();
		auto to_logic_gate_update();

		void simulate_cli(int steps);
		void debug();
	};
}


#endif

