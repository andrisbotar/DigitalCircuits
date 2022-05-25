#pragma once

#include <vector>
#include <string>

#ifndef __COMPONENTS__
#define __COMPONENTS__
namespace digitalc {
	
	//abstract base class for all circuit components
	class component
	{
	protected:
		std::vector<int> inputs{ 0,0 };
		int output = 0;
		std::string type = "Generic digital component";
	public:
		//component();
		virtual ~component(){}; 
		virtual void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector)=0;
	};

	//base class for logic gates
	class LogicGate :component
	{
	protected:
		std::vector<int> inputs{ 0,0 };
		int output = 0;
		std::string type = "Generic Logic Gate";
	public:
		LogicGate();
		LogicGate(int i1, int i2, int o);
		~LogicGate();
		virtual void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector)=0;
	};

	//Definitions of logic gates:
	class ANDgate:LogicGate
	{
	private:
		std::string type = "AND Gate";
	public:
		//ANDgate();
		//ANDgate(int i1,int i2,int o);
		~ANDgate();
		using LogicGate::LogicGate;
		void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector);
	};

	class ORgate :LogicGate
	{
	private:
		std::string type = "OR Gate";
	public:
		~ORgate();
		using LogicGate::LogicGate;
		void update(std::vector<bool>& in_vector, std::vector<bool>& out_vector);
	};





}
#endif