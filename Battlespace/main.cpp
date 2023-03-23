#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include "Player.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Escena
    QGraphicsScene *scene = new QGraphicsScene();

    //Item en la escena
    Player *player = new Player();
    player->setRect(0,0,100,100);

    //Agregado de el item a la escena
    scene->addItem(player);

    //Hacer rectangulo focusiable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    //Mostrar scena
    QGraphicsView *view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->show();

    return a.exec();
}
