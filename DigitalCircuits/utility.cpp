#include <vector>
#include <iostream>
#include "utility.h"
#include <string>
#include <sstream> 
//using namespace digitalc;

//various utility functions
namespace digitalc {

    std::string BoolToString(bool b)
    {
        return b ? "True" : "False";
    }








    /*template<typename T, typename A>
    void printstate(std::vector<T, A> circuitstate)
    {
        for (T i : circuitstate) {
            std::cout << i << " ";
        }
        std::cout << " \n";
    }*/

    void printstate(std::vector<bool> circuitstate)
    {
        for (auto i : circuitstate) {
            std::cout << i << " ";
        }
        std::cout << " \n";
    }

    void print_int_vector(std::vector<int> circuitstate)
    {
        for (auto i : circuitstate) {
            std::cout << i << " ";
        }
        std::cout << " \n";
    }

    std::string int_vector_to_string(std::vector<int> circuitstate) {
        std::stringstream ss;
        for (auto i : circuitstate) {
            ss << std::to_string(i) << " ";
        }
        std::string returnval;
        ss >> returnval;
        return returnval;
    }
}