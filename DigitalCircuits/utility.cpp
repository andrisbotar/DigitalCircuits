#include <vector>
#include <iostream>
#include <string>
#include <sstream> 
#include "utility.h"
#include "circuit.h"
//using namespace digitalc;

//various utility functions
namespace digitalc {

    //convert boolean "0" or "1" into human firendly text
    std::string BoolToString(bool b)
    {
        return b ? "True" : "False";
    }

    //Convert and integer into a bool vector representing the binary count for that number
    //A length option is used to pad the bool array to a desired length
    std::vector<bool> int_to_bool_vector(int number, int len) {
        int i = number;
        std::vector<bool> vector;
        while (i) {
            vector.push_back(i & 1);
            i >>= 1;
        }
        vector.insert(vector.end(), len-vector.size(), 0);
        std::reverse(vector.begin(), vector.end());
        return vector;
    }
    
    //Creates a truth table for a LogicGate
    std::vector<bool> truth_table(LogicGate& comp, int n)
    {
        //int output_wire = 0;
        int numtable = pow(2, n);
        std::vector<bool> input(n, 0);
        std::vector<bool> output(8, 0);
        std::vector<bool> table(numtable, 0);

        for (int i = 0; i < numtable;++i) {
            input = int_to_bool_vector(i, n);
            comp.update(input,output);
            table[i] = output[0];
        }
        return table;
    }





    /*template<typename T, typename A>
    void printstate(std::vector<T, A> circuitstate)
    {
        for (T i : circuitstate) {
            std::cout << i << " ";
        }
        std::cout << " \n";
    }*/

    //print out a vector of booleans
    void printstate(std::vector<bool> circuitstate)
    {
        for (auto i : circuitstate) {
            std::cout << i << " ";
        }
        std::cout << " \n";
    }

    //print out a vector of ints
    void print_int_vector(std::vector<int> circuitstate)
    {
        for (auto i : circuitstate) {
            std::cout << i << " ";
        }
        std::cout << " \n";
    }

    //convert a vector of ints to a single string
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