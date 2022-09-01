//Defines a class for storing a circuit with multiple inputs, outputs and update functionality

#include <iostream>
#include "circuit.h"
#include "utility.h"
#include "otherclasses.h"
using namespace digital_circuits;

////init global variables for keepign track of circuits
int CIRCUITCOUNT{0};

//circuit constructors and destructors first
circuit::circuit() 
{ 
    label = L"Circuit " + std::to_wstring(CIRCUITCOUNT);
    CIRCUITCOUNT++;
}
//Copy cosntructor
circuit::circuit(const circuit& other) 
{
    label = L"Circuit " + std::to_wstring(CIRCUITCOUNT);
    CIRCUITCOUNT++;
    this->state = other.state;
    this->new_state = other.new_state;
    this->hidden = other.hidden;
    this->label = other.label;

    //need to make copy cosntructor becuase unique_ptr-s cannot be simply copied
    for (const auto& item : other.components) {
        this->components.push_back(std::move(item.get()->clone()));
    }
}
circuit::circuit(int number_of_wires, bool default_wire_state)
{
    label = L"Circuit " + std::to_wstring(CIRCUITCOUNT); CIRCUITCOUNT++;
    this->state = std::vector<bool>(number_of_wires, default_wire_state);
    this->new_state = std::vector<bool>(number_of_wires, default_wire_state);
}
//alow labeling of cricuit
circuit::circuit(int number_of_wires, bool default_wire_state, std::wstring label) 
{
    label = label; CIRCUITCOUNT++;
    this->state = std::vector<bool>(number_of_wires, default_wire_state);
    this->new_state = std::vector<bool>(number_of_wires, default_wire_state);
}
circuit::~circuit()
{
    //Cleanup memory
    if (digital_circuits::verbose) {
        std::wcout << "Destroying circuit of size " << size() << " with " << component_count() << " components\n";
    }
    //for (auto vectorit = components.begin(); vectorit < components.end(); ++vectorit)        delete vectorit;
    components.clear();
    state.clear();
    new_state.clear();
}
/*circuit& circuit::operator=(circuit other)
{
    if (this != &other)
    {
        delete components;
        components = ;
        cpy(components, that.components);
        age = that.age;
    }
    return *this;
}*/

//define operators for circuits
circuit& circuit::operator=(circuit other)
{
    //swap and copy idiom
    if (verbose) {
        std::wcout << L"Copy assignment of " << label << L" \n";
    }
    std::swap(state, other.state);
    std::swap(new_state, other.new_state);
    std::swap(hidden, other.hidden);
    std::swap(label, other.label);

    for (const auto& item : other.components) {
        this->components.push_back(std::move(item.get()->clone()));
    }
    return *this;
}
circuit& circuit::operator++(int)
{  
    this->update();
    return *this;
}


//Core updating logic
void circuit::update() 
{
    for (const auto& item : components) {
        item->update(state, new_state);
    }
    //new_state[0] = defaul_wire_state 
    state.swap(new_state);
}

//state manipulation
void circuit::print_state() 
{
    //for (auto i : state) {        std::wcout << i << " ";    } 
    //std::vector<bool> not a standard container, so causes some problems
    for (int i = 0; i < state.size(); ++i) {
        if(vector_contains <int,std::vector<int>> (i,hidden)) {
             continue; 
        }
        std::wcout << state[i] << " ";
    }
    std::wcout << " \n";
}
std::vector<bool> circuit::get_state() 
{
    return this->state;
}
void circuit::set_state(std::vector<bool> default_state)
{
    this->state = default_state;
    this->new_state = default_state;
}
void circuit::reset_state()  //Reset circuit if needed
{
    this->state = std::vector<bool>(state.size(), false);
    this->new_state = std::vector<bool>(state.size(), false);
}



//acting on individual wires
void circuit::add_wires(int wire_count) 
{
    if (wire_count < 0) {
        std::wcout << "Cannot add negative number of wires.";
        return;
    }
    size_t new_size = state.size() + wire_count;
    state.resize(new_size);
    new_state.resize(new_size);
}
void circuit::delete_wire(int n) 
{
    hidden.push_back(n);
    for (int i = 0; i < components.size(); ++i) {
        std::vector<int> v = components[i]->get_input();
        //std::wcout <<"\n"<< i << ": "; print_int_vector(v);
        for (int j=0; j< v.size();++j){
            if (v[j] == n) {
                components[i]->set_input(j, 0);
            }
            /*if (v[j] > n) {
                components[i]->set_input(j, v[j] -1);
            }*/
        }
    }
}
void circuit::delete_wires(std::vector<int> wirestodelete) 
{
    for (auto wireindex : wirestodelete) {
        this->delete_wire(wireindex);
    }
}
bool circuit::get_wire_state(int n) {    return state[n];}
void circuit::set_wire_state(int n, bool value) {    state[n] = value;}
void circuit::hide_wire(int n) {    hidden.push_back(n);}
void circuit::un_hide_all_wires() {    hidden.clear();}


