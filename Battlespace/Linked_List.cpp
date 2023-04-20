#include "Linked_List.h"
#include "Blue_Enemy.h"
#include "Red_Enemy.h"
#include "Red_Enemy_Hard.h"
#include "Blue_Enemy_Hard.h"
#include <iostream>
#include <iostream>

/**
 * @brief Node::Node Constructor que crea un nodo con un enemigo rojo
 * @param red_enemy Enemigo rojo que se va a insertar en el nodo
 */
Node::Node(Red_Enemy *red_enemy)
{
    this->red_enemy = red_enemy;
    this->next = nullptr;
}

/**
 * @brief Node::Node Constructor que crea un nodo con un enemigo rojo del modo dificil
 * @param red_enemy Enemigo rojo del modo dificil que se va a insertar en el nodo
 */
Node::Node(Red_Enemy_Hard *red_hard_enemy)
{
    this->red_hard_enemy = red_hard_enemy;
    this->next = nullptr;
}

/**
 * @brief Node::Node Constructor que crea un nodo con un enemigo azul
 * @param red_enemy Enemigo azul que se va a insertar en el nodo
 */
Node::Node(Blue_Enemy *blue_enemy)
{
    this->blue_enemy = blue_enemy;
    this->next = nullptr;
}

/**
 * @brief Node::Node Constructor que crea un nodo con un enemigo azul del modo dificil
 * @param red_enemy Enemigo azul del modo dificil que se va a insertar en el nodo
 */
Node::Node(Blue_Enemy_Hard *blue_hard_enemy)
{
    this->blue_hard_enemy = blue_hard_enemy;
    this->next = nullptr;
}

/**
 * @brief Linkedlist::insertNode Metodo que inserta un nodo del enemigo rojo en la lista enlazada
 * @param red_enemy Enemigo rojo a insertar
 * @param token NUmero del enemigo rojo
 */
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

/**
 * @brief Linkedlist::insertNode Metodo que inserta un nodo del enemigo azul del modo dificil en la lista enlazada
 * @param red_enemy Enemigo azul del modo dificil a insertar
 * @param token NUmero del enemigo azul del modo dificil
 */
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

/**
 * @brief Linkedlist::insertNode Metodo que inserta un nodo del enemigo azul en la lista enlazada
 * @param red_enemy Enemigo azul a insertar
 * @param token NUmero del enemigo azul
 */
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

/**
 * @brief Linkedlist::insertNode Metodo que inserta un nodo del enemigo rojo del modo dificil en la lista enlazada
 * @param red_enemy Enemigo rojo del modo dificil a insertar
 * @param token NUmero del enemigo rojo del modo dificil
 */
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

/**
 * @brief Linkedlist::printList Metodo que imprime la lista enlazada completa
 */
void Linkedlist::printList()
{
    Node* temp = head;

    if (head == nullptr) {
        qDebug() << "List empty";
        return;
    }

    while (temp != nullptr) {

        if (temp->blue_enemy != nullptr){

            std::cout << "(800, " << temp->blue_enemy->random_number << ")" << " , ";
            temp = temp->next;
        }
        else if (temp->blue_hard_enemy != nullptr){

            std::cout << "(800, "<< temp->blue_hard_enemy->random_number << ")" << " , ";
            temp = temp->next;
        }
        else if (temp->red_enemy != nullptr){

            std::cout << "(800, " << temp->red_enemy->random_number << ")" << " , ";
            temp = temp->next;
        }
        else if (temp->red_hard_enemy != nullptr){

            std::cout << "(800, " << temp->red_hard_enemy->random_number << ")" << " , ";
            temp = temp->next;
        }
    }
}

/**
 * @brief Linkedlist::deleteNode Metodo que borra el nodo del eneemigo azul en la lista
 * @param blue_enemy Enemigo azul a eliminar de la lista
 */
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


/**
 * @brief Linkedlist::deleteNode Metodo que borra el nodo del eneemigo rojo en la lista
 * @param blue_enemy Enemigo rojo a eliminar de la lista
 */
void Linkedlist::deleteNode(Red_Enemy *red_enemy)
{

    Node* current = head;
    Node* prev = NULL;
    while (current != NULL) {
        if(current->red_enemy != nullptr){
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


/**
 * @brief Linkedlist::deleteNode Metodo que borra el nodo del eneemigo azul del modo dificil en la lista
 * @param blue_enemy Enemigo azul a eliminar de la lista
 */
void Linkedlist::deleteNode(Blue_Enemy_Hard *blue_hard_enemy)
{
    Node* current = head;
    Node* prev = NULL;
    while (current != NULL) {
        if(current->blue_hard_enemy != nullptr){
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

/**
 * @brief Linkedlist::deleteNode Metodo que borra el nodo del eneemigo rojo del modo dificil en la lista
 * @param blue_enemy Enemigo rojo a eliminar de la lista
 */
void Linkedlist::deleteNode(Red_Enemy_Hard *red_hard_enemy)
{
    Node* current = head;
    Node* prev = NULL;
    while (current != NULL) {
        if(current->red_hard_enemy != nullptr){
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
