#pragma once

#include <vector>

#ifndef __COMPONENTS__
#define __COMPONENTS__
namespace digitalc {

	class component
	{
	private:

	public:
		component();
		 ~component(); //virtual
		virtual void update(std::vector<bool>& input)=0;
	};


	class ANDgate:public component
	{
	private:
		int input1;
		int input2;
		int output;

	public:
		ANDgate();
		ANDgate(int i1,int i2,int o);
		~ANDgate();
		void update(std::vector<bool>& input);
	};







}
#endif