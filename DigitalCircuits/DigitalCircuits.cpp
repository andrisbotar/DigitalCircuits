// DigitalCircuits.cpp : Central file containing main function, demosntration cases, etc..

#include <iostream>
#include <string>
#include <vector>
#include <sstream> 
//#include <io.h>
//#include <fcntl.h>
#include "components.h" //Contains AND Gates, XOR gates, buffers...
#include "circuit.h" //Contains circuit class to collect and simualte components
#include "utility.h" //A few miscelaneous utility functions
using namespace digitalc; //"DigitalCircuit" namespace abbreviated


int main()
{   
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
    std::cout << "Intitial state: ";
    circuit1.printstate();
    //simulate one time step and print new state
    circuit1.update();
    std::cout << "New state:      ";
    circuit1.printstate();
    std::cout << "\n\n";

    //reset circuti and run proper simulation
    std::cout << "Simulation over several timesteps: \n";
    circuit1.reset_state();
    circuit1.simulate_cli(5);
    std::cout << "\n\n";

    //Print info for a specific component
    std::cout << "Detailed information of component 3: ";
    circuit1.component_info(2);
    std::cout << "\n";



    ANDgate ag(0, 1, 0);
    std::vector<bool> trutht = truth_table(ag, 2);
    printstate(trutht);



    //GLOBAL
    int n = 7;
    bool default_wire_state = false;

    //Unfortunately Windows console does not want to reliably display unicode characters
    // So unable to use proper "box drawing characters"
    //_setmode(_fileno(stdout), _O_U16TEXT);
    //const char continous_line_character = '\u2501';
    const char continous_line_character = '-';


    //Cleanup memory
    //std::cout << "Cleaning up: \n";
    //delete circuit1;
    
    //Exit program
    //std::string usrinput ="";
    //std::cin >> usrinput;
    std::cout << "\n";
    //std::cout << "Goodbye!\n";
}





