#ifndef RED_ENEMY_H
#define RED_ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include "Linked_List.h"

class Red_Enemy: public QObject ,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    int random_number = rand() % 550;
    int red_life = 2;
    Red_Enemy();
    void setEnemies_List(Linkedlist *enemies_list);
public slots:
    void move();
private:
    Linkedlist *enemies_list;
};

#endif // RED_ENEMY_H
