#include "Bullet_Collector.h"
#include "Bullet.h"
#include <QGraphicsScene>
#include <QDebug>



Bullet_Node::Bullet_Node(Bullet *bullet)
{
    this->bullet = bullet;
    this->bullet->damaged = true;
    this->next = nullptr;
}

Collector::Collector()
{
    head = nullptr;
}

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

void Collector::printList()
{
    Bullet_Node* temp = head;

    if (head == nullptr) {
        return;
    }

    while (temp != nullptr) {

        temp = temp->next;
    }
}

void Collector::deleteHead()
{
    if (head){
        Bullet_Node *nodeToEliminate = head;
        head = head->next;
        delete nodeToEliminate;
    }
}

void Collector::increment_size()
{
    size++;
}

void Collector::decrement_size()
{
    size--;
}

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
