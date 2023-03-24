#include "Red_Enemy.h"
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
    setPos(x() - 5,y());
    if (pos().x() <= 0){
        scene()->removeItem(this);
        delete this;
    }
}
