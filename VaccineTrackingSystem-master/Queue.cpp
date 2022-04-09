#include "Queue.h"
Queue::Queue()
{
    head = NULL;
    tail = NULL;
    count = 0;
}

Queue::~Queue() 
{
    Node* cursor = head;
    Node* temp = cursor->next;
    while (cursor != NULL)
    {
        delete cursor;
        cursor = temp;
        temp = temp->next;
    }
    head = NULL;
    tail = NULL;
}

Citizen* Queue::dequeue()
{
    if (isEmpty())
    {
        cout << "List empty.\n";
        return new Citizen();
    }

    Node* temp = head->next;
    Citizen* output = head->c;

    delete head;
    head = temp;
    count--;

    return output;
}

void Queue::enqueue(Citizen* item)
{
    if (isEmpty())
    {
        head = new Node(item);
        tail = head;
    }
    else
    {
        tail->next = new Node(item);
        tail = tail->next;
    }

    //cout << item->getName() << " added to queue.\n";
    count++;
}

int Queue::size() 
{
    return count;
}

bool Queue::isEmpty() {
    return (count == 0);
}