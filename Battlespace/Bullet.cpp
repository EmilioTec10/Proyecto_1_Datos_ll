#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <QString>
#include <QDebug>

/**
 * @brief Bullet::Bullet Metodo para crear el objeto de la bala en la escena e iniciar su movimiento pasivo
 */
Bullet::Bullet()
{
    setPixmap(QPixmap(":/Images/purple_laser.png"));

    //Movement of the bullet
    connect(timer,SIGNAL(timeout()),this,SLOT(move())); //connect method that actives the move method every time the timer stops
    timer->start(50); //Set time to the timer to stop
}

/**
 * @brief Bullet::setCollector Define el collector en esta clase
 * @param collector Collector de la otra clase
 */
void Bullet::setCollector(Collector *collector)
{
    this->collector = collector;
}

/**
 * @brief Bullet::set_CollectorLabel Define el label en esta clase
 * @param bullet_collector Label del collector en la otra clase
 */
void Bullet::set_CollectorLabel(QGraphicsTextItem *bullet_collector)
{
    this->bullet_collector = bullet_collector;
}

/**
 * @brief Bullet::move Funcion que hace que la bala se mueva en la escena
 */
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
            qDebug() << "size: " << collector->size;
            bullet_collector->setPlainText("Bullet Collector: " + QString::number(collector->size));
        }
    }
}
