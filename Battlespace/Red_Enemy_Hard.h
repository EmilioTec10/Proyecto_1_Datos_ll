#ifndef RED_ENEMY_HARD_H
#define RED_ENEMY_HARD_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include "Linked_List.h"

class Red_Enemy_Hard: public QObject ,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    int random_number = rand() % 550;
    int red_life = 3;
    Red_Enemy_Hard();
    bool nose = true;
    void setEnemies_List(Linkedlist *enemies_list);
public slots:
    void move();
    void move_y();
private:
    Linkedlist *enemies_list;
};


#endif // RED_ENEMY_HARD_H
