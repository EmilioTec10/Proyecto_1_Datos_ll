#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QString>
#include <QDebug>


Bullet::Bullet()
{
    setPixmap(QPixmap(":/Images/purple_laser.png"));

    //Movement of the bullet
    connect(timer,SIGNAL(timeout()),this,SLOT(move())); //connect method that actives the move method every time the timer stops
    timer->start(50); //Set time to the timer to stop
}

void Bullet::setCollector(Collector *collector)
{
    this->collector = collector;
}

void Bullet::set_CollectorLabel(QGraphicsTextItem *bullet_collector)
{
    this->bullet_collector = bullet_collector;
}

void Bullet::move()
{
    //Pasive movement of the bullet
    setPos(x() + 15,y());
    if (pos().x() > 800){ //Condition if the bullet gets to the end of the screen
        if (damaged){
            timer->stop();
            scene()->removeItem(this);
        }
        else{

            collector->insertNode(this);

            timer->stop();

            scene()->removeItem(this);

            bullet_collector->setPlainText("Bullet Collector: " + QString::number(collector->size));
        }
    }
}