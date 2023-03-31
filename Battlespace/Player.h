#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include "Linked_List.h"

class Player: public QObject ,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    int bullets_number;
    int enemies_screen;
    Player(int bullets_number);
    void spawn_enemies(int enemies, QGraphicsScene *scene);
    void spawn_hard_enemies(int enemies, QGraphicsScene *scene);

    Linkedlist *enemies_list = new Linkedlist();

public slots:
    void bullets();
    void spawn_hard_enemies(int enemies);
    void spawn_enemies(int enemies);
    void conect();
    void connector();
};
#endif // PLAYER_H
