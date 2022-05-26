#include <vector>
#include <iostream>
#include <string>
#include <sstream> 
#include "utility.h"
#include "circuit.h"
//using namespace digitalc;

//various utility functions
namespace digitalc {

    std::string BoolToString(bool b)
    {
        return b ? "True" : "False";
    }

    std::vector<bool> int_to_bool_vector(int n) {
        if (n == 0) { std::vector<bool> vector(1, 0); return vector; }
        int i = n;
        std::vector<bool> vector;
        while (i) {
            vector.push_back(i & 1);
            i >>= 1;
        }
        std::reverse(vector.begin(), vector.end());
        return vector;
    }
    

    std::vector<bool> truth_table(LogicGate& comp, int n)
    {
        int output_wire = 0;

        int numtable = pow(2, n);
        std::vector<bool> input(n, 0);
        std::vector<bool> output(8, 0);
        std::vector<bool> table(numtable, 0);

        for (int i = 0; i < numtable;++i) {
            //std::cout << "aaa " << (i) <<"\n";
            input = int_to_bool_vector(i);
            std::vector<bool> input{ 1,0 };
            printstate(input);
            comp.update(input,output);
            printstate(output);
            bool out = output[0];
            //std::cout <<" result: " << out << "\n";
            table[i] = out;
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