//acting on individual components
void circuit::add_component(std::unique_ptr<component> new_component) {    components.push_back(std::move(new_component));}
void circuit::replace_component(int n, std::unique_ptr<component> new_component) {    components[n] = std::move(new_component);}
void circuit::delete_component(int n)
{
    components.erase(components.begin() + n);
    //this->replace_component(n, std::make_unique<and_gate>(0, 0, 0));
}
void circuit::set_invert(int n, bool inverted){    components[n]->set_inversion(inverted);}
std::wstring circuit::component_info(int n) 
{
    components[n]->info();
    return L"";
}
std::wstring circuit::get_component_type(int n){      return components[n]->get_type(); }
std::wstring circuit::get_component_label(int n){     return components[n]->get_label(); }
int circuit::get_component_output(int n) {            return components[n]->get_output(); }
std::vector<int> circuit::get_component_inputs(int n){return components[n]->get_input(); }
/*std::unique_ptr<component> circuit::get_component_copy(int n)
{
    return std::make_unique<component>(components[n]->clone());
}*/

//Utility functions
size_t circuit::size() {               return state.size();}
size_t circuit::component_count() {    return components.size();}
void circuit::print_info() 
{
    std::wcout << "The circuit labelled '" << label << "' is currently in state: "; print_state();

    if (acyclic()) {
        std::wcout << "It has no feedback/Is an acyclic circuit.\n";
        //std::wcout<< "With total depth: ";
    }
    else {
        std::wcout << "It has feedback/Is a cyclic circuit.\n";
    }

    std::wcout << "And it has " << size() << " wires and contains "<< component_count() <<" components: \n";
    for (int i = 0; i < components.size(); ++i) { std::wcout << "- "; components[i]->info(); }
    //std::wcout<<"and has complexity: "<<complexity();
}
//Checks wether the circuit has any feedback or "cycles"
bool circuit::acyclic()
{
    std::vector<bool> visited(size(),false);
    for (int i = 0; i < components.size(); ++i) {
        int output_of_component = components[i]->get_output();
        //std::wcout << visited.size() << " " << output_of_component << " - " << components.size() << " " << i << "\n";
        if (visited[output_of_component] and !vector_contains(output_of_component,hidden)) { 
            return false; 
        }
        for (auto j : components[i]->get_input()) {
            visited[j] = true;
        }
        std::wstring typ = components[i]->get_type();
        if (typ.find(L"sub-circuit") != std::wstring::npos) {
            if (typ.find(L"acyclic") == std::wstring::npos) {
                return false;
            }
        }
    }
    return true;
}
bool digital_circuits::circuit::stayed_the_same()
{
    if (state == new_state) {
        return true;
    }
    return false;
}
std::wstring circuit::get_label() { return this->label; }

//conversions to lambda functions adn circuits
//One option is to output function that represents only one timestep, one update of the circuit state
auto circuit::lambda_update()
{
    return [this](auto const& x) {
        circuit copy(*this);
        copy.set_state(x);
        copy.update();
        return copy.get_state();
    };  

    //return []() {return true; };
}
//Other is to define some inputs as external inputs, run the circuit until it doesn't change anymore,
//or we reach some predefined amount of maximum updates, then copy an output
using bool_v_fn = std::function<std::vector<bool>(std::vector<bool>)>;
bool_v_fn circuit::lamda_terminal(int max_updates) 
{
    //boolean_function fn{  };
    //bool_fn  func = [](std::vector<bool> in) {return true; };
    //func = [auto x]() {return true; }
    bool_v_fn func;
    try {
        bool_v_fn  func = [this, max_updates](std::vector<bool> in) {
            try {
                circuit copy = *this;
                bool feedback = copy.acyclic();
                copy.set_state(in);
                int update_counter{ 0 };
                bool continue_updating = true;
                while (continue_updating) {
                    copy.update();
                    update_counter++;
                    continue_updating = update_counter < max_updates && (feedback || copy.stayed_the_same());
                }
                return copy.get_state();
            }
            catch (...) {
                std::wcout << "In lambda error.\n";
                return std::vector<bool>(2, 0);
            }
        };
    }
    catch(...) {
        std::wcout << "unable to calulate circuit output";
    }
    return func;
   // return [](std::vector<bool> in) {return std::vector<bool>(true); };
}

