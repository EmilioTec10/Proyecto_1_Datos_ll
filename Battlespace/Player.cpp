#include "Player.h"
#include <QKeyEvent>
#include <QGraphicsScene>
#include "Bullet.h"
#include "Red_Enemy.h"
#include "Blue_Enemy.h"
#include "Blue_Enemy_Hard.h"
#include "Red_Enemy_Hard.h"
#include <QTimer>
#include <QDebug>
#include <QObject>

Player::Player(int bullets_number)
{
    this->bullets_number = bullets_number;
}

void Player::bullets()
{

    if (bullets_number == 0){
        return;
    }
    else{
        Bullet *bullet = new Bullet();
        bullet->setPos(x()+100,y()+20);
        scene()->addItem(bullet);
        bullets_number--;
    }

}

void Player::spawn_Blue_enemies(){
    Blue_Enemy *blue_Enemy = new Blue_Enemy();
    scene()->addItem(blue_Enemy);
}

void Player::spawn_Red_enemies()
{
    Red_Enemy *red_Enemy = new Red_Enemy();
    scene()->addItem(red_Enemy);
}

void Player::spawn_enemies(int enemies)
{
   for (int i = 0; i < enemies; i++){
       Red_Enemy *red_Enemy = new Red_Enemy();
       scene()->addItem(red_Enemy);
       Blue_Enemy *blue_Enemy = new Blue_Enemy();
       scene()->addItem(blue_Enemy);
   }

}

void Player::spawn_hard_enemies(int enemies)
{
   for (int i = 0; i < enemies; i++){
       Red_Enemy_Hard *red_Enemy = new Red_Enemy_Hard();
       scene()->addItem(red_Enemy);
       Blue_Enemy_Hard *blue_Enemy = new Blue_Enemy_Hard();
       scene()->addItem(blue_Enemy);
   }

}

void Player::spawn_enemies(int enemies, QGraphicsScene *scene)
{
   for (int i = 0; i < enemies; i++){
       Red_Enemy *red_Enemy = new Red_Enemy();
       scene->addItem(red_Enemy);
       Blue_Enemy *blue_Enemy = new Blue_Enemy();
       scene->addItem(blue_Enemy);
   }

}
void Player::spawn_hard_enemies(int enemies, QGraphicsScene *scene)
{
   for (int i = 0; i < enemies; i++){
       Red_Enemy_Hard *red_Enemy = new Red_Enemy_Hard();
       scene->addItem(red_Enemy);
       Blue_Enemy_Hard *blue_Enemy = new Blue_Enemy_Hard();
       scene->addItem(blue_Enemy);
   }

}

void Player::conect()
{
    spawn_enemies(2);
}

void Player::connector()
{
    spawn_hard_enemies(2);
}
