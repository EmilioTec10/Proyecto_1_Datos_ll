#include "Player.h"
#include <QKeyEvent>
#include <QGraphicsScene>
#include "Bullet.h"
#include "Red_Enemy.h"
#include "Blue_Enemy.h"
#include "Blue_Enemy_Hard.h"
#include "Red_Enemy_Hard.h"
#include <QTimer>
#include <QObject>
#include <QDebug>
#include "SerialComm.h"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>


Player::Player(int bullets_number)
{
    this->bullets_number = bullets_number;
}

void Player::bullets()
{

    if (bullets_number == 0){
        if (collector->size != 0){
            collector->useBullet(scene(), x(), y());
            bullet_collector->setPlainText("Bullet Collector: " + QString::number(collector->size));
        }
        else{
            return;
        }
    }
    else{
        Bullet *bullet = new Bullet();
        bullet->setCollector(collector);
        bullet->set_CollectorLabel(bullet_collector);
        bullet->setPos(x()+110,y()+35);
        scene()->addItem(bullet);
        bullets_number--;
    }

}
int blue_recursive = 1;
int red_recursive = 1;
void Player::spawn_enemies(int enemies)
{
    for (int i = 0; i < enemies; i++){
        Red_Enemy *red_Enemy = new Red_Enemy();
        red_Enemy->token = red_recursive;
        scene()->addItem(red_Enemy);
        red_Enemy->setEnemies_List(enemies_list);
        enemies_list->insertNode(red_Enemy, red_Enemy->token);
        Blue_Enemy *blue_Enemy = new Blue_Enemy();
        blue_Enemy->token = blue_recursive;
        scene()->addItem(blue_Enemy);
        blue_Enemy->setEnemies_List(enemies_list);
        enemies_list->insertNode(blue_Enemy, blue_Enemy->token);
        blue_recursive++;
        red_recursive++;
    }

}

int red_hard_recursive = 0;
int blue_hard_recursive = 0;

void Player::spawn_hard_enemies(int enemies)
{
    for (int i = 0; i < enemies; i++){
        Blue_Enemy_Hard *blue_Enemy = new Blue_Enemy_Hard();
        blue_Enemy->token = blue_hard_recursive;
        scene()->addItem(blue_Enemy);
        blue_Enemy->setEnemies_List(enemies_list);
        enemies_list->insertNode(blue_Enemy, blue_Enemy->token);

        blue_hard_recursive++;
    }
    Red_Enemy_Hard *red_Enemy = new Red_Enemy_Hard();
    red_Enemy->token = red_hard_recursive;
    scene()->addItem(red_Enemy);
    red_Enemy->setEnemies_List(enemies_list);
    enemies_list->insertNode(red_Enemy, red_Enemy->token);

    red_hard_recursive++;

}

int red = 0;
int blue = 0;

void Player::spawn_enemies(int enemies, QGraphicsScene *scene)
{
    for (int i = 0; i < enemies; i++){
        Red_Enemy *red_Enemy = new Red_Enemy();
        red_Enemy->token = red;
        red_Enemy->setEnemies_List(enemies_list);
        enemies_list->insertNode(red_Enemy, red_Enemy->token);
        scene->addItem(red_Enemy);
        Blue_Enemy *blue_Enemy = new Blue_Enemy();
        blue_Enemy->token = blue;
        blue_Enemy->setEnemies_List(enemies_list);
        enemies_list->insertNode(blue_Enemy, blue_Enemy->token);
        scene->addItem(blue_Enemy);


        red++;
        blue++;
    }

}

int red_hard = 0;
int blue_hard = 0;

void Player::spawn_hard_enemies(int enemies, QGraphicsScene *scene)
{
    for (int i = 0; i < enemies; i++){

        Blue_Enemy_Hard *blue_Enemy = new Blue_Enemy_Hard();
        blue_Enemy->token = blue_hard;
        blue_Enemy->setEnemies_List(enemies_list);
        enemies_list->insertNode(blue_Enemy, blue_Enemy->token);
        scene->addItem(blue_Enemy);

        blue_Enemy->token = blue_hard;

        blue_hard++;
    }
    Red_Enemy_Hard *red_Enemy = new Red_Enemy_Hard();
    red_Enemy->token = red_hard;
    scene->addItem(red_Enemy);
    red_Enemy->setEnemies_List(enemies_list);
    enemies_list->insertNode(red_Enemy, red_Enemy->token);

    red_hard++;
}

void Player::set_enemies(int enemies)
{
    this->enemies = enemies;
}

void Player::setCollector(Collector *collector)
{
    this->collector = collector;
}

void Player::set_CollectorLabel(QGraphicsTextItem *bullet_collector)
{
    this->bullet_collector = bullet_collector;
}


void Player::conect()
{
    spawn_enemies(enemies);
}

void Player::connector()
{
    spawn_hard_enemies(enemies);
}
void Player::startSerialConnection() {

    const char *dispositivo_serial = "/dev/ttyUSB0"; // Cambiar según el dispositivo serial en uso
    int fd = open(dispositivo_serial, O_RDWR | O_NOCTTY);

    struct termios opciones;
    tcgetattr(fd, &opciones);
    opciones.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
    opciones.c_iflag = IGNPAR;
    opciones.c_oflag = 0;
    opciones.c_lflag = 0;
    tcsetattr(fd, TCSANOW, &opciones);

    char buffer[1];

    ssize_t n = read(fd, buffer, sizeof(buffer));
    std::string letra(buffer, n);
    std::cout <<  letra << std::endl;
    close(fd);
    data= letra;


}