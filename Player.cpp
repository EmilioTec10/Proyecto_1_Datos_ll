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

        qDebug() << blue_Enemy->token;
        qDebug() << red_Enemy->token;

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
       qDebug() << blue_Enemy->token;

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

void Player::conect()
{
    spawn_enemies(enemies);
}

void Player::connector()
{
    spawn_hard_enemies(enemies);
}