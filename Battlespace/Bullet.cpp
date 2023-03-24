#include "Bullet.h"
#include "Red_Enemy.h"
#include "Blue_Enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>

Bullet::Bullet()
{
    setPixmap(QPixmap(":/Images/bullet (1).png"));

    QTimer *timer = new QTimer;

    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(50);
}

void Bullet::move()
{
    // if bullet collides with enemy, destroy both
       QList<QGraphicsItem *> colliding_items = collidingItems();
       for (int i = 0, n = colliding_items.size(); i < n; ++i){
           if (typeid(*(colliding_items[i])) == typeid(Red_Enemy)){
               // remove them both
               scene()->removeItem(colliding_items[i]);
               scene()->removeItem(this);
               // delete them both
               delete colliding_items[i];
               delete this;
               return;
           }
           else if (typeid(*(colliding_items[i])) == typeid(Blue_Enemy)){
               // remove them both
               scene()->removeItem(colliding_items[i]);
               scene()->removeItem(this);
               // delete them both
               delete colliding_items[i];
               delete this;
               return;
           }
       }
    setPos(x() + 15,y());
    if (pos().x() > 800){
        scene()->removeItem(this);
        delete this;
    }
}
