#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Player: public QObject ,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    int bullets_number;
    void keyPressEvent(QKeyEvent * event);
    Player(int bullets_number);
public slots:
    void bullets();
    void spawn_Blue_enemies();
    void spawn_Red_enemies();
    void spawn_enemies();

};
#endif // PLAYER_H
