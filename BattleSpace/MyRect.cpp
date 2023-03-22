#include "MyRect.h"
#include "Bullet.h"
#include "Enemy.h"
#include <QKeyEvent>
#include <QGraphicsScene>

void MyRect::keyPressEvent(QKeyEvent *event){
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
    else if (event->key() == Qt::Key_Space){
        Bullet *bullet = new Bullet();
        bullet->setPos(x()+100,y()+50);
        scene()->addItem(bullet);
    }
}
void MyRect::spawn(){
    Enemy *enemy = new Enemy();
    scene()->addItem(enemy);
}
