#include "HashTable.h"

#include <iostream>

using namespace std;


int main()
{
	HashTable a;
	HashElement *b;
	a.put("Fujji",12.4);
	a.put("Anton",13.9);
	a.put("Fung",18.7);

	a.print_to_console();

	a.forse("Fujji", 67.907);
	a.forse("Atopus", 67.907);
	
	a.print_to_console();

	system("pause");
	return 0;
}