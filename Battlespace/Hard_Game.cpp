#include "Hard_Game.h"
#include "Red_Enemy_Hard.h"
#include "Blue_Enemy_Hard.h"
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
#include <QtWidgets>
#include <functional>
#include <iostream>

/**
 * @brief Hard_Game::Hard_Game Constructor que inicia la ventana del juego dificil
 * @param bullet_speed Velocidad de las balas al inico del juego
 * @param bullets Cantidad de balas al inicio del juego
 * @param ships_number Cantidad de naves enemigas al inicio del juego
 * @param health Cantidad de vidas al inicio del juego
 * @param parent Widget que hace que la ventana pueda tener objetos
 */
Hard_Game::Hard_Game(int bullet_speed,int bullets, int ships_number, int health, QWidget * parent){

    //Creation and configuration of the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    scene->setBackgroundBrush(QBrush(QImage(":/Images/background.jpg")));
    QFont font("Arial", 15, QFont::Helvetica);

    //Declaration of the private variables
    this->bullets_speed = bullet_speed;
    this->bullets_number = bullets;
    this->health_number = health;

    //Number of bullets label
    bullets_label = new QGraphicsTextItem("Bullets: " + QString::number(bullets_number));
    bullets_label->setFont(font);
    bullets_label->setDefaultTextColor(Qt::red);

    //Bullet collector label
    bullet_collector = new QGraphicsTextItem("Bullet Collector: " + QString::number(collector->size));
    bullet_collector->setFont(font);
    bullet_collector->setDefaultTextColor(Qt::red);

    //Bullets speed label
    bullets_speed_label = new QGraphicsTextItem("Bullets Speed: " + QString::number(bullets_speed));
    bullets_speed_label->setFont(font);
    bullets_speed_label->setDefaultTextColor(Qt::red);

    //Health Label
    health_label = new QGraphicsTextItem("Health: " + QString::number(health));
    health_label->setFont(font);
    health_label->setDefaultTextColor(Qt::red);

    //Fase Label
    fase_label = new QGraphicsTextItem("Fase: " + QString::number(fase_number));
    fase_label->setFont(font);
    fase_label->setDefaultTextColor(Qt::red);

    //Wave Label
    wave_label = new QGraphicsTextItem("Wave: " + QString::number(wave_number));
    wave_label->setFont(font);
    wave_label->setDefaultTextColor(Qt::red);

    //Creation of the line that detects collitions of the enemies
    line = new QGraphicsLineItem(10, 10, 10, 600);
    scene->addItem(line);

    //Creation of the player
    player = new Player(bullets_number);
    player->setPixmap(QPixmap(":/Images/player.png"));

    //Add of all the items in the scene
    scene->addItem(player);
    scene->addItem(bullets_label);
    scene->addItem(bullet_collector);
    scene->addItem(bullets_speed_label);
    scene->addItem(health_label);
    scene->addItem(wave_label);
    scene->addItem(fase_label);

    //Set positions of the items in the scene
    bullet_collector->setPos(0,20);
    bullets_speed_label->setPos(0,40);
    health_label->setPos(0,60);
    wave_label->setPos(700,20);
    fase_label->setPos(700,0);

    //Make the player the focus of the view
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    player->setPos(0,150);
    player->set_enemies(ships_number);
    player->setCollector(collector);
    player->set_CollectorLabel(bullet_collector);

    //Spawn enemies at the beginning
    player->spawn_hard_enemies(ships_number, scene);

    //Configurations of the scene
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    //Timer of the bullets
    timer_bullets = new QTimer;
    QObject::connect(timer_bullets,SIGNAL(timeout()),player,SLOT(bullets()));
    timer_bullets->start(bullet_speed);

    //Timer to increse the waves
    wave_timer = new QTimer;
    QObject::connect(wave_timer,SIGNAL(timeout()),this,SLOT(increase_wave()));
    wave_timer->start();
    wave_timer->setInterval((10000));

    //Timer to increse the fase
    fase_timer = new QTimer;
    QObject::connect(fase_timer,SIGNAL(timeout()),this,SLOT(increase_fase()));
    fase_timer->start(50000);

    //Timer to spawn enemies recursively
    timer_enemies = new QTimer;
    QObject::connect(timer_enemies,SIGNAL(timeout()),player,SLOT(connector()));
    timer_enemies->start(10000);

    //Timer to decrese the bullets label
    QObject::connect(timer_decrease_bullets,SIGNAL(timeout()),this,SLOT(decrease_bullets()));
    timer_decrease_bullets->start(bullet_speed);

    //Timer to check the Health of the player
    check = new QTimer;
    QObject::connect(check,SIGNAL(timeout()),this,SLOT(check_health()));
    check->start(50);

    show();
}

