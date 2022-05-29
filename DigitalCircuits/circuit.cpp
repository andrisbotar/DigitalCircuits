//Defines a class for storing a circuit with multiple inputs, outputs and update functionality

#include "circuit.h"
#include <iostream>
using namespace digitalc;

//Circuit constructors and destructors first
Circuit::Circuit() {}
Circuit::Circuit(int number_of_wires, bool default_wire_state){
    this->state = std::vector<bool>(number_of_wires, default_wire_state);
    this->new_state = std::vector<bool>(number_of_wires, default_wire_state);
}
Circuit::~Circuit(){
    //Cleanup memory
    std::wcout << "Destroying Circuit of size " << size() <<" with " <<components.size() << " components\n";
    //for (auto vectorit = components.begin(); vectorit < components.end(); ++vectorit)        delete vectorit;
    components.clear();
    state.clear();
    new_state.clear();
}

/*Circuit& Circuit::operator=(Circuit other)
{
    if (this != &other)
    {
        delete[] name;
        // This is a dangerous point in the flow of execution!
        // We have temporarily invalidated the class invariants,
        // and the next statement might throw an exception,
        // leaving the object in an invalid state :(
        name = new char[strlen(that.name) + 1];
        strcpy(name, that.name);
        age = that.age;
    }
    return *this;
}*/

//Core updating logic
void Circuit::update() {
    for (const auto& item : components) {
        item->update(state, new_state);
    }
    //new_state[0] = defaul_wire_state 
    state.swap(new_state);
}

//Reset circuit if needed
void Circuit::reset_state()
{
    this->state = std::vector<bool>(state.size(), false);
    this->new_state = std::vector<bool>(state.size(), false);
}

void Circuit::reset_state(std::vector<bool> default_state)
{
    this->state = default_state;
    this->new_state = default_state;
}

//acting on individual wires
void Circuit::addwires(int wire_count) {
    if (wire_count < 0) {
        std::wcout << "Cannot add negative number of wires.";
        return;
    }
    size_t new_size = state.size() + wire_count;
    state.resize(new_size);
}
void Circuit::deletewires() {}
bool Circuit::get_wire_state(int n) {
    return state[n];
}
void Circuit::set_wire_state(int n, bool value) {
    state[n] = value;
}

//acting on individual components
template<typename T>
void Circuit::addcomponent(std::unique_ptr<T> new_component) {
    components.push_back(std::move(new_component));
}
void Circuit::deletecomponent(){}
void Circuit::replacecomponent(int n, std::unique_ptr<component> new_component) {
    components[n] = move(new_component);
}
void Circuit::set_invert(int n, bool inverted)
{
    components[n]->set_inversion(inverted);
}
std::wstring Circuit::component_info(int n) {
    components[n]->info();
    return L"";
}

//Utility functions
size_t Circuit::size() {
    return state.size();
}
void Circuit::printstate() {
    for (auto i : state) {
        std::wcout << i << " ";
    }
    std::wcout << " \n";
}


//Simualtion
void Circuit::simulate_cli(int steps) {
    std::wcout << "   ";
    for (int i = 0; i < size(); ++i) { std::wcout << " " << i; }
    std::wcout << "\n---";
    for (int i = 0; i < size(); ++i) { std::wcout << "--"; }
    std::wcout << "\n";

    for (int i = 0; i < steps; ++i) {
        std::wcout << i << "|  ";
        printstate();
        update();
    }
}



//debug function
void Circuit::debug(int n) {
    //std::wcout << components.size() << " ";
    //std::wcout << this->state.size();
}



