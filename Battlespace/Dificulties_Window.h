#ifndef DIFICULTIES_WINDOW_H
#define DIFICULTIES_WINDOW_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>

class Dificulties: public QGraphicsView{
public:

  Dificulties(QWidget * parent=0);

  //Game dificulties
  void easy();
  void normal();
  void hard();

  QGraphicsScene * scene;
private:
  int width = 800;
  int height = 600;

};

#endif // DIFICULTIES_WINDOW_H
