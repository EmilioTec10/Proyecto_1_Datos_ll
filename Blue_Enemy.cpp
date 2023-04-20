#include "Blue_Enemy.h"
#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <stdlib.h>
#include <QList>
#include "Linked_List.h"
#include "XML_Reader.h"
#include <QGuiApplication>

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
 * @brief Blue_Enemy::move Funcion del movimiento del enemigo azul
 */
void Blue_Enemy::move()
{
    XML_Reader xml_reader;
    xml_reader.XML_Data_Finder("/home/emmanuel/CLionProjects/Proyecto_1_Datos_ll/Battlespace/Raged_Powers_XML3.xml");
    value_speed_blue = xml_reader.newest_data;
    //Colison od the blue enemy with the bullet
    QList<QGraphicsItem *> colliding_items = collidingItems(); //List of the colliding items
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Bullet)){ //Condition if the blue enemy colides with the bullet

            if (blue_life <= 0){
                //List of enemies
                enemies_list->deleteNode(this);


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
                    scene()->removeItem(colliding_items[i]);
                    delete colliding_items[i];
                    return;
                }
                else{
                    scene()->removeItem(colliding_items[i]);
                    scene()->removeItem(this);
                    enemies_list->deleteNode(this);
                    delete colliding_items[i];
                    delete this;
                    return;
                }
            }
        }
    }
    //Pasive movement of the blue enemy
    setPos(x() - value_speed_blue,y());
    if (pos().x() <= -20){ //Condition if the blue enemy gets to the end of the screen
        scene()->removeItem(this);
        delete this;
    }
}
