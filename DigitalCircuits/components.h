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
		virtual ~component()=0; 
		virtual void info() = 0;
		//virtual void update() = 0;
	};

	//base class for logic gates
	class LogicGate :component
	{
	protected:
		std::vector<int> inputs{ 0,0 };
		int output = 0;

	public:
		LogicGate();
		LogicGate(int i1, int i2, int o);
		~LogicGate();
		virtual std::string gettype();
		virtual void info(); //virtual?
		//virtual void update() = 0;  
		virtual void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector)=0; //redundant?
	};

	//Definitions of logic gates:
	class ANDgate:public LogicGate
	{
	private:

	public:
		ANDgate();
		ANDgate(int i1,int i2,int o);
		~ANDgate();
		std::string gettype();
		//using LogicGate::LogicGate;
		//void update();
		void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector);
	};

	class ORgate :LogicGate
	{
	private:
		
	public:
		ORgate();
		ORgate(int i1, int i2, int o);
		~ORgate();
		std::string gettype();
		void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector);
	};



	//other components
	class constant_input:component
	{
	private:
		int output = 0;
		bool value = true;
	public:
		constant_input();
		constant_input(bool value, int output);
		~constant_input();
		std::string gettype();
		void info();
		void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector);
	};

}
#endif