#include "AssociativeArray.h"
#include <iostream>


AssociativeArray::AssociativeArray(void)
{
}


AssociativeArray::~AssociativeArray(void)
{
}

void AssociativeArray::print_to_console()
{
	Node *work;
	for(int i = 0; i < size; ++i)
	{
		work = arr[i];
		while(work)
		{
			std::cout<< work->data.key <<'\t' <<work->data.value << '\n';
			work = work->next;
		}
	}
}