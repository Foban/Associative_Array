#pragma once

#include <string>

struct HashElement
{
	std::string key;
	double value;
};

struct Node
{
	HashElement data;
	Node *next;
	Node(const Node &);
	Node(HashElement);
	Node(std::string key, double value);
};

class HashTable
{
public:
	HashTable();
	HashTable(int size);
	HashTable(const HashTable &);
	~HashTable();

	void put(std::string key, double value);
	void forse(std::string key, double value);

	void put(HashElement);
	void forse(HashElement);

	HashElement* item(std::string key);
	bool has(std::string key);

	void print_to_console();

	void remove(std::string key);
	void clear();
private:
	int hash_function(std::string key);

	Node **arr;
	int size;
};

