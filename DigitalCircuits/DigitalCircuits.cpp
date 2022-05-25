// DigitalCircuits.cpp : Central file containing main function, demosntration cases, etc..
#include <iostream>
#include <string>
#include <vector>
#include <sstream> 
//#include <io.h>
//#include <fcntl.h>
#include "components.h"
#include "utility.h"
using namespace digitalc;

int main()
{   
    //user settigns
    int n = 7;
    bool default_wire_state = false;

    //set up variables
    std::vector<bool> input(n, default_wire_state);
    std::vector<bool> output(n, default_wire_state);
    std::vector<component*> components;
    

    //initialize data
    components.push_back(new constant_input(true, 0));
    components.push_back(new constant_input(true, 1));
    components.push_back(new ANDgate(0, 1, 2));
    components.push_back(new ORgate(0, 1, 3));
    components.push_back(new XORgate(2, 1, 4));
    components.push_back(new buffer(4, 5));
    components.push_back(new NOTgate(4, 6));
    

    //components[3]->set_inversion(true);

    //Unfortunately Windows console does not want to reliably display unicode characters
    // So unable to use proper "box drawing characters"
    //_setmode(_fileno(stdout), _O_U16TEXT);
    //const char continous_line_character = '\u2501';
    const char continous_line_character = '-';

    std::cout << "   ";
    for (int i = 0; i < n; ++i) { std::cout <<" " << i; }
    std::cout << "\n---";
    for (int i = 0; i < n; ++i) { std::cout << continous_line_character << continous_line_character; }
    std::cout << "\n";

    for (int i = 0; i < 5; ++i) {
        std::cout << i << "|  ";
        printstate(input);
        for (auto item : components) {
            item->update(input, output);
        }
        input.swap(output);
    }
    std::cout << "\n";


    //Print circuit contents   
    components[2]->info();


    //Cleanup memory
    std::cout << "\nCleaning up memory.\n";
    for (auto vectorit = components.begin(); vectorit < components.end(); ++vectorit)
       delete* vectorit;
    components.clear();
    input.clear();
    output.clear();
    
    //Exit program
    //std::string usrinput ="";
    //std::cin >> usrinput;
    std::cout << "\n";
    //std::cout << "Goodbye!\n";
}






