#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include "MyRect.h"
#include <QGraphicsView>
#include <QTimer>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Escena
    QGraphicsScene *scene = new QGraphicsScene();

    //Item en la escena
    MyRect *rect = new MyRect();
    rect->setRect(0,0,100,100);

    //Agregado de el item a la escena
    scene->addItem(rect);

    //Hacer rectangulo focusiable
    rect->setFlag(QGraphicsItem::ItemIsFocusable);
    rect->setFocus();

    //Mostrar scena
    QGraphicsView *view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->show();
    view->setFixedSize(500,500);
    scene->setSceneRect(0,0,500,500);

    rect->setPos(10,150);

    QTimer *timer = new QTimer;
    QObject::connect(timer,SIGNAL(timeout()),rect,SLOT(spawn()));
    timer->start(2000);

    return a.exec();
}
