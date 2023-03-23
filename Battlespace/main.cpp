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
    player->setPixmap(QPixmap(":/Images/nave (1).png"));

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

    //Timer de las balas
    QTimer *timer_bullets = new QTimer;
    QObject::connect(timer_bullets,SIGNAL(timeout()),player,SLOT(bullets()));
    timer_bullets->start(bullet_speed);

    //Timer de los enemigos
    QTimer *timer_enemies = new QTimer;
    QObject::connect(timer_enemies,SIGNAL(timeout()),player,SLOT(spawn_enemies()));
    timer_enemies->start(2000);


    return a.exec();
}
