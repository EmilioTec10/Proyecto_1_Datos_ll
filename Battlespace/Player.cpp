#include "Player.h"
#include <QKeyEvent>
#include <QGraphicsScene>
#include "Bullet.h"

void Player::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Up){
        if (pos().y() > 0){
            setPos(x(),y()-10);
        }
    }
    else if (event->key() == Qt::Key_Down){
        if (pos().y() < 400){
            setPos(x(),y()+10);
        }
    }
}

void Player::bullets()
{
    Bullet *bullet = new Bullet();
    bullet->setPos(x()+100,y()+50);
    scene()->addItem(bullet);

}
