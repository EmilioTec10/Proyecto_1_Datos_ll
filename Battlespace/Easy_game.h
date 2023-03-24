#ifndef EASY_GAME_H
#define EASY_GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "Player.h"

class Easy_game: public QGraphicsView{
public:
    Easy_game(QWidget * parent=0);

    QGraphicsScene * scene;
    Player * player;

};

#endif // EASY_GAME_H
