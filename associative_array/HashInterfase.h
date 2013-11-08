#pragma once

#include <string>

struct HashElement
{
	std::string key;
	double value;
	HashElement(){};
	HashElement(std::string key, double value):
		key(key), value(value){};
};

struct Node
{
	HashElement data;
	Node *next;
	Node(const Node &);
	Node(HashElement);
	Node(std::string key, double value);
};

class HashIterator;

class HashInterfase
{
public:
	friend HashIterator;
	
	typedef HashIterator Iterator;

    Iterator begin() const;
    Iterator end() const;


	HashInterfase(void);
	~HashInterfase(void);

	void put(std::string key, double value);
	void forse(std::string key, double value);

	void put(HashElement);
	void forse(HashElement);

	HashElement* item(std::string key);
	bool has(std::string key);
	
	void remove(std::string key);
	void clear();
protected:
	virtual int hash_function(std::string key) = 0;
	virtual void _put(std::string key, int index, double value) = 0;
	virtual void _forse(std::string key, int index, double value) = 0;

	virtual HashElement* _item(std::string key, int index) = 0;
	virtual bool _has(std::string key, int index) = 0;

	virtual void _remove(std::string key, int index) = 0;
	virtual void _clear() = 0;

    virtual HashElement &_asterisc(void *pointer) const = 0;
    virtual void _next(void *&pointer, int &current_index) const = 0;
    virtual void *_begin() const = 0;
    virtual void *_end() const = 0;
    virtual int _beginIndex() const = 0;
    virtual int _endIndex() const = 0;


	
    HashElement &asterisc(void *pointer) const;
    void next(void *&pointer, int &current_index) const;
};

class HashIterator
{
    public:
        friend HashInterfase;
        HashIterator();
        ~HashIterator();

        HashElement &operator*() const;
        HashIterator operator++();
        HashIterator operator++(int);
        bool operator==(const HashIterator &other) const;
        bool operator!=(const HashIterator &other) const {return !(*this == other);}
    private:
		const HashInterfase *owner;
        void *current;
		int current_index;

		HashIterator(const HashInterfase *owner, void *current, int current_index);
};

class IteratorException: public std::exception
{
        const char *what() const throw() {return "trying to access iterator, that isn't binded with container";}
};