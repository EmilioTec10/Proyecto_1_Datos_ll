#ifndef GAME_OVER_H
#define GAME_OVER_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>

class Game_Over: public QGraphicsView{
public:
  Game_Over(QWidget * parent=0);
  void main_menu();

  QGraphicsScene * scene;
};

#endif // GAME_OVER_H