bool_v_fn simplest_boolean_v_fn = [](std::vector<bool> a) {return std::vector<bool>(2, 0); };
bool_v_fn circuit::circuit_to_lambda(int max_updates) 
{
    //int max_updates = 100;
    circuit circ = *this;
    bool_v_fn  func = [circ, max_updates](std::vector<bool> in) {
        try {
            circuit copy = circ;
            bool feedback = copy.acyclic();
            copy.set_state(in);
            //std::wcout << "IN SIZE:  " <<in.size() <<" \n";
            int update_counter{ 0 };
            bool continue_updating = true;
            while (continue_updating) {
                copy.update();
                update_counter++;
                continue_updating = update_counter < max_updates && (feedback || copy.stayed_the_same());
            }
            //std::wcout << "aayayayayay"<< copy.get_state().size()<<"\n";
            return copy.get_state();
        }
        catch (...) {
            std::wcout << "In lambda error.\n";
            return std::vector<bool>(2, 0);
        }
    };
    return func;
}



//creates compoennt which represents runnign this circuit continously until it reaches some steady state
//If an oscillatory circuit is input, this may cause unpredictable or unexpected results
/*auto circuit::to_component() {
    //if(acyclic){ std:stderr<<"Steady state of acyclic circuit cannot be found" }
    
}*/

//Creates single-output logic gate
//It simulates runnign the circuit unitl it reaches "steady state", and a given wire is returned as output
//Use max_updates=1 if you are only curious about only a single timestep update
//If an oscillatory circuit is input, this may cause unpredictable or unexpected results
std::unique_ptr<sub_circuit_component> circuit::to_logic_gate(std::vector<int> inputs, int output, int output_port,int max_updates)
{
    //if(acyclic){ std:stderr<<"Steady state of acyclic circuit cannot be found" }

    bool_fn function;
    try {
        //bool_v_fn vfunction = this->lamda_terminal();
        bool_v_fn vfunction = circuit_to_lambda(  max_updates);
        function = [vfunction, output_port](std::vector<bool> inputvalues) {
            try {
                std::vector<bool> temparr = vfunction(inputvalues);
                return !!temparr[output_port];   // <- Why this needs to be !!x isntead of x, is jsut black magic. I spent hours tryign to work it out
            }
            catch (...) {
                std::wcout << "unable to calulate output";
                return false;
                //function = simplest_boolean_fn;
            }
        };
    }
    catch (...) {
        std::wcout << "Error ocurred in turning circuit to logic gate";
        function = simplest_boolean_fn;
        //return std::make_unique<sub_circuit_component>(inputs, output, function, this->size());
    }
    //sub_circuit_component subcircuit(inputs, output, function); return subcircuit;
    return std::make_unique<sub_circuit_component>(inputs, output, function, this->size());
}
std::unique_ptr<sub_circuit_component> circuit::to_logic_gate(int i1, int i2, int o, int output_port, int max_updates) 
{
    //if(acyclic){ std:stderr<<"Steady state of acyclic circuit cannot be found" }

    bool_fn function;
    try {
        //bool_v_fn vfunction = this->lamda_terminal();
        bool_v_fn vfunction = circuit_to_lambda( max_updates);
        function = [vfunction, output_port](std::vector<bool> inputvalues) {
            try {
                std::vector<bool> temparr = vfunction(inputvalues);
                return !!temparr[output_port];   // <- Why this needs to be !!x isntead of x, is jsut black magic. I spent hours tryign to work it out
            }
            catch (...) {
                std::wcout << "unable to calulate output";
                return false;
            }
        };
    }
    catch(...) {
        std::wcout << "Error ocurred in turning circuit to logic gate";
        function = simplest_boolean_fn;
    }
    //sub_circuit_component subcircuit(inputs, output, function); return subcircuit;
    //return std::make_unique<sub_circuit_component>(0, 1, 0, simplest_boolean_fn, 2);
    return std::make_unique<sub_circuit_component>(i1,i2,o, function, this->size());
}





//Simualtion
//Basic simulation that steps through a given number of timesteps 
//and prints results to console
void circuit::simulate_cli(int steps) 
{
    std::wcout << "   ";
    for (int i = 0; i < size(); ++i) { 
        if (vector_contains <int, std::vector<int>>(i, hidden)) { continue; }
        std::wcout << " " << i; 
    }
    std::wcout << L"\n\u2500\u252C\u2500";
    for (int i = 0; i < size()-hidden.size() ; ++i) { std::wcout << L"\u2500\u2500"; }
    std::wcout << "\n";

    for (int i = 0; i < steps; ++i) {
        std::wcout << i << L"\u2502  ";
        print_state();
        update();
    }
}



//debug function
void circuit::debug() 
{

    for (int i = 0; i < components.size(); ++i) {
        std::vector<int> v = components[4]->get_input();
        print_vector<int>(v);
    }

    //std::wcout << components.size() << " ";
    //std::wcout << this->state.size();
}



