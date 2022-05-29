//Digital circuits
//This is a program to represent, manipulate, simualate and display digital circuits
//Written by Andras Botar
//May 2022

//Contained files:
//digital_circuitsircuits.cpp : Central file containing main function, demonstration cases, etc..
//circuit.cpp and circuit.h: Defines a class for storing a circuit with multiple inputs, outputs, update functionality..
//Components.cpp and Components.h: Contains digital circuit components such as AND gates, OR gates, buffers...
//utility.cpp and utility.h: Contains various utility functions for creating truth tables, printing tables,printing vectors...

//Import required libraries and namespaces
#include <iostream>
#include <string>
#include <vector>
#include <sstream> 
#include <io.h>
#include <fcntl.h>
#include "components.h" //Contains AND Gates, XOR gates, buffers...
#include "circuit.h" //Contains circuit class to collect and simualte components
#include "utility.h" //A few miscelaneous utility functions
using namespace digital_circuits; //namespace for own code

//setup function to collect some start-up actions
int setup() {
    //Set up output mode of windows console so we can output unicode characters
    //Using std::wcout and std::wstring
    int _ = _setmode(_fileno(stdout), _O_U16TEXT);
    //std::wcout << L"Testing unicode -- English -- Ελληνικά -- Español." << std::endl;

    return 0;
}

//function to create and eample circuit with one of each logic gate type
void example_circuit(circuit& circuit_1) {
    circuit_1.add_component(std::make_unique< constant_input>(true, 1));
    circuit_1.add_component(std::make_unique< constant_input>(true, 2));
    circuit_1.add_component(std::make_unique< and_gate>(1, 2, 3));
    circuit_1.add_component(std::make_unique< or_gate>(1, 2, 4));
    circuit_1.add_component(std::make_unique< xor_gate>(1, 2, 5));
    circuit_1.add_component(std::make_unique< not_gate>(1, 7));
    circuit_1.add_component(std::make_unique< buffer>(1, 8));
    circuit_1.add_component(std::make_unique< majority_function>(1, 2, 9));
}

//Main function of program, start-point
int main()
{   
    setup();


    //create a circuit and fill it with example data
    circuit circuit_1(10);
    example_circuit(circuit_1);

    //copy-create two more circuits
    circuit circuit_2(circuit_1); //copy constructor
    circuit circuit_3; //copy assignment operator
    circuit_3 = circuit_1;
    
    //Invert logic gate
    circuit_1.set_invert(4,true);
    circuit_2.add_component(circuit_3.to_logic_gate(0,9,5,4));
    circuit_2.update();

    //print current state of circuit
    std::wcout << "Intitial state: ";
    circuit_1.print_state();
    //simulate one time step and print new state
    circuit_1.update();
    std::wcout << "New state:      ";
    circuit_1.print_state();
    std::wcout << "\n\n";

    //reset circuit and run proper simulation
    std::wcout << "Simulation over several timesteps: \n";
    circuit_1.reset_state();
    circuit_1.simulate_cli(5);
    std::wcout << "\n\n";

    std::wcout << "Delete wires and re-run simulation.\n";
    circuit_1.reset_state();
    circuit_1.delete_wires(std::vector<int>{2, 8});
    //circuit_1.delete_wires(std::vector<int>{5, 8});
    circuit_1.simulate_cli(5);
    std::wcout << "\n\n";



    //Print info for a specific component
    std::wcout << "Detailed information of component 3: \n";
    circuit_1.component_info(2);
    //std::wcout << "\n";

    //print truth table for a logic gate
    //int gate_size = 2;
    std::wcout << "\n";
    std::wcout << "Truth table for a XOR gate: \n";
    xor_gate gate_1(0, 1, 0);
    std::vector<bool> trutht_1 = truth_table(gate_1, 2);
    print_table(trutht_1, 2);
    std::wcout << "\n";

    std::wcout << "Truth table for a bigger XOR gate: \n";
    xor_gate gate_2(0, 2, 0);
    std::vector<bool> trutht_2 = truth_table(gate_2, 3);
    print_state(trutht_2);
    std::wcout << "\n";



    circuit_1.print_info();
    //circuit_1.debug();

    //Cleanup memory
    //std::wcout << "Cleaning up: \n";
    //delete circuit_1;
    
    //Exit program
    //std::wstring usrinput ="";
    //std::cin >> usrinput;
    std::wcout << "\n";
    //std::wcout << "Goodbye!\n";
    return 0;
}





