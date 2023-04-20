#include "Bullet_Collector.h"
#include "Bullet.h"
#include <QGraphicsScene>
#include <QDebug>
#include <iostream>

/**
 * @brief Bullet_Node::Bullet_Node Crea el nodo que almacena la bala y la convierte en una bala dañada
 * @param bullet Bala que se almacena en el nodo
 */
Bullet_Node::Bullet_Node(Bullet *bullet)
{
    this->bullet = bullet;
    this->bullet->damaged = true;
    this->next = nullptr;
}

/**
 * @brief Collector::Collector Crea el collector collocando la cabeza como nula
 */
Collector::Collector()
{
    head = nullptr;
}

/**
 * @brief Collector::insertNode Funcion que inserta un nuevo nodo en el bullet collector
 * @param bullet Bala que se inserta en el nodo
 */
void Collector::insertNode(Bullet *bullet)
{
    increment_size();

    Bullet_Node* newNode = new Bullet_Node(bullet);

    if (head == nullptr) {
        head = newNode;
        return;
    }

    Bullet_Node* temp = head;
    while (temp->next != nullptr) {

        temp = temp->next;
    }
    temp->next = newNode;
}

/**
 * @brief Collector::printList Funcion que imprime el bullet collector
 */
void Collector::printList()
{
    Bullet_Node* temp = head;

    if (head == nullptr) {
        qDebug() << "List empty";
        return;
    }

    while (temp != nullptr) {
        std::cout << temp->bullet << std::endl;
        temp = temp->next;
    }
}

/**
 * @brief Collector::deleteHead Funcion que borra la cabeza del nodo
 */
void Collector::deleteHead()
{
    if (head){
        Bullet_Node *nodeToEliminate = head;
        head = head->next;
        delete nodeToEliminate;
    }
}

/**
 * @brief Collector::increment_size funcion que incrementa el tamaño del bullet collector
 */
void Collector::increment_size()
{
    size++;
}

/**
 * @brief Collector::increment_size funcion que disminuye el tamaño del bullet collector
 */
void Collector::decrement_size()
{
    size--;
}

/**
 * @brief Collector::useBullet Funcion que usa la bala que esta a la cabeza del buller collector
 * @param scene Escena necesaria para poner la bala
 * @param x Poscion de la nave en el eje x
 * @param y Poscion de la nave en el eje y
 */
void Collector::useBullet(QGraphicsScene *scene, int x, int y)
{
    if (head == nullptr){
        return;
    }
    else{
        decrement_size();
        this->head->bullet->setPos(x + 110, y + 35);
        scene->addItem(this->head->bullet);
        this->head->bullet->timer->start();
        deleteHead();
    }
}

