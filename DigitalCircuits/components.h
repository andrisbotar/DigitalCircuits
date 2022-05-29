#pragma once

#include <vector>
#include <string>
//#include "circuit.h"
#include "otherclasses.h"

#ifndef __COMPONENTS__
#define __COMPONENTS__
namespace digitalc {
	
	//Abstract base class for all circuit components
	class component :public digital_object
	{
	public:
		//component();  
		virtual ~component();
		virtual void info() = 0;
		virtual std::vector<int> getinput() = 0;
		virtual void set_inversion(bool b)=0;
		virtual void setinput(int input_index, int new_value)= 0;
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
		virtual LogicGate* clone_impl() const = 0;
	public:
		LogicGate();
		//LogicGate(LogicGate L);
		LogicGate(int i1, int i2, int o);
		LogicGate(int i1, int i2, int o, std::wstring label);
		~LogicGate();
		virtual std::wstring gettype();
		virtual std::vector<int> getinput();
		virtual int getoutput();
		//virtual std::wstring getCNFsig();
		virtual void set_inversion(bool b);
		virtual void setoutput(int new_value);
		virtual void setinput(int input_index,int new_value);
		virtual void info(); //virtual?
		virtual void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector);
		auto clone() const;
		//virtual void update() = 0; 
		//std::vector<bool> truth_table();
	};

	//Common logic gates:
	class ANDgate:public LogicGate
	{
	private:
		virtual ANDgate* clone_impl() const override;
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
		virtual ORgate* clone_impl() const override;
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
		virtual XORgate* clone_impl() const override;
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
		virtual NOTgate* clone_impl() const override;
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
		virtual buffer* clone_impl() const override;
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
		virtual constant_input* clone_impl() const override;
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
		virtual Majorityfunction* clone_impl() const override;
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
		virtual SubCircuitComponent* clone_impl() const override;
	public:
		SubCircuitComponent();
		SubCircuitComponent(int i1, int i2, int o);
		//SubCircuitComponent(int i1, int i2, int o, Circuit subcircuit);
		~SubCircuitComponent();
		void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector);
	};



}
#endif