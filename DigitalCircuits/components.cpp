// components.cpp : Specific circuit components, AND gates, OR gates, buffers...
#include <iostream>
#include "components.h"
#include <vector>
#include "utility.h"
using namespace digitalc;


//component::component(){}
component::~component(){}



LogicGate::LogicGate(){} //:type("Generic Logic Gate") {}

LogicGate::LogicGate(int i1, int i2, int o) //: type("Generic Logic Gate")
{
	this->inputs = std::vector<int>{ i1,i2 };
	this->output = o;
}

/*LogicGate::~LogicGate() {
	std::cout << "Destroying " << this->type << std::endl;
}*/
LogicGate::~LogicGate() {} //std::cout << "Destroying " << this->gettype() << std::endl; 

std::string LogicGate::gettype() { 	return std::string("Generic Logic Gate"); }

void LogicGate::update(std::vector<bool>& in_vector, std::vector<bool>& out_vector) {

	//std::cout << "inputs size: " << inputs.size() << "\n";
	//std::cout << "output: " << output << "\n";
	out_vector[output] = in_vector[inputs[0]];
	//std::cout << "updated!\n";
	//return input;
}

void LogicGate::info() {
	std::cout << "type: " << this->gettype() << "\n";
	std::cout << "output: " << this->output << "\n";
	std::cout << "inputs: ";
		for (auto i : this->inputs) { std::cout << i <<","; }
	std::cout << "\b "; //delete last comma
	std::cout << "\n";
}




ANDgate::ANDgate(){}

ANDgate::ANDgate(int i1, int i2, int o)
{
	this->inputs = std::vector<int>{i1,i2};
	this->output = o;
}

ANDgate::~ANDgate() { std::cout << "Destroying " << this->gettype() << std::endl; }

std::string ANDgate::gettype(){ return std::string("AND Gate"); }

void ANDgate::update(std::vector<bool>& in_vector, std::vector<bool>& out_vector) {
	out_vector[output] = in_vector[inputs[0]] && in_vector[inputs[1]];
}

/*void ANDgate::update() {
	out_vector[output] = in_vector[inputs[0]] && in_vector[inputs[1]];
}*/



ORgate::ORgate() {}

ORgate::ORgate(int i1, int i2, int o)
{
	this->inputs = std::vector<int>{ i1,i2 };
	this->output = o;
}

ORgate::~ORgate() {	std::cout << "Destroying " << this->gettype() << std::endl; }

std::string ORgate::gettype() { return std::string("OR Gate"); }

void ORgate::update(std::vector<bool>& in_vector, std::vector<bool>& out_vector) {
	out_vector[output] = in_vector[inputs[0]] || in_vector[inputs[1]];
}






constant_input::constant_input(){}

constant_input::constant_input(bool val, int out)
{
	this->value = val;
	this->output = out;
}

constant_input::~constant_input(){}

std::string constant_input::gettype(){ 	return std::string( "Constant input"); }

void constant_input::info() {
	std::cout << "type: " << this->gettype() << "\n";
	std::cout << "value: " << this->value << "\n";
}

void constant_input::update(std::vector<bool>& in_vector, std::vector<bool>& out_vector)
{
	out_vector[output] = value;
}
