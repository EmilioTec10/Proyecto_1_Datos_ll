#ifndef EASY_GAME_H
#define EASY_GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include "Player.h"

class Easy_game: public QGraphicsView{
    Q_OBJECT
public:
    Easy_game(QWidget * parent=0);

    QTimer *timer_bulletss = new QTimer;
    int bullets_number = 60;

    QGraphicsTextItem *bullets_label = new QGraphicsTextItem("Bullets: " + QString::number(bullets_number));

    QGraphicsScene * scene;
    Player * player;
public slots:
    void decrease();
};

#endif // EASY_GAME_H
