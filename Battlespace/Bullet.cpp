#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>

Bullet::Bullet()
{
    setPixmap(QPixmap(":/Images/red_laser.png"));

    //Movement of the bullet
    QTimer *timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(move())); //connect method that actives the move method every time the timer stops
    timer->start(50); //Set time to the timer to stop
}
void Bullet::move()
{
    //Pasive movement of the bullet
    setPos(x() + 15,y());
    if (pos().x() > 800){ //Condition if the bullet gets to the end of the screen
        scene()->removeItem(this);
        delete this;
    }
}
