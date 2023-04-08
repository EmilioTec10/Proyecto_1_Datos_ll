#ifndef BLUE_ENEMY_HARD_H
#define BLUE_ENEMY_HARD_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include "Linked_List.h"

class Blue_Enemy_Hard: public QObject ,public QGraphicsPixmapItem{
    Q_OBJECT
public:

    Blue_Enemy_Hard();

    //Variables of the enemy
    int random_number = rand() % 550;
    int token = 0;
    int value_speed_blue;
    void setEnemies_List(Linkedlist *enemies_list);

public slots:

    void move();

private:

    Linkedlist *enemies_list;
};


#endif // BLUE_ENEMY_HARD_H
