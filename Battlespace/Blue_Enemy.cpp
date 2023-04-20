#include "Blue_Enemy.h"
#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <stdlib.h>
#include <QList>
#include "Linked_List.h"
#include <iostream>
#include <QDebug>

/**
 * @brief Blue_Enemy::Blue_Enemy Crea el objeto del enemigo azul e inicia el timer del movimiento
 *
 */
Blue_Enemy::Blue_Enemy()
{
    //Setups
    setPos(800,random_number);
    setPixmap(QPixmap(":/Images/Blue_Enemy"));

    //Movement of the blue enemy
    QTimer *timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(move())); //conect method that repeats the method everytime it recives the signal
    timer->start(50); //Signal every 50 miliseconds
}

/**
 * @brief Blue_Enemy::setEnemies_List Define la lista de las coordenadas de los eneemigos en la clase
 * @param enemies_list Lista de los enemigos de otra clase
 */
void Blue_Enemy::setEnemies_List(Linkedlist *enemies_list)
{
    this->enemies_list = enemies_list;
}

/**
 * @brief Blue_Enemy::setWave_Info Define la lista del objeto de los enemigos en la clase
 * @param waves_info Lista de los objetos de los enemigos
 */
void Blue_Enemy::setWave_Info(QGraphicsPixmapItem *waves_info[4])
{
    for (int i = 0; i < 4; ++i) {
        if (waves_info[i] != nullptr){
            this->waves_info[i] = waves_info[i];
        }
    }
}

/**
 * @brief Blue_Enemy::move Funcion del movimiento del enemigo azul
 */
void Blue_Enemy::move()
{
    //Colison od the blue enemy with the bullet
    QList<QGraphicsItem *> colliding_items = collidingItems(); //List of the colliding items
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Bullet)){ //Condition if the blue enemy colides with the bullet

            if (blue_life <= 0){
                //List of enemies
                enemies_list->deleteNode(this);
                std::cout << "[ ";
                enemies_list->printList();
                std::cout << " ]" << std::endl;

                //Array List
                removeEnemy();
                print_Wave_info();

                // remove them both
                scene()->removeItem(colliding_items[i]);
                scene()->removeItem(this);

                // delete them both
                delete colliding_items[i];
                delete this;
                return;
            }
            else{
                Bullet *bu =  qgraphicsitem_cast<Bullet *>(colliding_items[i]);
                if (bu->damaged){
                    blue_life = blue_life - 0.5;
                    qDebug() << "blue: " << blue_life;
                    scene()->removeItem(colliding_items[i]);
                    delete colliding_items[i];
                    return;
                }
                else{
                    scene()->removeItem(colliding_items[i]);
                    scene()->removeItem(this);
                    enemies_list->deleteNode(this);
                    std::cout << "nose; ";
                    print_Wave_info();
                    removeEnemy();
                    print_Wave_info();
                    qDebug() << "se ha eliminado un enemigo azul";
                    std::cout << "[ ";
                    enemies_list->printList();
                    std::cout << " ]" << std::endl;
                    delete colliding_items[i];
                    delete this;
                    return;
                }
            }
        }
    }
    //Pasive movement of the blue enemy
    setPos(x() - 10,y());
    if (pos().x() <= -20){ //Condition if the blue enemy gets to the end of the screen
        scene()->removeItem(this);
        delete this;
    }
}

/**
 * @brief Blue_Enemy::removeEnemy Quita la direccion de memoria de los objetos en el arreglo
 */
void Blue_Enemy::removeEnemy()
{
    delete waves_info[0];
    for (int i = 0; i < 4 - 1; i++) {
        waves_info[i] = waves_info[i + 1];
    }
    waves_info_size--;
}

/**
 * @brief Blue_Enemy::print_Wave_info Imprime las direcciones de los objetos del arreglo
 */
void Blue_Enemy::print_Wave_info()
{
    for (int i = 0; i < waves_info_size; ++i) {
        std::cout << waves_info[i] << std::endl;
    }
}
