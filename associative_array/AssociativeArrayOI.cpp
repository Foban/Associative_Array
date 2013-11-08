#include "AssociativeArrayOI.h"
#include <iostream>


AssociativeArrayOI::AssociativeArrayOI(void)
{
}


AssociativeArrayOI::~AssociativeArrayOI(void)
{
}




void AssociativeArrayOI::print_to_console()
{
	for(int i = 0, k = 0; k < number && i < size; ++i)
	{
		if(arr[i])
		{
			std::cout<< arr[i]->key << '\t' << arr[i]->value << '\n';
			++k;
		}
	}
}