#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QString>
#include <QDebug>
#include <iostream>

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
        std::cerr << "SI PUTO FUNCIONO" << std::endl;
        if (damaged){
            timer->stop();
            scene()->removeItem(this);
        }
        else{
            std::cerr << "SI PUTO FUNCIONO 2" << std::endl;
            collector->printList();
            collector->insertNode(this);
            std::cerr << "SI PUTO FUNCIONO 3" << std::endl;
            timer->stop();
            std::cerr << "SI PUTO FUNCIONO 4" << std::endl;
            scene()->removeItem(this);
            qDebug() << "size: " << collector->size;
            bullet_collector->setPlainText("Bullet Collector: " + QString::number(collector->size));
        }
    }
}