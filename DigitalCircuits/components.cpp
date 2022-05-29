// components.cpp : Specific circuit components, AND gates, OR gates, buffers...
#include <iostream>
#include <vector>
#include "components.h"
#include "utility.h"
#include "otherclasses.h"
//using namespace std::remove_cvref;
using namespace digital_circuits;


//init global variables for keepign track of components
int COMPONENTCOUNT{ 0 };

//component::component(){ label = L"circuit " + std::to_wstring(COMPONENTCOUNT); COMPONENTCOUNT++; } //wouldn't make component an abstract base class anymore
component::~component(){}

logic_gate::logic_gate(){ label = L"Component " + std::to_wstring(COMPONENTCOUNT); COMPONENTCOUNT++; } //:type("Generic Logic Gate") {}
logic_gate::logic_gate(int i1, int i2, int o) 
{
	label = L"Component " + std::to_wstring(COMPONENTCOUNT); COMPONENTCOUNT++;
	this->inputs = std::vector<int>{ i1,i2 };
	this->output = o;
}
logic_gate::logic_gate(int i1, int i2, int o, std::wstring label)
{
	label = label; COMPONENTCOUNT++;
	this->inputs = std::vector<int>{ i1,i2 };
	this->output = o;
}
/*digital_circuits::logic_gate::logic_gate(std::wstring type_string, int i1, int i2, int o)
{
	const std::wstring empty = L"";
	std::wstring type(empty);
	if (type_string.substr(0, type_string.find(L" ")) == L"Inverting") {
		type = empty;
	}

	if (type == L"AND Gate") { this = or_gate(i1, i2, o); }
	else{
		this->inputs = std::vector<int>{ i1,i2 };
		this->output = o;
	}
}*/
logic_gate::~logic_gate() {}//std::wcout << "Destroying " << this->get_type() << std::endl; }
std::wstring logic_gate::get_type() { 	return std::wstring(L"Generic Logic Gate"); }
std::vector<int> digital_circuits::logic_gate::get_input()
{
	return inputs;
}
int digital_circuits::logic_gate::getoutput()
{
	return this->output;
}
void logic_gate::set_inversion(bool b) {	inverting = b; }
void digital_circuits::logic_gate::set_output(int new_value)
{
	this->output = new_value;
}
void digital_circuits::logic_gate::set_input(int input_index, int new_value)
{
	this->inputs[input_index] = new_value;
}
void logic_gate::info() {
	std::wcout << L"Label: " << label << "\n";
	std::wcout << L"Type: " << this->get_type() << "\n";
	std::wcout << L"Input wires: ";
		for (auto i : this->inputs) { std::wcout << i <<","; }
	std::wcout << L"\b \n"; //delete last comma
	std::wcout << L"Output wire: " << this->output << "\n";
	//std::wcout << L"Inverting: " << bool_to_string(this->inverting);
	//std::wcout << L"\n";
}
void logic_gate::update(std::vector<bool>& in_vector, std::vector<bool>& out_vector) {
	//std::wcout << "inputs size: " << inputs.size() << "\n";
	//std::wcout << "output: " << output << "\n";
	out_vector[output] = in_vector[inputs[0]];
	//std::wcout << "updated!\n";
	//return input;
}

auto digital_circuits::logic_gate::clone() const{
	return std::unique_ptr<logic_gate>(clone_impl());
}




//Definitions for common logic gates
and_gate::and_gate(){}
and_gate::and_gate(int i1, int i2, int o)
{
	this->inputs = std::vector<int>{i1,i2};
	this->output = o;
}
and_gate::~and_gate() { std::wcout << L"Destroying " << this->get_type() << std::endl; }
std::wstring and_gate::get_type(){ return std::wstring(inverting ? L"Inverting " : L"") + std::wstring(L"AND Gate"); }
void and_gate::update(std::vector<bool>& in_vector, std::vector<bool>& out_vector) {
	//out_vector[output] = in_vector[inputs[0]] && in_vector[inputs[1]];
	//std::all_of(vec.begin(), vec.end(), [](bool x) { return x; });
	bool result = true;
	for (auto index : inputs){
		if (index >= 0 && index < in_vector.size())
			result = result && in_vector[index];
	}
	out_vector[output] = (inverting != result);
}
and_gate* and_gate::clone_impl() const { return new and_gate(*this); };

