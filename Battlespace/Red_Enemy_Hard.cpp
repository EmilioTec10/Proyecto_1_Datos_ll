#include "Red_Enemy_Hard.h"
#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <stdlib.h>
#include <QList>
#include <iostream>
#include <QDebug>

/**
 * @brief Red_Enemy::Red_Enemy Constructor que genera un enemigo rojo del modo dificil
 */
Red_Enemy_Hard::Red_Enemy_Hard()
{
    setPos(800,random_number);

    setPixmap(QPixmap(":/Images/Red_hard.png"));

    QTimer *timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(50);

    QTimer *timer_y = new QTimer;
    connect(timer_y,SIGNAL(timeout()),this,SLOT(move_y()));
    timer_y->start(1000);
}

/**
 * @brief Red_Enemy::setEnemies_List Define la lista enlazada de las coordenadas
 * @param enemies_list Lista enlazada de la otra clase
 */
void Red_Enemy_Hard::setEnemies_List(Linkedlist *enemies_list)
{
    this->enemies_list = enemies_list;
}

/**
 * @brief Red_Enemy::move Metodo que hace que el enemigo rojo del modo dificil se mueva pasivamente y ademas detecta las colisiones con las balas
 */
void Red_Enemy_Hard::move()
{
    // if bullet collides with enemy, destroy both
       QList<QGraphicsItem *> colliding_items = collidingItems();
       for (int i = 0, n = colliding_items.size(); i < n; ++i){
           if (typeid(*(colliding_items[i])) == typeid(Bullet)){

               if (red_life == 0){
                   enemies_list->deleteNode(this);
                   qDebug() << "se ha eliminado un enemigo rojo";
                   std::cout << "[ ";
                   enemies_list->printList();
                   std::cout << " ]" << std::endl;
                   // remove them both
                   scene()->removeItem(colliding_items[i]);
                   scene()->removeItem(this);
                   delete this;
                   // delete them both
                   delete colliding_items[i];
                   return;
               }
               else{
                   Bullet *bu =  qgraphicsitem_cast<Bullet *>(colliding_items[i]);
                   if (bu->damaged){
                       red_life = red_life - 0.5;
                       qDebug() << "red: " << red_life;
                       scene()->removeItem(colliding_items[i]);
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
       }
    setPos(x() - 5,y());
    if (pos().x() <= 0){
        scene()->removeItem(this);
        delete this;
    }
}
/**
 * @brief Red_Enemy_Hard::move_y Metodo que hace que las naves rojas del modo dificil se muevan en el eje y
 */
void Red_Enemy_Hard::move_y(){

    int random_number = rand() % 2;

    if (random_number == 1){
        if (y() - 50 > 50){
            setPos(x(),y() - 20);
        }
        else {
            setPos(x(),y() + 20);
        }
    }
    else {
        if (y() + 50 < 550){
            setPos(x(),y() + 20);
        }
        else {
            setPos(x(),y() - 20);
        }
    }
}
