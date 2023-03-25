#ifndef NORMAL_GAME_H
#define NORMAL_GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include "Player.h"

class Normal_Game: public QGraphicsView{
    Q_OBJECT
public:
    Normal_Game(QWidget * parent=0);

    QTimer *timer_bulletss = new QTimer;
    int bullets_number = 50;

    QGraphicsTextItem *bullets_label = new QGraphicsTextItem("Bullets: " + QString::number(bullets_number));

    QGraphicsScene * scene;
    Player * player;
public slots:
    void decrease();

};

#endif // NORMAL_GAME_H
