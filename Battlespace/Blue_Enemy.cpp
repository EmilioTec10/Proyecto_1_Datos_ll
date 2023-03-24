#include "Blue_Enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <stdlib.h>
#include <QList>

Blue_Enemy::Blue_Enemy()
{
    int random_number = rand() % 550;

    setPos(800,random_number);

    setPixmap(QPixmap(":/Images/BlueSpaceShip"));

    QTimer *timer = new QTimer;

    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(50);
}

void Blue_Enemy::move()
{
    setPos(x() - 10,y());
    if (pos().x() <= 0){
        scene()->removeItem(this);
        delete this;
    }
}
