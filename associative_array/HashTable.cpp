#include "HashTable.h"
#include <iostream>


Node::Node(const Node & other):
	data(other.data), next(0)
{}

Node::Node(HashElement other):
	data(other), next(0)
{
}

Node::Node(std::string key, double value):
	next(0)
{
	data.key = key;
	data.value = value;
}



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
	clear();
}


/////////////////////////////////////////////////////////////


int HashTable::hash_function(std::string key)
{
	return ((int)key.at(0)*(int)key.at(0)*key.size())%size;
}



void HashTable::put(std::string key, double value)
{
	if(!size)
	{
		size = 256;
		arr = new Node*[size];
		for(int i = 0; i < size; ++i)
			arr[i] = 0;
	}
	int _key = hash_function(key);
	Node *work = arr[_key];
	if(!has(key))
	{
		arr[_key] = new Node(key, value);
		arr[_key]->next = work;
	}
}

void HashTable::put(HashElement other)
{
	if(!size)
	{
		size = 256;
		arr = new Node*[size];
		for(int i = 0; i < size; ++i)
			arr[i] = 0;
	}
	int _key = hash_function(other.key);
	Node *work = arr[_key];
	if(!has(other.key))
	{
		arr[_key] = new Node(other);
		arr[_key]->next = work;
	}
}

void HashTable::forse(std::string key, double value)
{
	if(!size)
	{
		size = 256;
		arr = new Node*[size];
		for(int i = 0; i < size; ++i)
			arr[i] = 0;
	}
	int _key = hash_function(key);
	Node *work = arr[_key];
	if(!has(key))
	{
		arr[_key] = new Node(key, value);
		arr[_key]->next = work;
	}
	else
	{
		while(work->data.key != key)
			work = work->next;
		work->data.value = value;
	}
}

void HashTable::forse(HashElement other)
{
	if(!size)
	{
		size = 256;
		arr = new Node*[size];
		for(int i = 0; i < size; ++i)
			arr[i] = 0;
	}
	int _key = hash_function(other.key);
	Node *work = arr[_key];
	if(!has(other.key))
	{
		arr[_key] = new Node(other);
		arr[_key]->next = work;
	}
	else
	{
		while(work->data.key != other.key)
			work = work->next;
		work->data.value = other.value;
	}
}

HashElement* HashTable::item(std::string key)
{
	int _key = hash_function(key);
	Node *work = arr[_key];
	while(work)
	{
		if(work->data.key == key) return &(work->data);
		work = work->next;
	}
	return 0;
}

bool HashTable::has(std::string key)
{
	int _key = hash_function(key);
	Node *work = arr[_key];
	while(work)
	{
		if(work->data.key == key) return true;
		work = work->next;
	}
	return false;
}



void HashTable::print_to_console()
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



void HashTable::remove(std::string key)
{
	int _key = hash_function(key);
	Node *prev,*work = arr[_key];
	if(!work) return;
	if(work->data.key == key)
	{
		work = arr[_key]->next;
		arr[_key]->data.value = 0;
		delete arr[_key];
		arr[_key] = work;
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

void HashTable::clear()
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