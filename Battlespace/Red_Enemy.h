#ifndef RED_ENEMY_H
#define RED_ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include "Linked_List.h"

class Red_Enemy: public QObject ,public QGraphicsPixmapItem{
    Q_OBJECT
public:

    Red_Enemy();

    int random_number = rand() % 550;
    float red_life = 2.00;
    int token = 0;

    void setEnemies_List(Linkedlist *enemies_list);

public slots:

    void move();

private:

    Linkedlist *enemies_list;
};

#endif // RED_ENEMY_H
