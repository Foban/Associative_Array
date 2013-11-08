#include "HashTable.h"
#include <iostream>
#include <cmath>


HashTable::HashTable():
	size(0),arr(0)
{
}

HashTable::HashTable(int size):
	size(size)
{
	arr = new Node*[size];
	for(int i = 0; i < size; ++i)
		arr[i] = 0;
}

HashTable::HashTable(const HashTable & other):
	size(other.size)
{
	if(other.arr)
	{
		arr = new Node*[size];
		Node *work;
		Node *p, *q;
		for(int i = 0; i < size; ++i)
		{
			if(other.arr[i])
			{
				work = other.arr[i];
				p = new Node(*work);
				arr[i] = p;
				q = arr[i];
				work = work->next;
				while(work)
				{
					p = new Node(*work);
					q->next = p;
					q = p;
					work = work->next;
				}
			}
			else
			{
				arr[i] = 0;
			}
		}
	}
}

HashTable::~HashTable()
{
	_clear();
}


/////////////////////////////////////////////////////////////


int HashTable::hash_function(std::string key)
{
	if(!size)
	{
		size = 128;
		arr = new Node*[size];
		for(int i = 0; i < size; ++i)
			arr[i] = 0;
	}
	return ((int)(key.at(0)*(sqrt(5)-1)/2*key.size()))%size;
}



void HashTable::_put(std::string key, int index, double value)
{
	Node *work = arr[index];
	if(!_has(key, index))
	{
		arr[index] = new Node(key, value);
		arr[index]->next = work;
	}
}


void HashTable::_forse(std::string key, int index, double value)
{
	Node *work = arr[index];
	if(!_has(key, index))
	{
		arr[index] = new Node(key, value);
		arr[index]->next = work;
	}
	else
	{
		while(work->data.key != key)
			work = work->next;
		work->data.value = value;
	}
}



HashElement* HashTable::_item(std::string key, int index)
{
	Node *work = arr[index];
	while(work)
	{
		if(work->data.key == key) return &(work->data);
		work = work->next;
	}
	return 0;
}

bool HashTable::_has(std::string key, int index)
{
	Node *work = arr[index];
	while(work)
	{
		if(work->data.key == key) return true;
		work = work->next;
	}
	return false;
}



void HashTable::_remove(std::string key, int index)
{
	Node *prev,*work = arr[index];
	if(!work) return;
	if(work->data.key == key)
	{
		work = arr[index]->next;
		arr[index]->data.value = 0;
		delete arr[index];
		arr[index] = work;
		return;
	}
	while(work->next)
	{
		if(work->next->data.key == key)
		{
			prev = work->next;
			work->next = work->next->next;
			prev->data.value = 0;
			delete prev;
			return;
		}

		work = work->next;
	}
}

void HashTable::_clear()
{
	for(int i = 0; i < size; ++i)
	{
		while(arr[i])
		{
			Node *p;
			p=arr[i];
			arr[i]=arr[i]->next;
			p->data.value = 0;
			delete p;
			p=0;
		}	
	}
	delete [] arr;
}


//////////////////////////////////////////////////////////////

HashElement &HashTable::_asterisc(void *pointer) const
{
    if(pointer)
		return ((Node*)pointer)->data;
    else
        throw HashTableException();
}

void HashTable::_next(void *&pointer, int &current_index) const
{
	if(pointer)
	{
		Node *work = (Node*)pointer;
		if(work->next)
		{
			pointer = (void*)work->next;
		}
		else
		{
			++current_index;
			for(; current_index < size; ++current_index)
			{
				if(arr[current_index])
				{
					pointer = (void*)arr[current_index];
					return;
				}
			}
			pointer = 0;
		}
	}
}

void *HashTable::_begin() const
{
	int k = _beginIndex();
	if(arr[k])
		return (void*)arr[k];
	return 0;
}

void *HashTable::_end() const
{
	int k = _endIndex();
	if(arr[k])
	{
		Node* work = arr[k];
		while(work->next)
		{
			work = work->next;
		}
		return (void*)work;
	}
	return 0;
}

int HashTable::_beginIndex() const
{
	for(int i = 0; i < size; ++i)
	{
		if(arr[i]) return i;
	}
	return 0;
}

int HashTable::_endIndex() const
{
	for(int i = size-1; 0 < i; --i)
	{
		if(arr[i]) return i;
	}
	return 0;
}