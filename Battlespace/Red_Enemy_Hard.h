#ifndef RED_ENEMY_HARD_H
#define RED_ENEMY_HARD_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Red_Enemy_Hard: public QObject ,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    int red_life = 2;
    Red_Enemy_Hard();
    bool nose = true;
public slots:
    void move();
    void move_y();
};


#endif // RED_ENEMY_HARD_H
