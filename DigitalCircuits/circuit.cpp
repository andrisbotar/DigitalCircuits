//Defines a class for storing a circuit with multiple inputs, outputs and update functionality

#include <iostream>
#include "circuit.h"
#include "utility.h"
#include "otherclasses.h"
using namespace digitalc;

////init global variables for keepign track of circuits
int CIRCUITCOUNT{0};

//Circuit constructors and destructors first
Circuit::Circuit() { label = L"Circuit " + std::to_wstring(CIRCUITCOUNT); CIRCUITCOUNT++; }
Circuit::Circuit(int number_of_wires, bool default_wire_state){
    label = L"Circuit " + std::to_wstring(CIRCUITCOUNT); CIRCUITCOUNT++;
    this->state = std::vector<bool>(number_of_wires, default_wire_state);
    this->new_state = std::vector<bool>(number_of_wires, default_wire_state);
}
Circuit::Circuit(int number_of_wires, bool default_wire_state, std::wstring label) {
    label = label; CIRCUITCOUNT++;
    this->state = std::vector<bool>(number_of_wires, default_wire_state);
    this->new_state = std::vector<bool>(number_of_wires, default_wire_state);
}
Circuit::~Circuit(){
    //Cleanup memory
    std::wcout << "Destroying Circuit of size " << size() <<" with " << componentcount() << " components\n";
    //for (auto vectorit = components.begin(); vectorit < components.end(); ++vectorit)        delete vectorit;
    components.clear();
    state.clear();
    new_state.clear();
}
/*Circuit& Circuit::operator=(Circuit other){
    if (this != &other)
    {
        delete components;
        components = ;
        cpy(components, that.components);
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
void Circuit::printstate() {
    //for (auto i : state) {        std::wcout << i << " ";    }
    for (int i = 0; i < state.size(); ++i) {
        if(vector_contains <int,std::vector<int>> (i,hidden)){ continue; }
        std::wcout << state[i] << " ";
    }
    std::wcout << " \n";
}
//Reset circuit if needed
void Circuit::reset_state(){
    this->state = std::vector<bool>(state.size(), false);
    this->new_state = std::vector<bool>(state.size(), false);
}

void Circuit::reset_state(std::vector<bool> default_state){
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
void Circuit::deletewire(int n) {
    hidden.push_back(n);
    for (int i = 0; i < components.size(); ++i) {
        std::vector<int> v = components[i]->getinput();
        //std::wcout <<"\n"<< i << ": "; print_int_vector(v);
        for (int j=0; j< v.size();++j){
            if (v[j] == n) {
                components[i]->setinput(j, 0);
            }
            /*if (v[j] > n) {
                components[i]->setinput(j, v[j] -1);
            }*/
        }
    }
}
void Circuit::deletewires(std::vector<int> wirestodelete) {
    for (auto wireindex : wirestodelete) {
        this->deletewire(wireindex);
    }
}
bool Circuit::get_wire_state(int n) {
    return state[n];
}
void Circuit::set_wire_state(int n, bool value) {
    state[n] = value;
}
void Circuit::hidewire(int n) {
    hidden.push_back(n);
}
void Circuit::unhideallwires() {
    hidden.clear();
}


//acting on individual components
void Circuit::addcomponent(std::unique_ptr<component> new_component) {
    components.push_back(std::move(new_component));
}
void Circuit::replacecomponent(int n, std::unique_ptr<component> new_component) {
    components[n] = move(new_component);
}
void Circuit::deletecomponent(){}
void Circuit::set_invert(int n, bool inverted){
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
size_t Circuit::componentcount() {
    return components.size();
}
void Circuit::print_info() {
    std::wcout << "The circuit labelled '" << label << "' is currently in state: "; printstate();
    std::wcout << "It has " << size() << " wires and contains "<< componentcount() <<" components: \n";
    for (int i = 0; i < components.size(); ++i) { std::wcout << "- "; components[i]->info(); }
    //std::wcout<<"and has complexity: "<<complexity();
}

//Simualtion
void Circuit::simulate_cli(int steps) {
    std::wcout << "   ";
    for (int i = 0; i < size(); ++i) { 
        if (vector_contains <int, std::vector<int>>(i, hidden)) { continue; }
        std::wcout << " " << i; 
    }
    std::wcout << "\n---";
    for (int i = 0; i < size()-hidden.size() ; ++i) { std::wcout << "--"; }
    std::wcout << "\n";

    for (int i = 0; i < steps; ++i) {
        std::wcout << i << "|  ";
        printstate();
        update();
    }
}



//debug function
void Circuit::debug() {

    for (int i = 0; i < components.size(); ++i) {
        std::vector<int> v = components[4]->getinput();
        printvector<int>(v);
    }

    //std::wcout << components.size() << " ";
    //std::wcout << this->state.size();
}



