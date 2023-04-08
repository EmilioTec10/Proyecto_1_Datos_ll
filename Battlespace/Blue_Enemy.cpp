#include "Blue_Enemy.h"
#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <stdlib.h>
#include <QList>
#include "Linked_List.h"
#include <iostream>
#include <QDebug>

Blue_Enemy::Blue_Enemy()
{
    //Setups
    setPos(800,random_number);
    setPixmap(QPixmap(":/Images/Blue_Enemy"));

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

            if (blue_life <= 0){
                //List of enemies
                enemies_list->deleteNode(this);
                std::cout << "[ ";
                enemies_list->printList();
                std::cout << " ]" << std::endl;

                // remove them both
                scene()->removeItem(colliding_items[i]);
                scene()->removeItem(this);

                // delete them both
                delete colliding_items[i];
                delete this;
                return;
            }
            else{
                Bullet *bu =  qgraphicsitem_cast<Bullet *>(colliding_items[i]);
                if (bu->damaged){
                    blue_life = blue_life - 0.5;
                    qDebug() << "blue: " << blue_life;
                    scene()->removeItem(colliding_items[i]);
                    delete colliding_items[i];
                    return;
                }
                else{
                    scene()->removeItem(colliding_items[i]);
                    scene()->removeItem(this);
                    enemies_list->deleteNode(this);
                    qDebug() << "se ha eliminado un enemigo azul";
                    std::cout << "[ ";
                    enemies_list->printList();
                    std::cout << " ]" << std::endl;
                    delete colliding_items[i];
                    delete this;
                    return;
                }
            }
        }
    }
    //Pasive movement of the blue enemy
    setPos(x() - 10,y());
    if (pos().x() <= -20){ //Condition if the blue enemy gets to the end of the screen
        scene()->removeItem(this);
        delete this;
    }
}
