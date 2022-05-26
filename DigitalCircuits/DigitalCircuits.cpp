// DigitalCircuits.cpp : Central file containing main function, demosntration cases, etc..

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


int main()
{   
    //Set up output mode of windows console so we can output unicode characters
    //Using std::wcout and std::wstring
    int _ = _setmode(_fileno(stdout), _O_U16TEXT);
    //std::wcout << L"Testing unicode -- English -- Ελληνικά -- Español." << std::endl;

    //set up variables
    Circuit circuit1(7);

    //initialize data
    circuit1.addcomponent(new constant_input(true, 0));
    circuit1.addcomponent(new constant_input(true, 1));
    circuit1.addcomponent(new ANDgate(0, 1, 2));
    circuit1.addcomponent(new ORgate(0, 1, 3));
    circuit1.addcomponent(new XORgate(2, 1, 4));
    circuit1.addcomponent(new buffer(4, 5));
    circuit1.addcomponent(new NOTgate(4, 6));

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

    //reset circuti and run proper simulation
    std::wcout << "Simulation over several timesteps: \n";
    circuit1.reset_state();
    circuit1.simulate_cli(5);
    std::wcout << "\n\n";

    //Print info for a specific component
    std::wcout << "Detailed information of component 3: ";
    circuit1.component_info(2);
    //std::wcout << "\n";

    
    std::wcout << "Truth table for a XOR gate: \n";
    XORgate ag(0, 1, 0);
    int gate_size = 2;
    std::vector<bool> trutht = truth_table(ag, gate_size);
    //printstate(trutht);
    printtable(trutht, gate_size);

    //GLOBAL
    int n = 7;
    bool default_wire_state = false;

    //Unfortunately Windows console does not want to reliably display unicode characters
    // So unable to use proper "box drawing characters"
    //_setmode(_fileno(stdout), _O_U16TEXT);
    //const char continous_line_character = '\u2501';
    const char continous_line_character = '-';


    //Cleanup memory
    //std::wcout << "Cleaning up: \n";
    //delete circuit1;
    
    //Exit program
    //std::wstring usrinput ="";
    //std::cin >> usrinput;
    std::wcout << "\n";
    //std::wcout << "Goodbye!\n";
}





