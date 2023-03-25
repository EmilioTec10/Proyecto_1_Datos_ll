#include "Red_Enemy.h"
#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <stdlib.h>
#include <QList>

Red_Enemy::Red_Enemy()
{
    int random_number = rand() % 550;

    setPos(800,random_number);

    setPixmap(QPixmap(":/Images/RedSpaceShip"));

    QTimer *timer = new QTimer;

    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(50);
}

void Red_Enemy::move()
{
    // if bullet collides with enemy, destroy both
       QList<QGraphicsItem *> colliding_items = collidingItems();
       for (int i = 0, n = colliding_items.size(); i < n; ++i){
           if (typeid(*(colliding_items[i])) == typeid(Bullet)){

               if (red_life == 0){
                   // remove them both
                   scene()->removeItem(colliding_items[i]);
                   scene()->removeItem(this);
                   delete this;
                   // delete them both
                   delete colliding_items[i];
                   return;
               }
               else{
                   red_life--;
                   scene()->removeItem(colliding_items[i]);
                   delete colliding_items[i];
                   return;
               }
           }
       }
    setPos(x() - 5,y());
    if (pos().x() <= 0){
        scene()->removeItem(this);
        delete this;
    }
}
