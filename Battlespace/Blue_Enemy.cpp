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
    //Setups
    setPos(800,random_number);
    setPixmap(QPixmap(":/Images/BlueSpaceShip"));

    //Movement of the blue enemy
    QTimer *timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(move())); //conect method that repeats the method everytime it recives the signal
    timer->start(50); //Signal every 50 miliseconds
}

void Blue_Enemy::setEnemies_List(Linkedlist *enemies_list)
{
    this->enemies_list = enemies_list;
}

void Blue_Enemy::move()
{
    //Colison od the blue enemy with the bullet
    QList<QGraphicsItem *> colliding_items = collidingItems(); //List of the colliding items
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Bullet)){ //Condition if the blue enemy colides with the bullet

                //List of enemies
                enemies_list->printList();
                qDebug() << "";
                enemies_list->deleteNode(this);
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
    //Pasive movement of the blue enemy
    setPos(x() - 10,y());
    if (pos().x() <= -1){ //Condition if the blue enemy gets to the end of the screen
        scene()->removeItem(this);
        delete this;
    }
}
