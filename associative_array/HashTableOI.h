#pragma once

#include "HashInterfase.h"

class HashTableOI: public HashInterfase
{
public:
	HashTableOI(void);
	HashTableOI(int size);
	HashTableOI(const HashTableOI &);
	~HashTableOI(void);

	virtual void print_to_console(){};

protected:
	HashElement **arr;
	int size;
	int number;

private:
	int hash_function(std::string key);
	void _put(std::string key, int index, double value);
	void _forse(std::string key, int index, double value);
	
	HashElement* _item(std::string key, int index);
	bool _has(std::string key, int index);

	void _remove(std::string key, int index);
	void _clear();


	HashElement &_asterisc(void *pointer) const;
    void _next(void *&pointer, int &current_index) const;
    void *_begin() const;
    void *_end() const;
    int _beginIndex() const;
    int _endIndex() const;


	void resize();
	int find(std::string key, int index);
};

class HashTableOIException: public std::exception
{
    public:
        const char *what() const throw() {return "trying to access to not existing element";}
};