// components.cpp : Specific circuit components, AND gates, OR gates, buffers...
#include <iostream>
#include <vector>
#include "components.h"
#include "utility.h"
#include "otherclasses.h"
//using namespace std::remove_cvref;
using namespace digitalc;


//init global variables for keepign track of components
int COMPONENTCOUNT{ 0 };

//component::component(){ label = L"Circuit " + std::to_wstring(COMPONENTCOUNT); COMPONENTCOUNT++; } //wouldn't make component an abstract base class anymore
component::~component(){}

LogicGate::LogicGate(){ label = L"Component " + std::to_wstring(COMPONENTCOUNT); COMPONENTCOUNT++; } //:type("Generic Logic Gate") {}
LogicGate::LogicGate(int i1, int i2, int o) 
{
	label = L"Circuit " + std::to_wstring(COMPONENTCOUNT); COMPONENTCOUNT++;
	this->inputs = std::vector<int>{ i1,i2 };
	this->output = o;
}
LogicGate::LogicGate(int i1, int i2, int o, std::wstring label)
{
	label = label; COMPONENTCOUNT++;
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
std::vector<int> digitalc::LogicGate::getinput()
{
	return inputs;
}
int digitalc::LogicGate::getoutput()
{
	return this->output;
}
void LogicGate::set_inversion(bool b) {	inverting = b; }
void digitalc::LogicGate::setoutput(int new_value)
{
	this->output = new_value;
}
void digitalc::LogicGate::setinput(int input_index, int new_value)
{
	this->inputs[input_index] = new_value;
}
void LogicGate::info() {
	std::wcout << L"Label: " << label << "\n";
	std::wcout << L"Type: " << this->gettype() << "\n";
	std::wcout << L"Input wires: ";
		for (auto i : this->inputs) { std::wcout << i <<","; }
	std::wcout << L"\b \n"; //delete last comma
	std::wcout << L"Output wire: " << this->output << "\n";
	//std::wcout << L"Inverting: " << BoolToString(this->inverting);
	//std::wcout << L"\n";
}
void LogicGate::update(std::vector<bool>& in_vector, std::vector<bool>& out_vector) {
	//std::wcout << "inputs size: " << inputs.size() << "\n";
	//std::wcout << "output: " << output << "\n";
	out_vector[output] = in_vector[inputs[0]];
	//std::wcout << "updated!\n";
	//return input;
}

auto digitalc::LogicGate::clone() const{
	return std::unique_ptr<LogicGate>(clone_impl());
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
	}
	out_vector[output] = (inverting != result);
}
ANDgate* ANDgate::clone_impl() const { return new ANDgate(*this); };

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
ORgate* ORgate::clone_impl() const { return new ORgate(*this); };



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
XORgate* XORgate::clone_impl() const { return new XORgate(*this); };


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
NOTgate* NOTgate::clone_impl() const { return new NOTgate(*this); };


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
buffer* buffer::clone_impl() const { return new buffer(*this); };


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
constant_input* constant_input::clone_impl() const { return new constant_input(*this); };



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
Majorityfunction* Majorityfunction::clone_impl() const { return new Majorityfunction(*this); };



SubCircuitComponent::SubCircuitComponent() {}
SubCircuitComponent::SubCircuitComponent(int i1, int i2, int o)
{
	this->inputs = std::vector<int>{ i1,i2 };
	this->output = o;
}
/*SubCircuitComponent::SubCircuitComponent(int i1, int i2, int o, Circuit subcircuit){
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
SubCircuitComponent* SubCircuitComponent::clone_impl() const { return new SubCircuitComponent(*this); };






