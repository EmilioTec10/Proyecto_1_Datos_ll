#ifndef NORMAL_GAME_H
#define NORMAL_GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include "Player.h"

class Normal_Game: public QGraphicsView{
    Q_OBJECT
public:
    Normal_Game(int bullet_speed,int bullets, int ships_number, int health, QWidget * parent=0);

    QTimer *timer_bulletss = new QTimer;
    QTimer *timer_enemies;
    QTimer *wave_timer;
    QTimer *fase_timer;
    QTimer *check;

    QGraphicsTextItem *bullets_label;
    QGraphicsTextItem *health_label;
    QGraphicsTextItem *wave_label;
    QGraphicsTextItem *fase_label;
    QGraphicsLineItem *line;

    QGraphicsScene * scene;
    Player * player;
public slots:
    void decrease_bullets();
    void decrease_health();
    void check_health();
    void increase_wave();
    void increase_fase();
private:
    int width = 800;
    int height = 600;
    int bullets_number;
    int health_number;
    int fase_number = 1;
    int wave_number = 1;
};

#endif // NORMAL_GAME_H
