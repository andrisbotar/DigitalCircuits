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
    //user settigns
    int n = 7;
    bool default_wire_state = false;

    //set up variables
    Circuit circuit1(n);

    //initialize data
    circuit1.addcomponent(new constant_input(true, 0));
    circuit1.addcomponent(new constant_input(true, 1));
    circuit1.addcomponent(new ANDgate(0, 1, 2));
    circuit1.addcomponent(new ORgate(0, 1, 3));
    circuit1.addcomponent(new XORgate(2, 1, 4));
    /*components.push_back(new constant_input(true, 1));
    components.push_back(new ANDgate(0, 1, 2));
    components.push_back(new ORgate(0, 1, 3));
    components.push_back(new XORgate(2, 1, 4));
    components.push_back(new buffer(4, 5));
    components.push_back(new NOTgate(4, 6));
    */

    //Invert logic gates
    //components[3]->set_inversion(true);

    //Print component info  
    //components[2]->info();

    
    //circuit1.debug();
    //circuit1.update();



    circuit1.simulate_cli(5);




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






