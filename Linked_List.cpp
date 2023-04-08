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

void Linkedlist::insertNode(Red_Enemy *red_enemy, int token)
{
    Node* newNode = new Node(red_enemy);
    newNode->token = token;

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
void Linkedlist::insertNode(Blue_Enemy_Hard *blue_hard_enemy, int token)
{
    Node* newNode = new Node(blue_hard_enemy);
    newNode->token = token;

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
void Linkedlist::insertNode(Blue_Enemy *blue_enemy, int token)
{
    Node* newNode = new Node(blue_enemy);
    newNode->token = token;

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
void Linkedlist::insertNode(Red_Enemy_Hard *red_hard_enemy, int token)
{
    Node* newNode = new Node(red_hard_enemy);
    newNode->token = token;

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

void Linkedlist::deleteNode(Blue_Enemy *blue_enemy)
{

    Node* current = head;
    Node* prev = NULL;
    while (current != NULL) {
        if(current->blue_enemy != nullptr){
            if (current->token == blue_enemy->token) {
                if (prev != NULL) {
                    prev->next = current->next;
                }
                else {
                    head = current->next;
                }
                Node* temp = current;
                current = current->next;
                delete temp;
            }
            else {
                prev = current;
                current = current->next;
            }
        }
        else{
            prev = current;
            current = current->next;
        }
    }
}
void Linkedlist::deleteNode(Red_Enemy *red_enemy)
{

    Node* current = head;
    Node* prev = NULL;
    while (current != NULL) {
        if(current->blue_enemy != nullptr){
            if (current->token == red_enemy->token) {
                if (prev != NULL) {
                    prev->next = current->next;
                }
                else {
                    head = current->next;
                }
                Node* temp = current;
                current = current->next;
                delete temp;
            }
            else {
                prev = current;
                current = current->next;
            }
        }
        else{
            prev = current;
            current = current->next;
        }
    }
}

void Linkedlist::deleteNode(Blue_Enemy_Hard *blue_hard_enemy)
{
    Node* current = head;
    Node* prev = NULL;
    while (current != NULL) {
        if(current->blue_enemy != nullptr){
            if (current->token == blue_hard_enemy->token) {
                if (prev != NULL) {
                    prev->next = current->next;
                }
                else {
                    head = current->next;
                }
                Node* temp = current;
                current = current->next;
                delete temp;
            }
            else {
                prev = current;
                current = current->next;
            }
        }
        else{
            prev = current;
            current = current->next;
        }
    }
}

void Linkedlist::deleteNode(Red_Enemy_Hard *red_hard_enemy)
{
    Node* current = head;
    Node* prev = NULL;
    while (current != NULL) {
        if(current->blue_enemy != nullptr){
            if (current->token == red_hard_enemy->token) {
                if (prev != NULL) {
                    prev->next = current->next;
                }
                else {
                    head = current->next;
                }
                Node* temp = current;
                current = current->next;
                delete temp;
            }
            else {
                prev = current;
                current = current->next;
            }
        }
        else{
            prev = current;
            current = current->next;
        }
    }
}
