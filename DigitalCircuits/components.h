#pragma once

#include <vector>

#ifndef __COMPONENTS__
#define __COMPONENTS__
namespace digitalc {

	class component
	{
	protected:

	public:
		//component();
		virtual ~component(){}; 
		virtual void update(std::vector<bool>& input)=0;
	};


	class ANDgate:component
	{
	private:
		std::vector<int> inputs{0,0};
		int output = 1;
	public:
		ANDgate();
		ANDgate(int i1,int i2,int o);
		~ANDgate();
		void update(std::vector<bool>& state);
	};







}
#endif