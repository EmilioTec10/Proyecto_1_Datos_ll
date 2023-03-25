#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsRectItem>
#include <QObject>

class Enemy: public QObject ,public QGraphicsRectItem{
    Q_OBJECT
public:
    Enemy();
public slots:
    void move();
    void move_y();
};

#endif // ENEMY_H
