#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Player: public QObject ,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    void keyPressEvent(QKeyEvent * event);
public slots:
    void bullets();
    void spawn_Blue_enemies();
    void spawn_Red_enemies();

};
#endif // PLAYER_H
