// DigitalCircuits.cpp : Central file containing main function, demosntration cases, etc..
#include <iostream>
#include <string>
#include <vector>
#include "components.h"
#include "utility.h"
using namespace digitalc;

int main()
{   
    //user settigns
    int n = 5;

    //set up variables
    std::vector<bool> input(n);
    std::vector<bool> output(n);
    ANDgate gate1(0,1,2);
    ORgate gate2(0,1,3);

    

    //initialize data
    input[0] = true;
    input[1] = true;
    input[2] = false;

    //gate2.update(input, output);

    //print circuit contents
    //perform circuit update
    printstate(input);
    gate1.update(input, output);
    gate2.update(input, output);
    input.swap(output);
    printstate(input);





    //celanup memory
    //std::cout << "particle_vector has size " << components.size() << std::endl;
    //for (auto vectorit = components.begin(); vectorit < components.end(); ++vectorit)
      // delete* vectorit;
    //cstate.clear();
    //std::cout << "particle_vector now has size " << components.size() << std::endl;
    input.clear();
    output.clear();

    //std::string usrinput ="";
    //std::cin >> usrinput;
    std::cout << "\n";
    //std::cout << "Goodbye!\n";
}






