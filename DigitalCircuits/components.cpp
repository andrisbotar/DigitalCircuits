// components.cpp : Specific circuit components, AND gates, OR gates, buffers...
#include <iostream>
#include "components.h"
#include <vector>
#include "utility.h"
//using namespace std::remove_cvref;
using namespace digitalc;



//component::component(){}
//component::~component(){}
LogicGate::LogicGate(){} //:type("Generic Logic Gate") {}
LogicGate::LogicGate(int i1, int i2, int o) //: type("Generic Logic Gate")
{
	this->inputs = std::vector<int>{ i1,i2 };
	this->output = o;
}
/*digitalc::LogicGate::LogicGate(std::wstring type_string, int i1, int i2, int o)
{
	const std::wstring empty = L"";
	std::wstring type(empty);
	if (type_string.substr(0, type_string.find(L" ")) == L"Inverting") {
		type = empty;
	}

	if (type == L"AND Gate") { this = ORgate(i1, i2, o); }
	else{
		this->inputs = std::vector<int>{ i1,i2 };
		this->output = o;
	}
}*/
LogicGate::~LogicGate() {}//std::wcout << "Destroying " << this->gettype() << std::endl; }
std::wstring LogicGate::gettype() { 	return std::wstring(L"Generic Logic Gate"); }
void LogicGate::set_inversion(bool b) {	inverting = b; }
void LogicGate::info() {
	std::wcout << L"Type: " << this->gettype() << "\n";
	std::wcout << L"Output: " << this->output << "\n";
	std::wcout << L"Inputs: ";
		for (auto i : this->inputs) { std::wcout << i <<","; }
	std::wcout << L"\b \n"; //delete last comma
	std::wcout << L"Inverting: " << BoolToString(this->inverting);
	std::wcout << L"\n\n";
}
void LogicGate::update(std::vector<bool>& in_vector, std::vector<bool>& out_vector) {
	//std::wcout << "inputs size: " << inputs.size() << "\n";
	//std::wcout << "output: " << output << "\n";
	out_vector[output] = in_vector[inputs[0]];
	//std::wcout << "updated!\n";
	//return input;
}




//Definitions for common logic gates
ANDgate::ANDgate(){}
ANDgate::ANDgate(int i1, int i2, int o)
{
	this->inputs = std::vector<int>{i1,i2};
	this->output = o;
}
ANDgate::~ANDgate() { std::wcout << L"Destroying " << this->gettype() << std::endl; }
std::wstring ANDgate::gettype(){ return std::wstring(inverting ? L"Inverting " : L"") + std::wstring(L"AND Gate"); }
void ANDgate::update(std::vector<bool>& in_vector, std::vector<bool>& out_vector) {
	//out_vector[output] = in_vector[inputs[0]] && in_vector[inputs[1]];
	//std::all_of(vec.begin(), vec.end(), [](bool x) { return x; });
	bool result = true;
	for (auto index : inputs){
		if (index >= 0 && index < in_vector.size())
			result = result && in_vector[index];
		//std::wcout << "AAAAAA" << in_vector[index];
	}
	out_vector[output] = (inverting != result);
}

ORgate::ORgate() {}
ORgate::ORgate(int i1, int i2, int o)
{
	this->inputs = std::vector<int>{ i1,i2 };
	this->output = o;
}
ORgate::~ORgate() {	std::wcout << L"Destroying " << this->gettype() << std::endl; }
std::wstring ORgate::gettype() { return std::wstring(inverting ? L"Inverting " : L"") + std::wstring(L"OR Gate"); }
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
XORgate::~XORgate() { std::wcout << L"Destroying " << this->gettype() << std::endl; }
std::wstring XORgate::gettype() { return std::wstring(inverting ? L"Inverting " : L"") + std::wstring(L"XOR Gate"); }
void XORgate::update(std::vector<bool>& in_vector, std::vector<bool>& out_vector) {
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
NOTgate::~NOTgate() { std::wcout << L"Destroying " << this->gettype() << std::endl; }
std::wstring NOTgate::gettype() { return std::wstring(inverting ? L"Inverting " : L"") + std::wstring(L"NOT Gate"); }
void NOTgate::update(std::vector<bool>& in_vector, std::vector<bool>& out_vector) {
	out_vector[output] = (inverting != (!in_vector[inputs[0]]));
}


buffer::buffer() {}
buffer::buffer(int i1, int o)
{
	this->inputs = std::vector<int>{ i1 };
	this->output = o;
}
buffer::~buffer() { std::wcout << L"Destroying " << this->gettype() << std::endl; }
std::wstring buffer::gettype() { return std::wstring(inverting ? L"Inverting " : L"") + std::wstring(L"Buffer"); }
void buffer::update(std::vector<bool>& in_vector, std::vector<bool>& out_vector) {
	out_vector[output] = (inverting != in_vector[inputs[0]]);
}


constant_input::constant_input() {}
constant_input::constant_input(bool val, int out)
{
	this->set_inversion(val);
	this->output = out;
}
constant_input::~constant_input() { std::wcout << L"Destroying " << this->gettype() << std::endl; }
std::wstring constant_input::gettype() { return std::wstring(L"Constant " + BoolToString(inverting) + L" input"); }
void constant_input::info() {
	std::wcout << L"type: " << this->gettype() << "\n";
	std::wcout << L"value: " << this->inverting << "\n";
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
Majorityfunction::~Majorityfunction() { std::wcout << L"Destroying " << this->gettype() << std::endl; }
std::wstring Majorityfunction::gettype() { return std::wstring(inverting ? L"Inverting " : L"") + std::wstring(L"Majority Function"); }
void Majorityfunction::update(std::vector<bool>& in_vector, std::vector<bool>& out_vector) {
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



SubCircuitComponent::SubCircuitComponent() {}
SubCircuitComponent::SubCircuitComponent(int i1, int i2, int o)
{
	this->inputs = std::vector<int>{ i1,i2 };
	this->output = o;
}
/*SubCircuitComponent::SubCircuitComponent(int i1, int i2, int o, Circuit subcircuit)
{
	this->subcircuit = subcircuit;
	this->inputs = std::vector<int>{ i1,i2 };
	this->output = o;
}*/
SubCircuitComponent::~SubCircuitComponent() { std::wcout << L"Destroying " << this->gettype() << std::endl; }
std::wstring SubCircuitComponent::gettype() { return std::wstring(inverting ? L"Inverting " : L"") + std::wstring(L"XOR Gate"); }
void SubCircuitComponent::update(std::vector<bool>& in_vector, std::vector<bool>& out_vector) {


	bool result = false;
	for (auto index : inputs) {
		if (index >= 0 && index < in_vector.size())
			result = (!result != !in_vector[index]);
	}
	out_vector[output] = (inverting != result);
}