/**
 * @brief Hard_Game::keyPressEvent Funcion que recibe los eventos de el teclado y aplica funciones
 * @param event event recibido por el teclado
 */
void Hard_Game::keyPressEvent(QKeyEvent *event)
{

    if (event->key() == Qt::Key_Up){
        if (player->y() > 0){ // Conditon that makes the player only move in the window
            player->setPos(player->x(),player->y()-10);
        }
        else{
            return;
        }
    }
    else if (event->key() == Qt::Key_Down){
        if (player->y() < 500){ // Conditon that makes the player only move in the window
            player->setPos(player->x(),player->y() + 10);
        }
        else{
            return;
        }
    }
    else if (event->key() == Qt::Key_Q){
        if (bullets_speed < 1200){ //Condition that makes that the bullets don't create for more than 1,2 seconds

            bullets_speed += 100;

            //Set the timers and labels with the new velocity
            timer_bullets->setInterval(bullets_speed + 10);
            change_speed_bullets();
            timer_decrease_bullets->setInterval(bullets_speed);
        }
        else{
            return;
        }
    }
    else if (event->key() == Qt::Key_W){
        if (bullets_speed > 200){ //Condition that makes that the bullets don't create for less than 0,200 seconds

            bullets_speed -= 100;

            //Set the timers and labels with the new velocity
            timer_bullets->setInterval(bullets_speed + 10);
            change_speed_bullets();
            timer_decrease_bullets->setInterval(bullets_speed);
        }
        else{
            return;
        }
    }
}

/**
 * @brief Hard_Game::decrease_bullets Disminuye el contador de balas del label en la ventana
 */
void Hard_Game::decrease_bullets()
{
    if (bullets_number == 0){
        timer_decrease_bullets->stop();
    }
    else{
        bullets_number--;
        bullets_label->setPlainText("Bullets: " + QString::number(bullets_number));
    }
}

/**
 * @brief Hard_Game::decrease_health Disminuye la vida del jugador
 */
void Hard_Game::decrease_health()
{
    if (health_number == 0){
        return;
    }
    else{
        health_number--;
        health_label->setPlainText("Health: " + QString::number(health_number));
    }
}

/**
 * @brief Hard_Game::check_health Revisa si los enemigos llegaron al final para quitar una vida y en caso de llegar a 0 se abre la ventana de perdiste
 */
void Hard_Game::check_health()
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
            if (typeid(*(colliding_items[i])) == typeid(Red_Enemy_Hard)){ //Checks if the red enemy is colliding with the line
                Red_Enemy_Hard *red_ne =  qgraphicsitem_cast<Red_Enemy_Hard *>(colliding_items[i]);
                //player->enemies_list->printList();
                player->enemies_list->deleteNode(red_ne);
                qDebug() << "se ha eliminado un enemigo rojo";
                //qDebug() << "";
                std::cout << "[ ";
                player->enemies_list->printList();
                std::cout << " ]" << std::endl;
                decrease_health();
            }
            else if (typeid(*(colliding_items[i])) == typeid(Blue_Enemy_Hard)){ //Checks if the blue enemy is colliding with the line
                Blue_Enemy_Hard *blue_ne =  qgraphicsitem_cast<Blue_Enemy_Hard *>(colliding_items[i]);
                //player->enemies_list->printList();
                player->enemies_list->deleteNode(blue_ne);
                qDebug() << "se ha eliminado un enemigo azul";
                //qDebug() << "";
                std::cout << "[ ";
                player->enemies_list->printList();
                std::cout << " ]" << std::endl;
                decrease_health();
            }
        }
    }
}

/**
 * @brief Hard_Game::increase_wave Aumenta la oleada del juego
 */
void Hard_Game::increase_wave()
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

/**
 * @brief Hard_Game::increase_fase Aumenta la fase y revisa se gano el juego
 */
void Hard_Game::increase_fase()
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
    }
}

/**
 * @brief Hard_Game::change_speed_bullets Cambia la velocidad de las balas en el label
 */
void Hard_Game::change_speed_bullets()
{
    bullets_speed_label->setPlainText("Bullets Speed: " + QString::number(bullets_speed));
}


