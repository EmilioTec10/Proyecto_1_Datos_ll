#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>

Bullet::Bullet()
{
    setPixmap(QPixmap(":/Images/bullet (1).png"));

    QTimer *timer = new QTimer;

    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(50);
}
void Bullet::move()
{
    setPos(x() + 15,y());
    if (pos().x() > 800){
        scene()->removeItem(this);
        delete this;
    }
}
