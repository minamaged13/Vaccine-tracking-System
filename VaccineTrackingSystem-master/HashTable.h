#pragma once
#include "Citizen.h"
#include "Node.h"

class HashTable
{
private:
	static const int hashGroups = 100; // Bigger number used for production
	Node* table[hashGroups]; //array of heads of linked lists
	int size = 0;
	int hashFunction(long long key); //key = ID
public:
	//bool isEmpty() const; 
	//int numOfLists = 0;
	//int collisions[100] = { 0 };
	HashTable();
	void insertItem(Citizen* c);
	Citizen* searchItem(long long key);
	void deleteItem(long long key);
	void deleteAll();
	void printTable();
	int getSize();
	~HashTable();
};
