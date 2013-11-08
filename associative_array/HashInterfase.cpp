#include "HashInterfase.h"
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



HashInterfase::HashInterfase(void)
{
}

HashInterfase::~HashInterfase(void)
{
}



void HashInterfase::put(std::string key, double value)
{
	_put(key,hash_function(key), value);
}

void HashInterfase::forse(std::string key, double value)
{
	_forse(key,hash_function(key), value);
}



void HashInterfase::put(HashElement other)
{
	_put(other.key ,hash_function(other.key), other.value);
}

void HashInterfase::forse(HashElement other)
{
	_forse(other.key ,hash_function(other.key), other.value);
}



HashElement* HashInterfase::item(std::string key)
{
	return _item(key, hash_function(key));
}

bool HashInterfase::has(std::string key)
{
	return _has(key, hash_function(key));
}



void HashInterfase::remove(std::string key)
{
	_remove(key, hash_function(key));
}

void HashInterfase::clear()
{
	_clear();
}



HashInterfase::Iterator HashInterfase::begin() const
{
    return Iterator(this, _begin(), _beginIndex());
}

HashInterfase::Iterator HashInterfase::end() const
{
    return Iterator(this, 0, 0);
}

HashElement &HashInterfase::asterisc(void *pointer) const
{
    return _asterisc(pointer);
}

void HashInterfase::next(void *&pointer, int &current_index) const
{
    _next(pointer, current_index);
}

///////////////////////////////////////////////////////////////


HashIterator::HashIterator():
	owner(0), current(0), current_index(0)
{}

HashIterator::~HashIterator()
{
	owner = 0;
	current = 0;
	current_index = 0;
}

HashElement &HashIterator::operator*() const
{
	if(owner)
		return owner->asterisc(current);
	else
		throw IteratorException();
}

HashIterator HashIterator::operator++()
{
    if(owner)
		owner->next(current, current_index);

    return *this;
}

HashIterator HashIterator::operator++(int)
{
    HashIterator result(*this);
    ++(*this);
    return result;
}

bool HashIterator::operator==(const HashIterator &other) const
{
	return owner == other.owner && current == other.current;
}

HashIterator::HashIterator(const HashInterfase *owner, void *current, int current_index):
    owner(owner),
    current(current),
	current_index(current_index)
{}