#ifndef HARD_GAME_H
#define HARD_GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include "Player.h"

class Hard_Game: public QGraphicsView{
    Q_OBJECT
public:
    Hard_Game(QWidget * parent=0);

    QTimer *timer_bulletss = new QTimer;
    int bullets_number = 40;

    QGraphicsTextItem *bullets_label = new QGraphicsTextItem("Bullets: " + QString::number(bullets_number));

    QGraphicsScene * scene;
    Player * player;
public slots:
    void decrease();
};

#endif // HARD_GAME_H
