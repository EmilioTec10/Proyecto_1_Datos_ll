#ifndef RED_ENEMY_H
#define RED_ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Red_Enemy: public QObject ,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    int red_life = 2;
    Red_Enemy();
public slots:
    void move();
};

#endif // RED_ENEMY_H
