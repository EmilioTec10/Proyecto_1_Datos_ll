#include "Red_Enemy.h"
#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include "Normal_Game.h"
#include "XML_Reader.h"
#include <QList>
#include <iostream>

Red_Enemy::Red_Enemy()
{
    std::cerr << value_speed << std::endl;
    setPos(800,random_number);

    setPixmap(QPixmap(":/Images/Red_Enemy"));

    QTimer *timer = new QTimer;

    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    timer->start(50);
}

void Red_Enemy::setEnemies_List(Linkedlist *enemies_list)
{
    this->enemies_list = enemies_list;
}



void Red_Enemy::move()
{
    XML_Reader xml_reader;
    xml_reader.XML_Data_Finder("/home/emmanuel/CLionProjects/Proyecto_1_Datos_ll/Battlespace/Raged_Powers_XML2.xml");
    value_speed = xml_reader.newest_data;
    // if bullet collides with enemy, destroy both
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Bullet)){

            if (red_life == 0){
                enemies_list->printList();
                //qDebug() << "";
                enemies_list->deleteNode(this);
                enemies_list->printList();
                // remove them both
                scene()->removeItem(colliding_items[i]);
                scene()->removeItem(this);
                delete this;
                // delete them both
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


    setPos(x() - value_speed, y());
    if (pos().x() <= 0){
        scene()->removeItem(this);
        delete this;
    }
}