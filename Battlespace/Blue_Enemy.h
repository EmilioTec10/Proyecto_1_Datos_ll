#ifndef BLUE_ENEMY_H
#define BLUE_ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Blue_Enemy: public QObject ,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Blue_Enemy();
public slots:
    void move();
};


#endif // BLUE_ENEMY_H
