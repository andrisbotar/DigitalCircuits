#pragma once

#include <vector>
#include <string>

#ifndef __COMPONENTS__
#define __COMPONENTS__
namespace digitalc {
	
	//abstract base class for all circuit components
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

	//base class for logic gates
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

	//Definitions of logic gates:
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

	class constant_input:public LogicGate
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

	//other components
}
#endif