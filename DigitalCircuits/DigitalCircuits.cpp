// DigitalCircuits.cpp : Central file containing main function, demosntration cases, etc..
#include <iostream>
#include <string>
#include <vector>
#include <sstream> 
//#include <io.h>
//#include <fcntl.h>
#include "components.h"
#include "circuit.h"
#include "utility.h"
using namespace digitalc;

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


    //Invert logic gates
    circuit1.debug(2);

    //Print component info  
    //components[2]->info();

   

    //print current state of circuit
    circuit1.printstate();
    //simulate one time step and print new state
    circuit1.update();
    circuit1.printstate();
    std::cout << "\n\n";

    //reset circuti and run proper simulation
    circuit1.reset_state();
    circuit1.simulate_cli(5);





    //GLOBAL
    int n = 7;
    bool default_wire_state = false;

    //Unfortunately Windows console does not want to reliably display unicode characters
    // So unable to use proper "box drawing characters"
    //_setmode(_fileno(stdout), _O_U16TEXT);
    //const char continous_line_character = '\u2501';
    const char continous_line_character = '-';


    
    //Exit program
    //std::string usrinput ="";
    //std::cin >> usrinput;
    std::cout << "\n";
    //std::cout << "Goodbye!\n";
}






