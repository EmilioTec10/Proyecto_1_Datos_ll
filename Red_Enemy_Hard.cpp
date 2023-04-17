#include "Red_Enemy_Hard.h"
#include "Bullet.h"
#include "Normal_Game.h"
#include "XML_Reader.h"
#include <QTimer>
#include <QGraphicsScene>
#include <stdlib.h>
#include <QList>
#include <iostream>

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

void Red_Enemy_Hard::setEnemies_List(Linkedlist *enemies_list)
{
    this->enemies_list = enemies_list;
}

void Red_Enemy_Hard::move()
{
    XML_Reader xml_reader;
    xml_reader.XML_Data_Finder("/home/emmanuel/CLionProjects/Proyecto_1_Datos_ll/Battlespace/Raged_Powers_XML5.xml");
    value_speed = xml_reader.newest_data;
    // if bullet collides with enemy, destroy both
       QList<QGraphicsItem *> colliding_items = collidingItems();
       for (int i = 0, n = colliding_items.size(); i < n; ++i){
           if (typeid(*(colliding_items[i])) == typeid(Bullet)){

               if (red_life == 0){
                   enemies_list->deleteNode(this);
                   // qDebug() << "se ha eliminado un enemigo rojo";
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
                       // qDebug() << "red: " << red_life;
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
