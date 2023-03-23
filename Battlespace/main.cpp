#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QTimer>
#include "Player.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Escena
    QGraphicsScene *scene = new QGraphicsScene();
    int width = 800;
    int height = 600;

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
    view->setFixedSize(width,height);
    scene->setSceneRect(0,0,width,height);

    player->setPos(0,150);
    int bullet_speed = 1000;

    QTimer *timer = new QTimer;
    QObject::connect(timer,SIGNAL(timeout()),player,SLOT(bullets()));
    timer->start(bullet_speed);

    return a.exec();
}
