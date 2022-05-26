//Define class for storign circuit with multiple inputs, outputs and update functionality

#include "circuit.h"
#include <iostream>
using namespace digitalc;

//Circuit constructors and destructors first
Circuit::Circuit() {}
Circuit::Circuit(int number_of_wires) {
    this->state = std::vector<bool>(number_of_wires, false);
    this->new_state = std::vector<bool>(number_of_wires, false);
}
Circuit::Circuit(int number_of_wires, bool default_wire_state){
    this->state = std::vector<bool>(number_of_wires, default_wire_state);
    this->new_state = std::vector<bool>(number_of_wires, default_wire_state);
}
Circuit::~Circuit(){
    //Cleanup memory
    std::cout << "Destroying Circuit of size " << size() <<" with " <<components.size() << " components\n";
    for (auto vectorit = components.begin(); vectorit < components.end(); ++vectorit)
        delete* vectorit;
    components.clear();
    state.clear();
    new_state.clear();
}

//Core updating logic
void Circuit::update() {
    for (auto item : components) {
        item->update(state, new_state);
    }
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
        std::cout << "Cannot add negative number of wires.";
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
void Circuit::addcomponent(component* c) {
    components.push_back(c);
}
void Circuit::deletecomponent(){}
void Circuit::replacecomponent(int n, component* new_component) {
    components[n] = new_component;
}
void Circuit::set_invert(int n, bool inverted)
{
    components[n]->set_inversion(inverted);
}
std::string Circuit::component_info(int n) {
    components[n]->info();
    return "";
}

//Utility functions
size_t Circuit::size() {
    return state.size();
}
void Circuit::printstate() {
    for (auto i : state) {
        std::cout << i << " ";
    }
    std::cout << " \n";
}


//Simualtion
void Circuit::simulate_cli(int steps) {
    std::cout << "   ";
    for (int i = 0; i < size(); ++i) { std::cout << " " << i; }
    std::cout << "\n---";
    for (int i = 0; i < size(); ++i) { std::cout << "--"; }
    std::cout << "\n";

    for (int i = 0; i < steps; ++i) {
        std::cout << i << "|  ";
        printstate();
        update();
    }
}



//debug function
void Circuit::debug(int n) {
    //std::cout << components.size() << " ";
    //std::cout << this->state.size();
}



