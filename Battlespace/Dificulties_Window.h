#ifndef DIFICULTIES_WINDOW_H
#define DIFICULTIES_WINDOW_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>

class Dificulties: public QGraphicsView{
public:
  Dificulties(QWidget * parent=0);

  void easy();
  void normal();
  void hard();

  QGraphicsScene * scene;
};

#endif // DIFICULTIES_WINDOW_H
