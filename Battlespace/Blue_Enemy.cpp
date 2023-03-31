#include "Blue_Enemy.h"
#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <stdlib.h>
#include <QList>
#include "Linked_List.h"
#include <QDebug>

Blue_Enemy::Blue_Enemy()
{
    setPos(800,random_number);

    setPixmap(QPixmap(":/Images/BlueSpaceShip"));

    QTimer *timer = new QTimer;

    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(50);
}

void Blue_Enemy::setEnemies_List(Linkedlist *enemies_list)
{
    this->enemies_list = enemies_list;
}

void Blue_Enemy::move()
{
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Bullet)){
                enemies_list->printList();
                qDebug() << "";
                enemies_list->deleteNode(1);
                enemies_list->printList();
                // remove them both
                scene()->removeItem(colliding_items[i]);
                scene()->removeItem(this);
                // delete them both
                delete colliding_items[i];
                delete this;
                return;
        }
    }
    setPos(x() - 10,y());
    if (pos().x() <= -1){
        scene()->removeItem(this);
        delete this;
    }
}
