#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include "Linked_List.h"

class Player: public QObject ,public QGraphicsPixmapItem{
    Q_OBJECT
public:

    Player(int bullets_number);

    int bullets_number;
    int enemies_screen;

    void spawn_enemies(int enemies, QGraphicsScene *scene);
    void spawn_hard_enemies(int enemies, QGraphicsScene *scene);
    void set_enemies(int enemies);

    Linkedlist *enemies_list = new Linkedlist();

public slots:

    void bullets();
    void spawn_hard_enemies(int enemies);
    void spawn_enemies(int enemies);
    void conect();
    void connector();

private:
    int enemies;
};
#endif // PLAYER_H
