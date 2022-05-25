// DigitalCircuits.cpp : Central file containing main function, demosntration cases, etc..
#include <iostream>
#include <string>
#include <vector>
#include <sstream> 
#include "components.h"
#include "utility.h"
using namespace digitalc;

int main()
{   
    //user settigns
    int n = 5;
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

    //components[3]->set_inversion(true);

    for (int i = 0; i < 5; ++i) {
        printstate(input);
        for (auto item : components) {
            item->update(input, output);
        }
        input.swap(output);
    }

    //print circuit contents
    


    std::cout << "\n";
    components[2]->info();


    //celanup memory
    std::cout << "\nCleaning up memory.\n";
    for (auto vectorit = components.begin(); vectorit < components.end(); ++vectorit)
       delete* vectorit;
    components.clear();
    input.clear();
    output.clear();
    

    //std::string usrinput ="";
    //std::cin >> usrinput;
    std::cout << "\n";
    //std::cout << "Goodbye!\n";
}






