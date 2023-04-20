#include "Red_Enemy.h"
#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <stdlib.h>
#include <iostream>
#include <QList>

/**
 * @brief Red_Enemy::Red_Enemy Constructor que genera un enemigo rojo
 */
Red_Enemy::Red_Enemy()
{
    setPos(800,random_number);

    setPixmap(QPixmap(":/Images/Red_Enemy"));

    QTimer *timer = new QTimer;

    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(50);
}

/**
 * @brief Red_Enemy::setEnemies_List Define la lista enlazada de las coordenadas
 * @param enemies_list Lista enlazada de la otra clase
 */
void Red_Enemy::setEnemies_List(Linkedlist *enemies_list)
{
    this->enemies_list = enemies_list;
}

/**
 * @brief Red_Enemy::setWave_Info Define el arreglo de la informacion de las oleadas
 * @param waves_info Lista de la informacion de las oledas en la otra clase
 */
void Red_Enemy::setWave_Info(QGraphicsPixmapItem *waves_info[4])
{
    for (int i = 0; i < 4; ++i) {
        if (waves_info[i] != nullptr){
            this->waves_info[i] = waves_info[i];
        }
    }
}

/**
 * @brief Red_Enemy::move Metodo que hace que el enemigo rojo se mueva pasivamente y ademas detecta las colisiones con las balas
 */
void Red_Enemy::move()
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

                   removeEnemy();
                   print_Wave_info();

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
 * @brief Red_Enemy::removeEnemy Metodo que quita el enemigo de la informacion de las oleadas
 */
void Red_Enemy::removeEnemy()
{
    delete waves_info[0];
    for (int i = 0; i < 4 - 1; i++) {
        waves_info[i] = waves_info[i + 1];
    }
    waves_info_size--;
}

/**
 * @brief Red_Enemy::print_Wave_info Metodo que imprime la informacion de las oleadas
 */
void Red_Enemy::print_Wave_info()
{
    for (int i = 0; i < waves_info_size; ++i) {
        std::cout << waves_info[i] << std::endl;
    }
}
