#pragma once
#include <iostream>
#include "Node.h"
using namespace std;
//Queue implementation using doubly linked list
class Queue
{
    Node* head;
    Node* tail;      

    int count;
public:
    Queue();
    ~Queue();

    Citizen* dequeue();
    void enqueue(Citizen* item);
    int size();
    bool isEmpty();
};

