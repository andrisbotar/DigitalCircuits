// components.cpp : Specific circuit components, AND gates, OR gates, buffers...
#include <iostream>
#include "components.h"
#include <vector>
#include "utility.h"
using namespace digitalc;


//component::component(){}
//component::~component(){}



ANDgate::ANDgate() {
	this->inputs = std::vector<int>{ 0,0 };
	this->output = 0;
}

ANDgate::ANDgate(int i1, int i2, int o)
{
	this->inputs = std::vector<int>{i1,i2};
	this->output = o;
}

ANDgate::~ANDgate(){
	std::cout << "deleted!\n";
}


void ANDgate::update(std::vector<bool>& state) {
	
	//std::cout << "inputs size: " << inputs.size() << "\n";
	std::cout << "output: " << output << "\n";

	state[output] = state[inputs[0]] && state[inputs[1]];

	//std::cout << "updated!\n";
	//return input;
}




