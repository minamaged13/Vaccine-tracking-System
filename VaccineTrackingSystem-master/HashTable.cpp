#include "HashTable.h"
#include <iostream>

HashTable::HashTable()
{
	for (int i = 0; i < hashGroups; i++)
	{
		table[i] = NULL;
	}
}

int HashTable::hashFunction(long long key)
{
	int index = 0, numInKey;
	for (int i = 0; i < 13; i++)
	{
		numInKey = key % 10;
		if (i % 2 == 0)
		{
			numInKey *= 3;
		}
		index += numInKey;
		key /= 10;
	}
	return index % hashGroups;
}

void HashTable::insertItem(Citizen* c)
{
	long long key = c->getId();
	int index = hashFunction(key);
	Node* newCit = new Node(c);
	if (table[index] == NULL)
	{
		table[index] = newCit;
		//numOfLists++;
	}
	else
	{
		newCit->next = table[index];
		table[index] = newCit;
		//collisions[index]++;
	} 
	size++;
}

Citizen* HashTable::searchItem(long long key)
{
	int index = hashFunction(key);

	Node* cursor = table[index];
	while (cursor != NULL)
	{
		if (cursor->c->getId() == key)
			return cursor->c;
		cursor = cursor->next;
	}

	return new Citizen();
}

void HashTable::deleteItem(long long key)
{
	int index = hashFunction(key);
	Node* temp;
	Node* cursor = table[index];
	while (cursor->next != NULL)
	{
		if (cursor->next->c->getId() == key)
		{
			temp = cursor->next->next;
			delete cursor->next;
			cursor->next = temp;
			cout << "\nYour record has been erased.\n\n";
			break;
		}
		cursor = cursor->next;
	}
	size--;
}

void HashTable::deleteAll()
{
	if (size == 0)
		return;
	for (int i = 0; i < hashGroups; i++)
	{
		Node* cursor = table[i];
		Node* temp = cursor->next;
		while (cursor->next != NULL)
		{
			delete cursor;
			cursor = temp;
			temp = temp->next;
		}
		delete temp;
	}
	size = 0;
}

void HashTable::printTable()
{
	for (int i = 0; i < hashGroups; i++)
	{
		Node* cursor = table[i];
		while (cursor != NULL && size != 0)
		{
			cursor->c->CitDisplay();
			cout << endl;
			cursor = cursor->next;
		}
	}
	cout << "total users: " << size << endl;
}


int HashTable::getSize()
{
	return size;
}

HashTable::~HashTable()
{
	deleteAll();
}
