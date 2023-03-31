#include "Linked_List.h"
#include "Blue_Enemy.h"
#include "Red_Enemy.h"
#include "Red_Enemy_Hard.h"
#include "Blue_Enemy_Hard.h"
#include <QDebug>


Node::Node(Red_Enemy *red_enemy)
{
    this->red_enemy = red_enemy;
    this->next = nullptr;
}

Node::Node(Red_Enemy_Hard *red_hard_enemy)
{
    this->red_hard_enemy = red_hard_enemy;
    this->next = nullptr;
}

Node::Node(Blue_Enemy *blue_enemy)
{
    this->blue_enemy = blue_enemy;
    this->next = nullptr;
}

Node::Node(Blue_Enemy_Hard *blue_hard_enemy)
{
    this->blue_hard_enemy = blue_hard_enemy;
    this->next = nullptr;
}

void Linkedlist::insertNode(Red_Enemy *red_enemy)
{
    Node* newNode = new Node(red_enemy);

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
void Linkedlist::insertNode(Blue_Enemy_Hard *blue_hard_enemy)
{
    Node* newNode = new Node(blue_hard_enemy);

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
void Linkedlist::insertNode(Blue_Enemy *blue_enemy)
{
    Node* newNode = new Node(blue_enemy);

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
void Linkedlist::insertNode(Red_Enemy_Hard *red_hard_enemy)
{
    Node* newNode = new Node(red_hard_enemy);

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
        if (temp->blue_enemy != nullptr){

            qDebug() << "(800, " << temp->blue_enemy->random_number << ")" << " , ";
            temp = temp->next;
        }
        else if (temp->blue_hard_enemy != nullptr){

            qDebug() << "(800, "<< temp->blue_hard_enemy->random_number << ")" << " , ";
            temp = temp->next;
        }
        else if (temp->red_enemy != nullptr){

            qDebug() << "(800, " << temp->red_enemy->random_number << ")" << " , ";
            temp = temp->next;
        }
        else if (temp->red_hard_enemy != nullptr){

            qDebug() << "(800, " << temp->red_hard_enemy->random_number << ")" << " , ";
            temp = temp->next;
        }
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
