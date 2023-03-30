#ifndef LINKED_LIST_H
#define LINKED_LIST_H

class Node
{
public:
    int data;
    Node* next;

    Node();
    Node(int data);
};

class Linkedlist {
    Node* head;

public:

    Linkedlist() { head = nullptr; }
    void insertNode(int);
    void printList();
    void deleteNode(int);
};

#endif // LINKED_LIST_H
