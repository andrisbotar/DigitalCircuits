// components.cpp : Specific circuit components, AND gates, OR gates, buffers...
#include <iostream>
#include "components.h"
#include <vector>
#include "utility.h"
using namespace digitalc;


//component::component(){}
//component::~component(){}



LogicGate::LogicGate() {
}

LogicGate::LogicGate(int i1, int i2, int o)
{
	this->inputs = std::vector<int>{ i1,i2 };
	this->output = o;
}

/*LogicGate::~LogicGate() {
	std::cout << "Destroying " << this->type << std::endl;
}*/
LogicGate::~LogicGate() {}

void LogicGate::update(std::vector<bool>& in_vector, std::vector<bool>& out_vector) {

	//std::cout << "inputs size: " << inputs.size() << "\n";
	//std::cout << "output: " << output << "\n";
	out_vector[output] = in_vector[inputs[0]];
	//std::cout << "updated!\n";
	//return input;
}



//ANDgate::ANDgate() {}

/*ANDgate::ANDgate(int i1, int i2, int o)
{
	this->inputs = std::vector<int>{i1,i2};
	this->output = o;
}*/

ANDgate::~ANDgate() { std::cout << "Destroying " << this->type << std::endl; }

void ANDgate::update(std::vector<bool>& in_vector, std::vector<bool>& out_vector) {
	out_vector[output] = in_vector[inputs[0]] && in_vector[inputs[1]];
}




ORgate::~ORgate() {
	std::cout << "Destroying " << type << std::endl;
}

void ORgate::update(std::vector<bool>& in_vector, std::vector<bool>& out_vector) {
	out_vector[output] = in_vector[inputs[0]] || in_vector[inputs[1]];
}


