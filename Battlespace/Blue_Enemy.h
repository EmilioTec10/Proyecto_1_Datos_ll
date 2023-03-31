#ifndef BLUE_ENEMY_H
#define BLUE_ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include "Linked_List.h"

class Blue_Enemy: public QObject ,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    int random_number = rand() % 550;
    Blue_Enemy();
    void setEnemies_List(Linkedlist *enemies_list);
public slots:
    void move();
private:
    Linkedlist *enemies_list;
};


#endif // BLUE_ENEMY_H
