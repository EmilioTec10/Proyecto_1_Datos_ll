#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsTextItem>
#include <QTimer>
#include "Bullet_Collector.h"

class Damaged_Bullet;

class Bullet: public QObject ,public QGraphicsPixmapItem{
    Q_OBJECT
public:

    Bullet();
    Collector *collector = nullptr;
    QTimer *timer = new QTimer;
    void setCollector(Collector *collector);
    void set_CollectorLabel(QGraphicsTextItem *bullet_collector);

    bool damaged = false;

public slots:

    void move();
private:
    Damaged_Bullet *damaged_bullet;
    QGraphicsTextItem *bullet_collector;
};

#endif // BULLET_H
