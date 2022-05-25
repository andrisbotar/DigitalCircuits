// components.cpp : Specific circuit components, AND gates, OR gates, buffers...
#include <iostream>
#include "components.h"
#include <vector>
#include "utility.h"
using namespace digitalc;



//component::component(){}
//component::~component(){}
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
void LogicGate::set_inversion(bool b) {	inverting = b; }
void LogicGate::info() {
	std::cout << "Type: " << this->gettype() << "\n";
	std::cout << "Output: " << this->output << "\n";
	std::cout << "Inputs: ";
		for (auto i : this->inputs) { std::cout << i <<","; }
	std::cout << "\b \n"; //delete last comma
	std::cout << "Inverting: " << BoolToString(this->inverting);
	std::cout << "\n\n"; 
}
void LogicGate::update(std::vector<bool>& in_vector, std::vector<bool>& out_vector) {
	//std::cout << "inputs size: " << inputs.size() << "\n";
	//std::cout << "output: " << output << "\n";
	out_vector[output] = in_vector[inputs[0]];
	//std::cout << "updated!\n";
	//return input;
}



//Definitions for common logic gates
ANDgate::ANDgate(){}
ANDgate::ANDgate(int i1, int i2, int o)
{
	this->inputs = std::vector<int>{i1,i2};
	this->output = o;
}
ANDgate::~ANDgate() { std::cout << "Destroying " << this->gettype() << std::endl; }
std::string ANDgate::gettype(){ return std::string(inverting ? "Inverting " : "") + std::string("AND Gate"); }
void ANDgate::update(std::vector<bool>& in_vector, std::vector<bool>& out_vector) {
	//out_vector[output] = in_vector[inputs[0]] && in_vector[inputs[1]];
	//std::all_of(vec.begin(), vec.end(), [](bool x) { return x; });
	bool result = true;
	for (auto index : inputs){
		if (index >= 0 && index < in_vector.size())
			result = result && in_vector[index];
	}
	out_vector[output] = (inverting != result);
}

ORgate::ORgate() {}
ORgate::ORgate(int i1, int i2, int o)
{
	this->inputs = std::vector<int>{ i1,i2 };
	this->output = o;
}
ORgate::~ORgate() {	std::cout << "Destroying " << this->gettype() << std::endl; }
std::string ORgate::gettype() { return std::string(inverting ? "Inverting " : "") + std::string("OR Gate"); }
void ORgate::update(std::vector<bool>& in_vector, std::vector<bool>& out_vector) {
	//out_vector[output] = in_vector[inputs[0]] || in_vector[inputs[1]];
	//std::any_of(vec.begin(), vec.end(), [](bool x) { return x; } )
	bool result = false;
	for (auto index : inputs) {
		if (index >= 0 && index < in_vector.size())
			result = result || in_vector[index];
	}
	out_vector[output] = (inverting != result);
}


XORgate::XORgate() {}
XORgate::XORgate(int i1, int i2, int o)
{
	this->inputs = std::vector<int>{ i1,i2 };
	this->output = o;
}
XORgate::~XORgate() { std::cout << "Destroying " << this->gettype() << std::endl; }
std::string XORgate::gettype() { return std::string(inverting ? "Inverting " : "") + std::string("XOR Gate"); }
void XORgate::update(std::vector<bool>& in_vector, std::vector<bool>& out_vector) {
	//out_vector[output] = in_vector[inputs[0]] || in_vector[inputs[1]];
	//std::any_of(vec.begin(), vec.end(), [](bool x) { return x; } )
	bool result = false;
	for (auto index : inputs) {
		if (index >= 0 && index < in_vector.size())
			result = (!result != !in_vector[index]);
	}
	out_vector[output] = (inverting != result);
}


NOTgate::NOTgate() {}
NOTgate::NOTgate(int i1, int o)
{
	this->inputs = std::vector<int>{ i1 };
	this->output = o;
}
NOTgate::~NOTgate() { std::cout << "Destroying " << this->gettype() << std::endl; }
std::string NOTgate::gettype() { return std::string(inverting ? "Inverting " : "") + std::string("NOT Gate"); }
void NOTgate::update(std::vector<bool>& in_vector, std::vector<bool>& out_vector) {
	//out_vector[output] = in_vector[inputs[0]] || in_vector[inputs[1]];
	//std::any_of(vec.begin(), vec.end(), [](bool x) { return x; } )
	out_vector[output] = (inverting != (!in_vector[inputs[0]]));
}


buffer::buffer() {}
buffer::buffer(int i1, int o)
{
	this->inputs = std::vector<int>{ i1 };
	this->output = o;
}
buffer::~buffer() { std::cout << "Destroying " << this->gettype() << std::endl; }
std::string buffer::gettype() { return std::string(inverting ? "Inverting " : "") + std::string("Buffer"); }
void buffer::update(std::vector<bool>& in_vector, std::vector<bool>& out_vector) {
	//out_vector[output] = in_vector[inputs[0]] || in_vector[inputs[1]];
	//std::any_of(vec.begin(), vec.end(), [](bool x) { return x; } )
	out_vector[output] = (inverting != in_vector[inputs[0]]);
}


constant_input::constant_input() {}
constant_input::constant_input(bool val, int out)
{
	this->set_inversion(val);
	this->output = out;
}
constant_input::~constant_input() { std::cout << "Destroying " << this->gettype() << std::endl; }
std::string constant_input::gettype() { return std::string("Constant " + BoolToString(inverting) + " input"); }
void constant_input::info() {
	std::cout << "type: " << this->gettype() << "\n";
	std::cout << "value: " << this->inverting << "\n";
}
void constant_input::update(std::vector<bool>& in_vector, std::vector<bool>& out_vector)
{
	out_vector[output] = inverting;
}


//Other, less common components
Majorityfunction::Majorityfunction() {}
Majorityfunction::Majorityfunction(int i1, int i2, int o)
{
	this->inputs = std::vector<int>{ i1,i2 };
	this->output = o;
}
Majorityfunction::~Majorityfunction() { std::cout << "Destroying " << this->gettype() << std::endl; }
std::string Majorityfunction::gettype() { return std::string(inverting ? "Inverting " : "") + std::string("Majority Function"); }
void Majorityfunction::update(std::vector<bool>& in_vector, std::vector<bool>& out_vector) {
	//out_vector[output] = in_vector[inputs[0]] && in_vector[inputs[1]];
	//std::all_of(vec.begin(), vec.end(), [](bool x) { return x; });
	int true_count = 0;
	int count = 0;
	for (auto index : inputs) {
		if (index >= 0 && index < in_vector.size()) {
			count++;
			if (in_vector[index]) { true_count++; };
		}
	}

	bool result = false;
	if (true_count > floor(count / 2)) { result = true; }

	out_vector[output] = (inverting != result);
}




