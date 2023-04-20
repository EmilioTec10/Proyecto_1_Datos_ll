#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsTextItem>
#include "Linked_List.h"
#include "Bullet_Collector.h"

class Player: public QObject ,public QGraphicsPixmapItem{
    Q_OBJECT
public:

    Player(int bullets_number);

    int bullets_number;
    int enemies_screen;

    void spawn_enemies(int enemies, QGraphicsScene *scene);
    void spawn_hard_enemies(int enemies, QGraphicsScene *scene);
    void set_enemies(int enemies);
    void setCollector(Collector *collector);
    void set_CollectorLabel(QGraphicsTextItem *bullet_collector);
    void removeEnemy();
    void print_Wave_info();

    Linkedlist *enemies_list = new Linkedlist();

public slots:

    void bullets();
    void spawn_hard_enemies(int enemies);
    void spawn_enemies(int enemies);
    void conect();
    void connector();

private:
    int enemies;
    int waves_info_size = 4;
    QGraphicsTextItem *bullet_collector;
    Collector *collector;
    QGraphicsPixmapItem* waves_info[4];
    QGraphicsPixmapItem* waves_info_hard[3];
};
#endif // PLAYER_H
