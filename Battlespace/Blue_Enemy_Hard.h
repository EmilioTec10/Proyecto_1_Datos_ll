#ifndef BLUE_ENEMY_HARD_H
#define BLUE_ENEMY_HARD_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Blue_Enemy_Hard: public QObject ,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Blue_Enemy_Hard();
public slots:
    void move();
};


#endif // BLUE_ENEMY_HARD_H
