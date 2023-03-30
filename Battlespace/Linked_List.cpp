#include "Linked_List.h"
#include <QDebug>

Node::Node()
{
    data = 0;
    next = nullptr;
}

Node::Node(int data)
{
    this->data = data;
    this->next = nullptr;
}

void Linkedlist::insertNode(int data)
{
    Node* newNode = new Node(data);

    if (head == nullptr) {
        head = newNode;
        return;
    }

    Node* temp = head;
    while (temp->next != nullptr) {

        temp = temp->next;
    }

    temp->next = newNode;
}

void Linkedlist::printList()
{
    Node* temp = head;

    if (head == nullptr) {
        qDebug() << "List empty";
        return;
    }

    while (temp != nullptr) {
        qDebug() << temp->data << " , ";
        temp = temp->next;
    }
}

void Linkedlist::deleteNode(int node_index)
{

    Node *temp1 = head, *temp2 = NULL;
    int ListLen = 0;

    if (head == NULL) {
        qDebug() << "List empty.";
        return;
    }

    while (temp1 != NULL) {
        temp1 = temp1->next;
        ListLen++;
    }

    if (ListLen < node_index) {
        qDebug() << "Index out of range";
        return;
    }

    temp1 = head;

    if (node_index == 1) {

        // Update head
        head = head->next;
        delete temp1;
        return;
    }

    while (node_index-- > 1) {

        temp2 = temp1;

        temp1 = temp1->next;
    }

    temp2->next = temp1->next;

    delete temp1;
}