or_gate::or_gate() {}
or_gate::or_gate(int i1, int i2, int o)
{
	this->inputs = std::vector<int>{ i1,i2 };
	this->output = o;
}
or_gate::~or_gate() {	std::wcout << L"Destroying " << this->get_type() << std::endl; }
std::wstring or_gate::get_type() { return std::wstring(inverting ? L"Inverting " : L"") + std::wstring(L"OR Gate"); }
void or_gate::update(std::vector<bool>& in_vector, std::vector<bool>& out_vector) {
	//out_vector[output] = in_vector[inputs[0]] || in_vector[inputs[1]];
	//std::any_of(vec.begin(), vec.end(), [](bool x) { return x; } )
	bool result = false;
	for (auto index : inputs) {
		if (index >= 0 && index < in_vector.size())
			result = result || in_vector[index];
	}
	out_vector[output] = (inverting != result);
}
or_gate* or_gate::clone_impl() const { return new or_gate(*this); };



xor_gate::xor_gate() {}
xor_gate::xor_gate(int i1, int i2, int o)
{
	this->inputs = std::vector<int>{ i1,i2 };
	this->output = o;
}
xor_gate::~xor_gate() { std::wcout << L"Destroying " << this->get_type() << std::endl; }
std::wstring xor_gate::get_type() { return std::wstring(inverting ? L"Inverting " : L"") + std::wstring(L"XOR Gate"); }
void xor_gate::update(std::vector<bool>& in_vector, std::vector<bool>& out_vector) {
	bool result = false;
	for (auto index : inputs) {
		if (index >= 0 && index < in_vector.size())
			result = (!result != !in_vector[index]);
	}
	out_vector[output] = (inverting != result);
}
xor_gate* xor_gate::clone_impl() const { return new xor_gate(*this); };


not_gate::not_gate() {}
not_gate::not_gate(int i1, int o)
{
	this->inputs = std::vector<int>{ i1 };
	this->output = o;
}
not_gate::~not_gate() { std::wcout << L"Destroying " << this->get_type() << std::endl; }
std::wstring not_gate::get_type() { return std::wstring(inverting ? L"Inverting " : L"") + std::wstring(L"NOT Gate"); }
void not_gate::update(std::vector<bool>& in_vector, std::vector<bool>& out_vector) {
	out_vector[output] = (inverting != (!in_vector[inputs[0]]));
}
not_gate* not_gate::clone_impl() const { return new not_gate(*this); };


buffer::buffer() {}
buffer::buffer(int i1, int o)
{
	this->inputs = std::vector<int>{ i1 };
	this->output = o;
}
buffer::~buffer() { std::wcout << L"Destroying " << this->get_type() << std::endl; }
std::wstring buffer::get_type() { return std::wstring(inverting ? L"Inverting " : L"") + std::wstring(L"Buffer"); }
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
constant_input::~constant_input() { std::wcout << L"Destroying " << this->get_type() << std::endl; }
std::wstring constant_input::get_type() { return std::wstring(L"Constant " + bool_to_string(inverting) + L" input"); }
void constant_input::info() {
	std::wcout << L"type: " << this->get_type() << "\n";
	std::wcout << L"value: " << this->inverting << "\n";
}
void constant_input::update(std::vector<bool>& in_vector, std::vector<bool>& out_vector)
{
	out_vector[output] = inverting;
}
constant_input* constant_input::clone_impl() const { return new constant_input(*this); };



//Other, less common components
majority_function::majority_function() {}
majority_function::majority_function(int i1, int i2, int o)
{
	this->inputs = std::vector<int>{ i1,i2 };
	this->output = o;
}
majority_function::~majority_function() { std::wcout << L"Destroying " << this->get_type() << std::endl; }
std::wstring majority_function::get_type() { return std::wstring(inverting ? L"Inverting " : L"") + std::wstring(L"Majority Function"); }
void majority_function::update(std::vector<bool>& in_vector, std::vector<bool>& out_vector) {
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
majority_function* majority_function::clone_impl() const { return new majority_function(*this); };



sub_circuit_component::sub_circuit_component() {}
sub_circuit_component::sub_circuit_component(int i1, int i2, int o)
{
	this->inputs = std::vector<int>{ i1,i2 };
	this->output = o;
}
/*sub_circuit_component::sub_circuit_component(int i1, int i2, int o, circuit subcircuit){
	this->subcircuit = subcircuit;
	this->inputs = std::vector<int>{ i1,i2 };
	this->output = o;
}*/
sub_circuit_component::~sub_circuit_component() { std::wcout << L"Destroying " << this->get_type() << std::endl; }
std::wstring sub_circuit_component::get_type() { return std::wstring(inverting ? L"Inverting " : L"") + std::wstring(L"XOR Gate"); }
void sub_circuit_component::update(std::vector<bool>& in_vector, std::vector<bool>& out_vector) {


	bool result = false;
	for (auto index : inputs) {
		if (index >= 0 && index < in_vector.size())
			result = (!result != !in_vector[index]);
	}
	out_vector[output] = (inverting != result);
}
sub_circuit_component* sub_circuit_component::clone_impl() const { return new sub_circuit_component(*this); };






