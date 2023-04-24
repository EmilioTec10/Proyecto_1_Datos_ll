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


/**
 * @brief Player::Player Constructor que crea al jugador en la pantalla de juego
 * @param bullets_number Cantidad de balas del jugador
 */
Player::Player(int bullets_number)
{
    this->bullets_number = bullets_number;
}

/**
 * @brief Player::bullets Funcion que usa las balas en el juego y ademas que usa el collector una vez se hayan acabado las balas
 */
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
int waves_index_recursive = 0;

/**
 * @brief Player::spawn_enemies Metodo que crea a la oleada cada vez que el timer se termine
 * @param enemies Cantidad de enemigos
 */
void Player::spawn_enemies(int enemies)
{
    waves_info_size = 4;

    for (int i = 0; i < enemies; i++){
        Red_Enemy *red_Enemy = new Red_Enemy();
        red_Enemy->token = red_recursive;
        scene()->addItem(red_Enemy);
        red_Enemy->setEnemies_List(enemies_list);
        enemies_list->insertNode(red_Enemy, red_Enemy->token);
        waves_info[waves_index_recursive] = red_Enemy;
        Blue_Enemy *blue_Enemy = new Blue_Enemy();
        blue_Enemy->token = blue_recursive;
        scene()->addItem(blue_Enemy);
        blue_Enemy->setEnemies_List(enemies_list);
        enemies_list->insertNode(blue_Enemy, blue_Enemy->token);
        waves_info[waves_index_recursive + 1] = blue_Enemy;

        qDebug() << blue_Enemy->token;
        qDebug() << red_Enemy->token;

        waves_index_recursive = waves_index_recursive + 2;

        blue_recursive++;
        red_recursive++;
    }

}

int red_hard_recursive = 0;
int blue_hard_recursive = 0;

/**
 * @brief Player::spawn_enemies Metodo que crea a la oleada cada vez que el timer se termine
 * @param enemies Cantidad de enemigos
 */
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
int waves_index = 0;

/**
 * @brief Player::spawn_enemies Metodo que crea a la oleada al incio del juego
 * @param enemies Cantidad de enemigos
 */
void Player::spawn_enemies(int enemies, QGraphicsScene *scene)
{

    for (int i = 0; i < enemies; i++){
        Red_Enemy *red_Enemy = new Red_Enemy();
        red_Enemy->token = red;
        red_Enemy->setEnemies_List(enemies_list);
        enemies_list->insertNode(red_Enemy, red_Enemy->token);
        scene->addItem(red_Enemy);
        waves_info[waves_index] = red_Enemy;
        Blue_Enemy *blue_Enemy = new Blue_Enemy();
        blue_Enemy->token = blue;
        blue_Enemy->setEnemies_List(enemies_list);
        enemies_list->insertNode(blue_Enemy, blue_Enemy->token);
        scene->addItem(blue_Enemy);
        waves_info[waves_index + 1] = blue_Enemy;
        qDebug() << blue_Enemy->token;

        waves_index = waves_index + 2;

        red++;
        blue++;
    }


}

int red_hard = 0;
int blue_hard = 0;

/**
 * @brief Player::spawn_enemies Metodo que crea a la oleada al inicio del juego
 * @param enemies Cantidad de enemigos
 */
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

/**
 * @brief Player::set_enemies Metodo que define la cantidad de enemigos en esta clase
 * @param enemies cantidad de enemigos de la otra clase
 */
void Player::set_enemies(int enemies)
{
    this->enemies = enemies;
}

/**
 * @brief Player::setCollector Metodo que define el collector en esta clase
 * @param collector collector de la otra clase
 */
void Player::setCollector(Collector *collector)
{
    this->collector = collector;
}

/**
 * @brief Player::set_CollectorLabel Metodo que define la etiqueta de texto en esta clase
 * @param bullet_collector Etiqueta de texto en esta clase
 */
void Player::set_CollectorLabel(QGraphicsTextItem *bullet_collector)
{
    this->bullet_collector = bullet_collector;
}

/**
 * @brief Player::removeEnemy metodo que quita el enemigo de el arreglo
 */
void Player::removeEnemy()
{
    delete waves_info[0];
    for (int i = 0; i < 4 - 1; i++) {
        waves_info[i] = waves_info[i + 1];
    }
    waves_info_size--;
}

/**
 * @brief Player::print_Wave_info Metodo que imprime la informacion de las oleadas
 */
void Player::print_Wave_info()
{
    for (int i = 0; i < waves_info_size; ++i) {
        std::cout << waves_info[i] << std::endl;
    }
}

/**
 * @brief Player::conect Metodo que llama a el metodo que generar las oleadas con el fin de que se puede usar en un timer
 */
void Player::conect()
{
    spawn_enemies(enemies);
}

/**
 * @brief Player::conect Metodo que llama a el metodo que generar las oleadas en el modo dificil con el fin de que se puede usar en un timer
 */
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

    char buffer[5];

    ssize_t n = read(fd, buffer, sizeof(buffer));
    //std::cout <<  letra << std::endl;
    close(fd);
    data12 = buffer[0];
    data21 = buffer[1];


}