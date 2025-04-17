#include "sqll.h"

void push(node *&head, int value)
{
    node *newNode = new node;
    newNode->data = value;
    newNode->next = nullptr;

    // insert at index 0
    newNode->next = head;
    head = newNode;
}

void pop(node *&head)
{
    if(head == nullptr){
        cout << "Empty list, nothing to pop" << endl;
        return;
    }

    // remove the head
    node *dltTemp = head;
    head = head->next;

    delete dltTemp;
}

void enqueue(node *&head, int value)
{
    node *newNode = new node;
    newNode->data = value;
    newNode->next = nullptr;

    if(head == nullptr)
    {
        head = newNode;
        return;
    }

    // insert at the end
    node *walker = head;
    while(walker->next != NULL){
        walker = walker->next;
    }
    walker->next = newNode;
}
void dequeue(node *&head)
{
    if (head == nullptr){
        cout << "Empty list, nothing to dequeue!" << endl;
        return;
    }

    node *dltTemp = head;
    head = head->next;

    delete dltTemp;

}

void displayList(node *&head)
{
    node *walker = head;

    while(walker != nullptr){
        cout << walker->data << " ";
        walker = walker->next;
    }
    cout << endl;
}