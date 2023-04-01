#ifndef WIN_WINDOW_H
#define WIN_WINDOW_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>

class Win_Window: public QGraphicsView{
public:
  Win_Window(QWidget * parent=0);

  void main_menu();

  QGraphicsScene * scene;
};

#endif // WIN_WINDOW_H
