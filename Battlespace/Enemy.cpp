#include "Enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <stdlib.h>
#include <QList>

Enemy::Enemy()
{
    int random_number = rand() % 550;

    setPos(800,random_number);

    setRect(0,0,50,50);

    QTimer *timer = new QTimer;
    QTimer *timer_y = new QTimer;

    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    connect(timer_y,SIGNAL(timeout()),this,SLOT(move_y()));

    timer->start(50);
    timer_y->start(1000);
}

void Enemy::move()
{
    setPos(x() - 10,y());
    if (pos().x() <= 0){
        scene()->removeItem(this);
        delete this;
    }
}
void Enemy::move_y(){
    setPos(x(),y()+50);
}
