#include "Normal_Game.h"
#include <QImage>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QDebug>

Normal_Game::Normal_Game(QWidget *parent){
    //Escena
    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    scene->setBackgroundBrush(QBrush(QImage(":/Images/space_background (1).png")));

    int width = 800;
    int height = 600;
    int bullet_speed = 800;

    //Item en la escena
    Player *player = new Player(bullets_number);
    player->setPixmap(QPixmap(":/Images/nave (1).png"));
    QFont font("Arial", 15, QFont::Helvetica);
    bullets_label->setFont(font);
    bullets_label->setDefaultTextColor(Qt::red);

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

    scene->addItem(bullets_label);

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

    QObject::connect(timer_bulletss,SIGNAL(timeout()),this,SLOT(decrease()));
    timer_bulletss->start(bullet_speed);

    show();
}
void Normal_Game::decrease()
{
    if (bullets_number == 0){
        timer_bulletss->stop();
    }
    else{
        bullets_number--;
        bullets_label->setPlainText("Bullets: " + QString::number(bullets_number));
    }
}
