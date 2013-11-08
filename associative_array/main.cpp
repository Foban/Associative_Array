#include "AssociativeArray.h"
#include "AssociativeArrayOI.h"

#include <iostream>

using namespace std;


int main()
{
	AssociativeArray a;
	a.put("Fujji",12.4);
	a.put("Anton",13.9);
	a.put("Fung",18.7);
	a.put("Artem", 27.4);

	a.print_to_console();
	AssociativeArray::Iterator it = a.begin();
	for(AssociativeArray::Iterator end = a.end();it != end; ++it)
		cout<< (*it).key <<'\n';

	AssociativeArrayOI b;
	b.put("Fujji",12.4);
	b.put("Anton",13.9);
	b.put("Fung",18.7);
	b.put("Artem", 27.4);

	b.print_to_console();
	AssociativeArrayOI::Iterator ite = b.begin();
	for(AssociativeArrayOI::Iterator ende = b.end();ite != ende; ite++)
		cout<< (*ite).key <<'\n';

	system("pause");
	return 0;
}