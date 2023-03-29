#include "Normal_Game.h"
#include "Red_Enemy.h"
#include "Blue_Enemy.h"
#include "Game_Over.h"
#include "Win_Window.h"
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QImage>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QFont>
#include <QList>
#include <functional>

Normal_Game::Normal_Game(int bullet_speed, int bullets, int ships_number, int health, QWidget *parent){
    //Escena
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    scene->setBackgroundBrush(QBrush(QImage(":/Images/space_background (1).png")));
    QFont font("Arial", 15, QFont::Helvetica);

    this->bullets_speed = bullet_speed;
    this->bullets_number = bullets;
    this->health_number = health;

    bullets_label = new QGraphicsTextItem("Bullets: " + QString::number(bullets_number));
    bullets_label->setFont(font);
    bullets_label->setDefaultTextColor(Qt::red);

    fase_label = new QGraphicsTextItem("Fase: " + QString::number(fase_number));
    fase_label->setFont(font);
    fase_label->setDefaultTextColor(Qt::red);

    wave_label = new QGraphicsTextItem("Wave: " + QString::number(wave_number));
    wave_label->setFont(font);
    wave_label->setDefaultTextColor(Qt::red);

    line = new QGraphicsLineItem(10, 10, 10, 600);
    scene->addItem(line);

    //Item en la escena
    player = new Player(bullets_number);
    player->setPixmap(QPixmap(":/Images/nave (1).png"));

    health_label = new QGraphicsTextItem("Health: " + QString::number(health));
    health_label->setFont(font);
    health_label->setDefaultTextColor(Qt::red);

    //Agregado de el item a la escena
    scene->addItem(player);
    scene->addItem(bullets_label);
    scene->addItem(health_label);
    scene->addItem(wave_label);
    scene->addItem(fase_label);
    health_label->setPos(0,20);
    wave_label->setPos(700,20);
    fase_label->setPos(700,0);

    //Hacer rectangulo focusiable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    player->setPos(0,150);

    //Mostrar scena
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    //Timer de las balas
    timer_bullets = new QTimer;
    QObject::connect(timer_bullets,SIGNAL(timeout()),player,SLOT(bullets()));
    timer_bullets->start(bullet_speed);

    wave_timer = new QTimer;
    QObject::connect(wave_timer,SIGNAL(timeout()),this,SLOT(increase_wave()));
    wave_timer->start();
    wave_timer->setInterval((10000));

    player->spawn_enemies(ships_number, scene);

    timer_enemies = new QTimer;
    QObject::connect(timer_enemies,SIGNAL(timeout()),player,SLOT(conect()));
    timer_enemies->start(10000);


    fase_timer = new QTimer;
    QObject::connect(fase_timer,SIGNAL(timeout()),this,SLOT(increase_fase()));
    fase_timer->start(50000);

    //Timer de los enemigos
    /*
    QTimer *timer_blue_enemies = new QTimer;
    QObject::connect(timer_blue_enemies,SIGNAL(timeout()),player,SLOT(spawn_Blue_enemies()));
    timer_blue_enemies->start(2000);

    //Timer de los enemigos
    QTimer *timer_red_enemies = new QTimer;
    QObject::connect(timer_red_enemies,SIGNAL(timeout()),player,SLOT(spawn_Red_enemies()));
    timer_red_enemies->start(3000);
    */

    QObject::connect(timer_decrease_bullets,SIGNAL(timeout()),this,SLOT(decrease_bullets()));
    timer_decrease_bullets->start(bullet_speed);

    check = new QTimer;
    QObject::connect(check,SIGNAL(timeout()),this,SLOT(check_health()));
    check->start(50);

    show();
}

void Normal_Game::keyPressEvent(QKeyEvent *event)
{

    if (event->key() == Qt::Key_Up){
        if (player->y() > 0){
            player->setPos(player->x(),player->y()-10);
        }
    }
    else if (event->key() == Qt::Key_Down){
        if (player->y() < 500){
            player->setPos(player->x(),player->y() + 10);
        }
    }
    else if (event->key() == Qt::Key_Q){
        bullets_speed += 100;
        timer_bullets->setInterval(bullets_speed + 10);
        timer_decrease_bullets->setInterval(bullets_speed);
    }
    else if (event->key() == Qt::Key_W){
        bullets_speed -= 100;
        timer_bullets->setInterval(bullets_speed);
        timer_decrease_bullets->setInterval(bullets_speed);
    }
}
void Normal_Game::decrease_bullets()
{
    if (bullets_number == 0){
        timer_decrease_bullets->stop();
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

void Normal_Game::check_health()
{
    if (health_number == 0){
        check->stop();
        Game_Over *game_over = new Game_Over();
        game_over->show();
        this->close();
    }
    else{
        QList<QGraphicsItem *> colliding_items = line->collidingItems();
        for (int i = 0, n = colliding_items.size(); i < n; ++i){
            if (typeid(*(colliding_items[i])) == typeid(Red_Enemy) || typeid(*(colliding_items[i])) == typeid(Blue_Enemy)){

                decrease_health();
            }
        }
    }
}

void Normal_Game::increase_wave()
{
    if (wave_number == 5){
        wave_number = 1;
        wave_label->setPlainText("Wave: " + QString::number(wave_number));
    }
    else{
        wave_number++;
        wave_label->setPlainText("Wave: " + QString::number(wave_number));
    }
}

void Normal_Game::increase_fase()
{
    if (fase_number == 3){
        wave_timer->stop();
        fase_timer->stop();
        Win_Window *win_Window = new Win_Window();
        win_Window->show();
        this->close();

    }
    else{
        fase_number++;
        fase_label->setPlainText("Fase: " + QString::number(fase_number));
        //timer_enemies->stop();
    }
}
