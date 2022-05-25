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
    std::cout << "\nCleaning up memory.\n";
    for (auto vectorit = components.begin(); vectorit < components.end(); ++vectorit)
        delete* vectorit;
    components.clear();
    state.clear();
    new_state.clear();
}

//debug function
void Circuit::debug() {
    std::cout << components.size() << " ";
    std::cout << this->state.size();
}

//adding and deleting wires and components
void Circuit::addcomponent(component *c){
    components.push_back(c);
}
void Circuit::addwires(int wire_count) {
    if (wire_count < 0) {
        std::cout << "Cannot add negative number of wires.";
        return;
    }
    size_t new_size = state.size() + wire_count;
    state.resize(new_size);
}
void Circuit::deletewires(){}
void Circuit::deletecomponent(){}


//Updating logic
void Circuit::update(){
    for (auto item : components) {
        item->update(state, new_state);
    }
    state.swap(new_state);
}

//Display functionality
void Circuit::printstate(){
    for (auto i : state) {
        std::cout << i << " ";
    }
    std::cout << " \n";
}

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

//Simualtion
void Circuit::simulate_cli(int steps) {
    std::cout << "   ";
    for (int i = 0; i < state.size(); ++i) { std::cout << " " << i; }
    std::cout << "\n---";
    for (int i = 0; i < state.size(); ++i) { std::cout << "--"; }
    std::cout << "\n";

    for (int i = 0; i < 5; ++i) {
        std::cout << i << "|  ";
        printstate();
        for (auto item : components) {
            item->update(state, new_state);
        }
        state.swap(new_state);
    }
}





