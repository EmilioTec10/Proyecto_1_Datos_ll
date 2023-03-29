#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Player: public QObject ,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    int bullets_number;
    int enemies_screen;
    Player(int bullets_number);
    void spawn_enemies(int enemies, QGraphicsScene *scene);
public slots:
    void bullets();
    void spawn_Blue_enemies();
    void spawn_Red_enemies();
    void spawn_enemies(int enemies);
    void conect();
};
#endif // PLAYER_H
