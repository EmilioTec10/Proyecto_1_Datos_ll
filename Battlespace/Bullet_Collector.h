#ifndef LINKED_BULLET_LIST_H
#define LINKED_BULLET_LIST_H

#include <QGraphicsScene>

class Bullet;

class Bullet_Node
{
public:
    //Data of the node
    Bullet_Node* next;
    Bullet *bullet = nullptr;

    //Main methods
    Bullet_Node(Bullet *bullet);
};

class Collector
{
public:
    Collector();

    int size = 0;

    Bullet_Node* head;

    void insertNode(Bullet *bullet);
    void printList();
    void deleteHead();
    void increment_size();
    void decrement_size();
    void useBullet(QGraphicsScene *scene, int x, int y);
};


#endif // LINKED_BULLET_LIST_H
