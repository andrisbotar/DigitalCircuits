#pragma once

#include <vector>
#include <string>
//#include "circuit.h"

#ifndef __COMPONENTS__
#define __COMPONENTS__
namespace digitalc {
	
	//Abstract base class for all circuit components
	class component
	{
	public:
		//component();
		virtual ~component(){};
		virtual void info() = 0;
		virtual void set_inversion(bool b)=0;
		virtual void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector) = 0;
		//virtual void update() = 0;
	};

	//Base class for logic gates
	class LogicGate :public component
	{
	protected:
		std::vector<int> inputs{ 0,0 };
		int output{ 0 };
		bool inverting{ false };
	public:
		LogicGate();
		LogicGate(int i1, int i2, int o);
		~LogicGate();
		virtual std::wstring gettype();
		virtual void set_inversion(bool b);
		virtual void info(); //virtual?
		virtual void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector);
		//virtual void update() = 0; 
		//std::vector<bool> truth_table();
	};

	//Common logic gates:
	class ANDgate:public LogicGate
	{
	private:

	public:
		ANDgate();
		ANDgate(int i1,int i2,int o);
		~ANDgate();
		std::wstring gettype();
		void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector);
		//using LogicGate::LogicGate;
	};

	class ORgate : public LogicGate
	{
	private:
		
	public:
		ORgate();
		ORgate(int i1, int i2, int o);
		~ORgate();
		std::wstring gettype();
		void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector);
	};

	class XORgate : public LogicGate
	{
	private:
		std::wstring gettype();
	public:
		XORgate();
		XORgate(int i1, int i2, int o);
		~XORgate();
		void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector);
	};

	//Unitary logic gates
	class NOTgate :public LogicGate
	{
	private:
		//int output = 0;
	public:
		NOTgate();
		NOTgate(int i1, int o);
		~NOTgate();
		std::wstring gettype();
		void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector);
	};

	class buffer :public LogicGate
	{
	private:
		//int output = 0;
	public:
		buffer();
		buffer(int i1, int o);
		~buffer();
		std::wstring gettype();
		void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector);
	};

	//Nullary constant 
	class constant_input :public LogicGate
	{
	private:
		//int output = 0;
	public:
		constant_input();
		constant_input(bool value, int output);
		~constant_input();
		std::wstring gettype();
		void info();
		void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector);
	};

	//Other, less common components
	//Majority function:  evaluates to false when half or more arguments are false and true otherwise
	//i.e. the value of the function equals the value of the majority of the inputs
	class Majorityfunction :public LogicGate
	{
	private:
		
	public:
		Majorityfunction();
		Majorityfunction(int i1, int i2, int o);
		~Majorityfunction();
		std::wstring gettype();
		void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector);
	};

	//Wrapper to package an entire circuit as a single component
	class SubCircuitComponent :public LogicGate
	{
	private:
		std::wstring gettype();
		//digitalc::Circuit subcirsdfdfcuit();
	public:
		SubCircuitComponent();
		SubCircuitComponent(int i1, int i2, int o);
		//SubCircuitComponent(int i1, int i2, int o, Circuit subcircuit);
		~SubCircuitComponent();
		void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector);
	};



}
#endif