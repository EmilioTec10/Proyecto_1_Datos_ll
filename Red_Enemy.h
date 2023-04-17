#ifndef RED_ENEMY_H
#define RED_ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include "Linked_List.h"
#include <QGuiApplication>

class Red_Enemy: public QObject ,public QGraphicsPixmapItem{
Q_OBJECT
public:
    Red_Enemy();
    int x_axis_movement=5;
    int random_number = rand() % 550;
    int token = 0;
    int value_speed;
    float red_life = 2.00;
    void set_new_axis_movement_value(int valor);
    void setEnemies_List(Linkedlist *enemies_list);

public slots:

    void move();

private:

    Linkedlist *enemies_list;

};

#endif // RED_ENEMY_H