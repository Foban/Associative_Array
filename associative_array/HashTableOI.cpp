#include "HashTableOI.h"


HashTableOI::HashTableOI(void):
	size(0), number(0),arr(0)
{
}

HashTableOI::HashTableOI(int size):
	size(size), number(0), arr(0)
{
	arr = new HashElement* [size];
	for(int i = 0; i < size; ++i)
		arr[i] = 0;
}


HashTableOI::HashTableOI(const HashTableOI &other):
	size(other.size), number(other.number), arr(0)
{
	arr = new HashElement* [size];
	for(int i = 0; i < size; ++i)
	{
		if(other.arr[i])
			arr[i] = new HashElement (*other.arr[i]);
		else
			arr[i]  = 0;
	}
}


HashTableOI::~HashTableOI(void)
{
	_clear();
}



////////////////////////////////////////////////////////////////////////




int HashTableOI::hash_function(std::string key)
{
	if(!size)
	{
		size = 128;
		arr = new HashElement* [size];
		for(int i = 0; i < size; ++i)
			arr[i] = 0;
	}
	return ((int)(key.at(0)*(sqrt(5)-1)/2*key.size()))%size;
}


void HashTableOI::_put(std::string key, int index, double value)
{
	if(number == size)
		resize();
	if(find(key, index) < 0)
	{
		for(int  i = 0, m; i < size; ++i)
		{
			m = (i+index)%size;
			if(!arr[m])
			{
				arr[m] = new HashElement(key, value);
				++number;
				return;
			}
		}
	}
}

void HashTableOI::_forse(std::string key, int index, double value)
{
	if(number == size)
		resize();
	int k;
	++number;
	if(k = find(key, index) < 0)
	{
		for(int  i = 0, m; i < size; ++i)
		{
			m = (i+index)%size;
			if(!arr[m])
			{
				arr[m] = new HashElement(key, value);
				return;
			}
		}
	}
	else
	{
		arr[k]->value = value;
	}
}


HashElement* HashTableOI::_item(std::string key, int index)
{
	int k;
	if(k = find(key,index) > -1)
		return arr[k];
	return 0;
}

bool HashTableOI::_has(std::string key, int index)
{
	if(find(key,index) > -1)
		return true;
	return false;
}


void HashTableOI::_remove(std::string key, int index)
{
	int k;
	if(k = find(key,index) > -1)
		delete arr[k];
}

void HashTableOI::_clear()
{
	for(int i = 0; i < size; ++i)
		delete arr[i];
	delete [] arr;
	size = 0;
}

//////////////////////////////////////////////////////////////////////////

HashElement &HashTableOI::_asterisc(void *pointer) const
{
    if(pointer)
		return *(HashElement*)pointer;
    else
        throw HashTableOIException();
}

void HashTableOI::_next(void *&pointer, int &current_index) const
{
	if(pointer)
	{
		++current_index;
		for(; current_index < size; ++current_index)
		{
			if(arr[current_index])
			{
				pointer = arr[current_index];
				return;
			}
		}
		pointer = 0;
	}
}

void *HashTableOI::_begin() const
{
	return arr[_beginIndex()];
}

void *HashTableOI::_end() const
{
	return arr[_endIndex()];
}

int HashTableOI::_beginIndex() const
{
	for(int i = 0; i < size; ++i)
	{
		if(arr[i]) return i;
	}
	return 0;
}

int HashTableOI::_endIndex() const
{
	for(int i = size-1; 0 < i; --i)
	{
		if(arr[i]) return i;
	}
	return 0;
}


//////////////////////////////////////////////////////////////////////////


void HashTableOI::resize() 
{
	HashElement **brr = new HashElement* [size];
	for(int i = 0; i < size; ++i)
	{
		if(arr[i])
			brr[i] = new HashElement (*arr[i]);
		else
			brr[i]  = 0;
	}
	int old_size = size;
	clear();
	size = old_size * 1.25;
	arr = new HashElement* [size];
	for(int i = 0; i < size; ++i)
		arr[i] = 0;
	for(int i = 0; i < old_size; ++i)
	{
		if(brr[i])
			put(*brr[i]);
	}
}

int HashTableOI::find(std::string key, int index)
{
	int m;
	for(int i = 0; i < size; ++i)
	{
		m = (i+index)%size;
		if(arr[m] && arr[m]->key == key) return (i+index)%size;
	}
	return -1;
}


/////////////////////////////////////////////////////////////////
