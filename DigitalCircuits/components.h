#pragma once

#include <vector>
#include <string>

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
		int output = 0;
		virtual std::string gettype();
		bool inverting = false;
	public:
		LogicGate();
		LogicGate(int i1, int i2, int o);
		~LogicGate();
		virtual void set_inversion(bool b);
		virtual void info(); //virtual?
		//virtual void update() = 0;  
		virtual void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector)=0; 
	};

	//Common logic gates:
	class ANDgate:public LogicGate
	{
	private:
		std::string gettype();
	public:
		ANDgate();
		ANDgate(int i1,int i2,int o);
		~ANDgate();
		void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector);
		//using LogicGate::LogicGate;
	};

	class ORgate : public LogicGate
	{
	private:
		std::string gettype();
	public:
		ORgate();
		ORgate(int i1, int i2, int o);
		~ORgate();
		void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector);
	};

	class XORgate : public LogicGate
	{
	private:
		std::string gettype();
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
		int output = 0;
		std::string gettype();
	public:
		NOTgate();
		NOTgate(int i1, int o);
		~NOTgate();
		void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector);
	};

	class buffer :public LogicGate
	{
	private:
		int output = 0;
		std::string gettype();
	public:
		buffer();
		buffer(int i1, int o);
		~buffer();
		void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector);
	};

	//Nullary constant 
	class constant_input :public LogicGate
	{
	private:
		int output = 0;
		std::string gettype();
	public:
		constant_input();
		constant_input(bool value, int output);
		~constant_input();
		void info();
		void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector);
	};

	//Other, less common components
	//Majority function:  evaluates to false when half or more arguments are false and true otherwise
	//i.e. the value of the function equals the value of the majority of the inputs
	class Majorityfunction :public LogicGate
	{
	private:
		std::string gettype();
	public:
		Majorityfunction();
		Majorityfunction(int i1, int i2, int o);
		~Majorityfunction();
		void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector);
	};
}
#endif