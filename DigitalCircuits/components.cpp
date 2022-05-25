// components.cpp : Specific circuit components, AND gates, OR gates, buffers...
#include <iostream>
#include "components.h"
#include <vector>
#include "utility.h"
using namespace digitalc;


//component::component(){}
component::~component(){}



LogicGate::LogicGate(): type("Generic Logic Gate") {}

LogicGate::LogicGate(int i1, int i2, int o) : type("Generic Logic Gate")
{
	this->inputs = std::vector<int>{ i1,i2 };
	this->output = o;
}

LogicGate::LogicGate(int i1, int i2, int o, std::string type_name)
{
	this->inputs = std::vector<int>{ i1,i2 };
	this->output = o;
	this->type = type_name;
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

void LogicGate::info() {
	std::cout << "type: " << this->type << "\n";
}




ANDgate::ANDgate() : type("AND Gate") {}

ANDgate::ANDgate(int i1, int i2, int o) : LogicGate(i1,  i2,  o, "AND Gate")
{
	//this->inputs = std::vector<int>{i1,i2};
	//this->output = o;
}

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




constant_input::constant_input()
{
}

constant_input::constant_input(bool val, int out)
{
	this->value = val;
	this->output = out;
}

constant_input::~constant_input()
{
}

void constant_input::info() {
	std::cout << "type: " << this->type << "\n";
}

void constant_input::update(std::vector<bool>& out_vector)
{
	out_vector[output] = value;
}
