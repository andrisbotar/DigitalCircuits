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
    std::wstring BoolToString(bool b)
    {
        return b ? L"True" : L"False";
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
        int numtable = (int)pow(2, n);
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

    //prints atable of booleans with column and row indecies, and unicode box drawing characters
    void printtable(std::vector<bool> table, int width)
    {
        std::wcout << "  ";
        for (int i = 0; i < width; ++i) {
            std::wcout << " " << i;
        }
        std::wcout << L" \n\u2500\u2540";
        for (int i = 0; i < width; ++i) {
            std::wcout << L"\u2500\u2500";
        }
        std::wcout << "\n";
        for (int j = 0; j < ceil(table.size() / width); ++j) {
            std::wcout << j << L"\u2502";
            for (int i = 0; i < width; ++i) {
                std::wcout << " " << table[i+j* width];
            }
            std::wcout << "\n";
        }
        std::wcout << "\n";
    }





    /*template<typename T, typename A>
    void printstate(std::vector<T, A> circuitstate)
    {
        for (T i : circuitstate) {
            std::wcout << i << " ";
        }
        std::wcout << " \n";
    }*/

    //print out a vector of booleans
    void printstate(std::vector<bool> circuitstate)
    {
        for (auto i : circuitstate) {
            std::wcout << i << " ";
        }
        std::wcout << " \n";
    }

    //print out a vector of ints
    void print_int_vector(std::vector<int> circuitstate)
    {
        for (auto i : circuitstate) {
            std::wcout << i << " ";
        }
        std::wcout << " \n";
    }

    //convert a vector of ints to a single string
    std::wstring int_vector_to_string(std::vector<int> circuitstate) {
        std::wstringstream ss;
        for (auto i : circuitstate) {
            ss << std::to_wstring(i) << " ";
        }
        std::wstring returnval;
        ss >> returnval;
        return returnval;
    }
}