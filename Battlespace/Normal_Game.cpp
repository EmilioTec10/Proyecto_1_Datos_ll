#include "Normal_Game.h"
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>

Normal_Game::Normal_Game(QWidget *parent){
    //Escena
    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
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
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    player->setPos(0,150);
    int bullet_speed = 800;

    //Timer de las balas
    QTimer *timer_bullets = new QTimer;
    QObject::connect(timer_bullets,SIGNAL(timeout()),player,SLOT(bullets()));
    timer_bullets->start(bullet_speed);

    //Timer de los enemigos
    QTimer *timer_blue_enemies = new QTimer;
    QObject::connect(timer_blue_enemies,SIGNAL(timeout()),player,SLOT(spawn_Blue_enemies()));
    timer_blue_enemies->start(2000);

    //Timer de los enemigos
    QTimer *timer_red_enemies = new QTimer;
    QObject::connect(timer_red_enemies,SIGNAL(timeout()),player,SLOT(spawn_Red_enemies()));
    timer_red_enemies->start(3000);

    show();
}
