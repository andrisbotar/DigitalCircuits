// DigitalCircuits.cpp : Central file containing main function, demosntration cases, etc..
#include <iostream>
#include <string>
#include <vector>
#include "components.h"
using namespace digitalc;

void printstate(std::vector<bool> circuitstate)
{
    for (auto i : circuitstate) {
        std::cout << i << " ";
    }
    std::cout << " \n";
}

int main()
{   
    //user settigns
    int n = 3;

    //set up variables
    std::vector<bool> cstate(n);
    //std::vector<bool> output(n);
    ANDgate gate1(0,1,2);

    //initialize data
    cstate[0] = true;
    cstate[1] = true;
    cstate[2] = false;


    //print circuit contents
    //perform circuit update
    printstate(cstate);
    gate1.update(cstate);
    printstate(cstate);

    //std::string usrinput ="";
    //std::cin >> usrinput;
    std::cout << "\n";
    //std::cout << "Goodbye!\n";
}






