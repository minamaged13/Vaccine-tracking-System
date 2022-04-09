#pragma once
#include "Citizen.h"
class Node
{
public:
	Citizen* c;
	Node* next;
	Node(Citizen* cit);
};

