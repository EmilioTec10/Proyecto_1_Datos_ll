#ifndef BLUE_ENEMY_H
#define BLUE_ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include "Linked_List.h"

class Blue_Enemy: public QObject ,public QGraphicsPixmapItem{
    Q_OBJECT
public:

    Blue_Enemy();

    //Variables of the enemy
    int random_number = rand() % 550;
    float blue_life = 0.5;
    int token = 0;

    void setEnemies_List(Linkedlist *enemies_list);
    void setWave_Info(QGraphicsPixmapItem* waves_info[4]);
    void removeEnemy();
    void print_Wave_info();

public slots:

    void move();

private:

    int waves_info_size = 4;
    QGraphicsPixmapItem* waves_info[4];
    Linkedlist *enemies_list;
};


#endif // BLUE_ENEMY_H
