#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include "Linked_List.h"
#include "Bullet_Collector.h"


class Player: public QObject ,public QGraphicsPixmapItem{
    Q_OBJECT
public:

    Player(int bullets_number);
    std::string data1;
    std::string data2;
    char data12;
    char data21;
    int bullets_number;
    int enemies_screen;
    const int MAX_BUFFER_SIZE = 255;
    void spawn_enemies(int enemies, QGraphicsScene *scene);
    void spawn_hard_enemies(int enemies, QGraphicsScene *scene);
    void set_enemies(int enemies);
    void setCollector(Collector *collector);
    void set_CollectorLabel(QGraphicsTextItem *bullet_collector);

    int fd;

    std::list<char> buffer;

    Linkedlist *enemies_list = new Linkedlist();

public slots:
    void startSerialConnection();
    void bullets();
    void spawn_hard_enemies(int enemies);
    void spawn_enemies(int enemies);
    void conect();
    void connector();
    void removeEnemy();
    void print_Wave_info();


private:
    int enemies;
    int waves_info_size = 4;
    Collector *collector;
    QGraphicsTextItem *bullet_collector;
    QGraphicsPixmapItem* waves_info[4];
    QGraphicsPixmapItem* waves_info_hard[3];
};
#endif // PLAYER_H
