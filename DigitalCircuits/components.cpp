// components.cpp : Specific circuit components, AND gates, OR gates, buffers...
#include <iostream>
#include "components.h"
#include <vector>
using namespace digitalc;


component::component(){
}

component::~component(){
}



ANDgate::ANDgate(){
	input1 = 0;
	input2 = 0;
	output = 0;
}

ANDgate::ANDgate(int i1, int i2, int o)
{
	input1 = i1;
	input2 = i2;
	output = o;
}

ANDgate::~ANDgate(){
	std::cout << "deleted!\n";
}


void ANDgate::update(std::vector<bool>& state) {
	std::cout << "updated!\n";

	state[output] = state[input1] && state[input2];
	//return input;
}




