#pragma once

#include <vector>

#ifndef __COMPONENTS__
#define __COMPONENTS__
namespace digitalc {

	class component
	{
	protected:
		int input1 = 0;
		int input2 = 0;
		int output = 0;

	public:
		component();
		 ~component(); //virtual
		virtual void update(std::vector<bool>& input)=0;
	};


	class ANDgate:component
	{
	private:

	public:
		ANDgate();
		ANDgate(int i1,int i2,int o);
		~ANDgate();
		void update(std::vector<bool>& input);
	};







}
#endif