#ifndef HARD_GAME_H
#define HARD_GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "Player.h"

class Hard_Game: public QGraphicsView{
public:
    Hard_Game(QWidget * parent=0);

    QGraphicsScene * scene;
    Player * player;

};

#endif // HARD_GAME_H
