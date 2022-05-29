#pragma once

#include <vector>
#include <string>
//#include "circuit.h"
#include "otherclasses.h"

#ifndef __COMPONENTS__
#define __COMPONENTS__
namespace digital_circuits {
	
	//Abstract base class for all circuit components
	class component :public digital_object
	{
	public:
		//component();  
		virtual ~component();
		virtual void info() = 0;
		virtual std::vector<int> get_input() = 0;
		virtual int getoutput()=0;
		virtual void set_inversion(bool b)=0;
		virtual void set_input(int input_index, int new_value)= 0;
		virtual void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector) = 0;
		//virtual void update() = 0;
	};

	//Base class for logic gates
	class logic_gate :public component
	{
	protected:
		std::vector<int> inputs{ 0,0 };
		int output{ 0 };
		bool inverting{ false };
		virtual logic_gate* clone_impl() const = 0;
	public:
		logic_gate();
		//logic_gate(logic_gate L);
		logic_gate(int i1, int i2, int o);
		logic_gate(int i1, int i2, int o, std::wstring label);
		~logic_gate();
		virtual std::wstring get_type();
		virtual std::vector<int> get_input();
		virtual int getoutput();
		//virtual std::wstring getCNFsig();
		virtual void set_inversion(bool b);
		virtual void set_output(int new_value);
		virtual void set_input(int input_index,int new_value);
		virtual void info(); //virtual?
		virtual void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector);
		auto clone() const;
		//virtual void update() = 0; 
		//std::vector<bool> truth_table();
	};

	//Common logic gates:
	class and_gate:public logic_gate
	{
	private:
		virtual and_gate* clone_impl() const override;
	public:
		and_gate();
		and_gate(int i1,int i2,int o);
		~and_gate();
		std::wstring get_type();
		void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector);
		//using logic_gate::logic_gate;
	};

	class or_gate : public logic_gate
	{
	private:
		virtual or_gate* clone_impl() const override;
	public:
		or_gate();
		or_gate(int i1, int i2, int o);
		~or_gate();
		std::wstring get_type();
		void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector);
	};

	class xor_gate : public logic_gate
	{
	private:
		std::wstring get_type();
		virtual xor_gate* clone_impl() const override;
	public:
		xor_gate();
		xor_gate(int i1, int i2, int o);
		~xor_gate();
		void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector);
	};

	//Unitary logic gates
	class not_gate :public logic_gate
	{
	private:
		//int output = 0;
		virtual not_gate* clone_impl() const override;
	public:
		not_gate();
		not_gate(int i1, int o);
		~not_gate();
		std::wstring get_type();
		void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector);
	};

	class buffer :public logic_gate
	{
	private:
		//int output = 0;
		virtual buffer* clone_impl() const override;
	public:
		buffer();
		buffer(int i1, int o);
		~buffer();
		std::wstring get_type();
		void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector);
	};

	//Nullary constant 
	class constant_input :public logic_gate
	{
	private:
		//int output = 0;
		virtual constant_input* clone_impl() const override;
	public:
		constant_input();
		constant_input(bool value, int output);
		~constant_input();
		std::wstring get_type();
		void info();
		void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector);
	};

	//Other, less common components
	//Majority function:  evaluates to false when half or more arguments are false and true otherwise
	//i.e. the value of the function equals the value of the majority of the inputs
	class majority_function :public logic_gate
	{
	private:
		virtual majority_function* clone_impl() const override;
	public:
		majority_function();
		majority_function(int i1, int i2, int o);
		~majority_function();
		std::wstring get_type();
		void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector);
	};

	//Wrapper to package an entire circuit as a single component
	class sub_circuit_component :public logic_gate
	{
	private:
		std::wstring get_type();
		//digital_circuits::circuit subcirsdfdfcuit();
		virtual sub_circuit_component* clone_impl() const override;
	public:
		sub_circuit_component();
		sub_circuit_component(int i1, int i2, int o);
		//sub_circuit_component(int i1, int i2, int o, circuit subcircuit);
		~sub_circuit_component();
		void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector);
	};



}
#endif