#ifndef NORMAL_GAME_H
#define NORMAL_GAME_H
#include <QGuiApplication>
#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include "Player.h"
#include "Bullet_Collector.h"
#include "SerialComm.h"
#include <QGuiApplication>
#include <QPixmap>


class Normal_Game: public QGraphicsView{
Q_OBJECT


public:
    QObject *serialComm;

    Normal_Game(int bullet_speed,int bullets, int ships_number, int health,bool Speed, bool Freeze, bool Bullet, bool Slow, QWidget * parent=0);
    Normal_Game();
    void keyPressEvent(QKeyEvent *event);
    bool Raged_Powers_Bullet_Speed;
    bool Raged_Powers_Bullet_Amount;
    bool Raged_Powers_Enemy_Speed;
    bool Raged_Powers_Enemy_Freeze;
    void Serial_ON();

    void change_speed_bullets();
    int get_enemy_speed();
    //Timers of the game
    QTimer *timer_bullets;
    QTimer *timer_decrease_bullets = new QTimer;
    QTimer *timer_enemies;
    QTimer *wave_timer;
    QTimer *fase_timer;
    QTimer *wave_arduino_timer;
    QTimer *timer;
    QTimer *setBullets;
    QTimer *check;
    QTimer *check2;
    QTimer *check3;
    QTimer *check4;
    Collector *collector = new Collector();
    //Changable labels
    QGraphicsTextItem *bullets_label;
    QGraphicsTextItem *bullet_collector;
    QGraphicsTextItem *bullets_speed_label;
    QGraphicsTextItem *health_label;
    QGraphicsTextItem *wave_label;
    QGraphicsTextItem *fase_label;
    QGraphicsLineItem *line;
    bool serial;
    SerialComm *pichadeconexion = new SerialComm();

    //Items
    QGraphicsScene * scene;
    Player * player;



public slots:

    //Methods to change text in labels
    void decrease_bullets();
    void decrease_health();
    void check_health();
    void increase_wave();
    void increase_fase();
    void Back_to_past();
    void Back_to_past_2();
    void Aduino_Movement();
    void potenciometer();
    void enviar_Dato();
    void Wait();


private:

    //Main variables
    int width = 800;
    int height = 600;
    int fase_number = 1;
    int wave_number = 1;
    int bullets_speed;
    int bullets_number;
    int health_number;
    int enemy_speed;
    void Back_to_past(int &variable, int newValue, int delayInSeconds);



};

#endif // NORMAL_GAME_H