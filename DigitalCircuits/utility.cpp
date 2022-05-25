#include <vector>
#include <iostream>
#include "utility.h"
using namespace digitalc;

namespace digitalc {
    void printstate(std::vector<bool> circuitstate)
    {
        for (auto i : circuitstate) {
            std::cout << i << " ";
        }
        std::cout << " \n";
    }
}