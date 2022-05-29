//Digital Circuits
//This is a program to represent, manipulate, simualate and display digital circuits
//Written by Andras Botar
//May 2022

//Contained files:
//DigitalCircuits.cpp : Central file containing main function, demonstration cases, etc..
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
using namespace digitalc; //"DigitalCircuit" namespace abbreviated

//setup function to collect some start-up actions
int setup() {
    //Set up output mode of windows console so we can output unicode characters
    //Using std::wcout and std::wstring
    int _ = _setmode(_fileno(stdout), _O_U16TEXT);
    //std::wcout << L"Testing unicode -- English -- Ελληνικά -- Español." << std::endl;

    return 0;
}

//function to create and eample circuit with one of each logic gate type
void example_circuit(Circuit& circuit1) {
    circuit1.addcomponent(std::make_unique< constant_input>(true, 1));
    circuit1.addcomponent(std::make_unique< constant_input>(true, 2));
    circuit1.addcomponent(std::make_unique< ANDgate>(1, 2, 3));
    circuit1.addcomponent(std::make_unique< ORgate>(1, 2, 4));
    circuit1.addcomponent(std::make_unique< XORgate>(1, 2, 5));
    circuit1.addcomponent(std::make_unique< NOTgate>(1, 7));
    circuit1.addcomponent(std::make_unique< buffer>(1, 7));
    circuit1.addcomponent(std::make_unique< majority_function>(1, 2, 7));
}

//Main function of program, start-point
int main()
{   
    setup();


    //create a circuit
    
    Circuit circuit2(9);
    Circuit circuit1(9);
    example_circuit(circuit2);
    example_circuit(circuit1);
    //circuit1 = circuit2;

    //Invert logic gate
    circuit1.set_invert(4,true);
    

    //print current state of circuit
    std::wcout << "Intitial state: ";
    circuit1.printstate();
    //simulate one time step and print new state
    circuit1.update();
    std::wcout << "New state:      ";
    circuit1.printstate();
    std::wcout << "\n\n";

    //reset circuit and run proper simulation
    std::wcout << "Simulation over several timesteps: \n";
    circuit1.reset_state();
    circuit1.simulate_cli(5);
    std::wcout << "\n\n";

    std::wcout << "Delete wires and re-run simulation.\n";
    circuit1.reset_state();
    circuit1.deletewires(std::vector<int>{2, 8});
    //circuit1.deletewires(std::vector<int>{5, 8});
    circuit1.simulate_cli(5);
    std::wcout << "\n\n";



    //Print info for a specific component
    std::wcout << "Detailed information of component 3: \n";
    circuit1.component_info(2);
    //std::wcout << "\n";

    //print truth table for a logic gate
    //int gate_size = 2;
    std::wcout << "Truth table for a XOR gate: \n";
    XORgate gate1(0, 1, 0);
    std::vector<bool> trutht1 = truth_table(gate1, 2);
    printtable(trutht1, 2);
    std::wcout << "\n";

    std::wcout << "Truth table for a bigger XOR gate: \n";
    XORgate gate2(0, 2, 0);
    std::vector<bool> trutht2 = truth_table(gate2, 3);
    printstate(trutht2);
    std::wcout << "\n";



    circuit1.print_info();
    //circuit1.debug();

    //Cleanup memory
    //std::wcout << "Cleaning up: \n";
    //delete circuit1;
    
    //Exit program
    //std::wstring usrinput ="";
    //std::cin >> usrinput;
    std::wcout << "\n";
    //std::wcout << "Goodbye!\n";
    return 0;
}





