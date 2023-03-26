#include "Normal_Game.h"
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QImage>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QFont>
#include <QDebug>

Normal_Game::Normal_Game(int bullet_speed, int bullets, int ships_number, int health, QWidget *parent){
    //Escena
    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    scene->setBackgroundBrush(QBrush(QImage(":/Images/space_background (1).png")));
    QFont font("Arial", 15, QFont::Helvetica);

    this->bullets_number = bullets;
    this->health_number = health;

    bullets_label = new QGraphicsTextItem("Bullets: " + QString::number(bullets_number));
    bullets_label->setFont(font);
    bullets_label->setDefaultTextColor(Qt::red);

    //Item en la escena
    Player *player = new Player(bullets_number);
    player->setPixmap(QPixmap(":/Images/nave (1).png"));

    health_label = new QGraphicsTextItem("Health: " + QString::number(health));
    health_label->setFont(font);
    health_label->setDefaultTextColor(Qt::red);

    QPushButton * normal_ = new QPushButton("nose");
    normal_->setGeometry(0,0,50,50);
    QGraphicsProxyWidget *proxy_norma = new QGraphicsProxyWidget();
    proxy_norma->setWidget(normal_);
    scene->addItem(proxy_norma);
    proxy_norma->setPos(750,550);
    connect(normal_, &QPushButton::released, this, &Normal_Game::decrease_health);

    //Agregado de el item a la escena
    scene->addItem(player);
    scene->addItem(bullets_label);
    scene->addItem(health_label);
    health_label->setPos(0,20);

    //Hacer rectangulo focusiable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    //Mostrar scena
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    player->setPos(0,150);

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

    QObject::connect(timer_bulletss,SIGNAL(timeout()),this,SLOT(decrease_bullets()));
    timer_bulletss->start(bullet_speed);

    show();
}
void Normal_Game::decrease_bullets()
{
    if (bullets_number == 0){
        timer_bulletss->stop();
    }
    else{
        bullets_number--;
        bullets_label->setPlainText("Bullets: " + QString::number(bullets_number));
    }
}

void Normal_Game::decrease_health()
{
    if (health_number == 0){
        return;
    }
    else{
        health_number--;
        health_label->setPlainText("Health: " + QString::number(health_number));
    }
}
