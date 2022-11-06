#include <iostream>
#include <string>

using namespace std;

// create a purchaseQueue using node list
// DATA STRUCTURE - QUEUE
class PurchaseQueueNode
{
public:
    int queueNo;
    string username;
    int ticketID;

    PurchaseQueueNode *next;
    PurchaseQueueNode *prev;
};

class PurchaseQueue
{
public:
    PurchaseQueueNode *head;
    PurchaseQueueNode *tail;
    int size;
    int capacity;

    PurchaseQueue(int capacity)
    {
        head = nullptr;
        tail = nullptr;
        size = 0;
        this->capacity = capacity;
    }

    void enqueue(string user_name, int ticket_ID);
    void dequeue();
    void getPosition(string user_name);
    int getPositionValue(string user_name);
    void printQueue();
};

// enqueue a user into the queue
void PurchaseQueue::enqueue(string user_name, int ticket_ID)
{
    PurchaseQueueNode *newNode = new PurchaseQueueNode;
    newNode->username = user_name;
    newNode->ticketID = ticket_ID;
    if (tail == nullptr)
    {
        newNode->queueNo = 1;
    }
    else
    {
        newNode->queueNo = tail->queueNo + 1;
    }

    // newNode->queueNo = tail->queueNo + 1;

    newNode->next = nullptr;
    newNode->prev = tail;
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        tail->next = newNode;
    }
    tail = newNode;

    size++;
}

// dequeue the first user from the queue
void PurchaseQueue::dequeue()
{
    PurchaseQueueNode *temp = head;
    head = head->next;
    head->prev = nullptr;
    delete temp;
    size--;
}

// print the user's position in the queue in a format of "Your position in the queue is: "
void PurchaseQueue::getPosition(string user_name)
{
    PurchaseQueueNode *temp = head;
    int position = 1;
    while (temp != nullptr)
    {
        if (temp->username == user_name)
        {
            cout << "Your position in the queue is " << position << endl;
        }
        position++;
        temp = temp->next;
    }
}

// get integer of the user's position in queue
int PurchaseQueue::getPositionValue(string user_name)
{
    PurchaseQueueNode *temp = head;
    int position = 1;
    while (temp != nullptr)
    {
        if (temp->username == user_name)
        {
            return position;
        }
        position++;
        temp = temp->next;
    }
    return -1;
}

// print the queue
void PurchaseQueue::printQueue()
{
    PurchaseQueueNode *temp = head;
    while (temp != nullptr)
    {
        cout << temp->queueNo << " " << temp->username << " " << temp->ticketID << endl;
        temp = temp->next;
    }
}