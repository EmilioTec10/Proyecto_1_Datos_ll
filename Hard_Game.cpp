#include "Hard_Game.h"
#include "Red_Enemy_Hard.h"
#include "Blue_Enemy_Hard.h"
#include "Game_Over.h"
#include "Win_Window.h"
#include "XML_Reader.h"
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



Hard_Game::Hard_Game(int bullet_speed,int bullets, int ships_number, int health,bool Speed, bool Freeze, bool Bullet, bool Slow, QWidget * parent){

    //Creation and configuration of the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    scene->setBackgroundBrush(QBrush(QImage(":/Images/background.jpg")));
    QFont font("Arial", 15, QFont::Helvetica);

    //Declaration of the private variables
    this->bullets_speed = bullet_speed;
    this->bullets_number = bullets;
    this->health_number = health;
    Raged_Powers_Bullet_Speed =Speed;
    Raged_Powers_Bullet_Amount = Bullet;
    Raged_Powers_Enemy_Speed =Slow;
    Raged_Powers_Enemy_Freeze=Freeze;
    //Number of bullets label
    bullets_label = new QGraphicsTextItem("Bullets: " + QString::number(bullets_number));
    bullets_label->setFont(font);
    bullets_label->setDefaultTextColor(Qt::red);

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
    scene->addItem(bullets_speed_label);
    scene->addItem(health_label);
    scene->addItem(wave_label);
    scene->addItem(fase_label);

    //Set positions of the items in the scene
    bullets_speed_label->setPos(0,20);
    health_label->setPos(0,40);
    wave_label->setPos(700,20);
    fase_label->setPos(700,0);

    //Make the player the focus of the view
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    player->setPos(0,150);
    player->set_enemies(ships_number);

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

void Hard_Game::keyPressEvent(QKeyEvent *event)
{
    XML_Reader xml_reader;
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
    else if (event->key() == Qt::Key_P && Raged_Powers_Bullet_Speed ==true) {
        xml_reader.XML_Data_Finder("/home/emmanuel/CLionProjects/Proyecto_1_Datos_ll/Battlespace/Raged_Powers_XML.xml");

        bullets_speed = xml_reader.newest_data;
        timer_bullets->setInterval(bullets_speed + 10);
        change_speed_bullets();
        timer_decrease_bullets->setInterval(bullets_speed);
        QTimer *timer = new QTimer;
        connect(timer,SIGNAL(timeout()),this,SLOT(Back_to_past())); //conect method that repeats the method everytime it recives the signal
        timer->start(5000); //Signal every 50 miliseconds

    }
    else if (event->key() == Qt::Key_O && Raged_Powers_Bullet_Amount ==true) {
        xml_reader.XML_Data_Finder("/home/emmanuel/CLionProjects/Proyecto_1_Datos_ll/Battlespace/Raged_Powers_XML4.xml");
        bullets_number+=xml_reader.newest_data;
        bullets_label->setPlainText("Bullets: " + QString::number(bullets_number));


    }else if (event->key() == Qt::Key_P && Raged_Powers_Enemy_Speed ==true) {
        Raged_Powers_Enemy_Speed=false;
        xml_reader.Data_Changer("/home/emmanuel/CLionProjects/Proyecto_1_Datos_ll/Battlespace/Raged_Powers_XML2.xml","1");
        xml_reader.Data_Changer("/home/emmanuel/CLionProjects/Proyecto_1_Datos_ll/Battlespace/Raged_Powers_XML3.xml","2");
        QTimer *timer = new QTimer;
        connect(timer, SIGNAL(timeout()), this,SLOT(Back_to_past_2())); //conect method that repeats the method everytime it recives the signal
        timer->start(6000); //Signal every 50 miliseconds
    }
    else if (event->key() == Qt::Key_O && Raged_Powers_Enemy_Freeze ==true) {
        Raged_Powers_Enemy_Freeze=false;
        xml_reader.Data_Changer("/home/emmanuel/CLionProjects/Proyecto_1_Datos_ll/Battlespace/Raged_Powers_XML2.xml","0");
        xml_reader.Data_Changer("/home/emmanuel/CLionProjects/Proyecto_1_Datos_ll/Battlespace/Raged_Powers_XML3.xml","0");
        QTimer *timer = new QTimer;
        connect(timer, SIGNAL(timeout()), this,SLOT(Back_to_past_2())); //conect method that repeats the method everytime it recives the signal
        timer->start(7000); //Signal every 50 miliseconds
    }
}
void Hard_Game::Back_to_past(){

    bullets_speed = 500;
    timer_bullets->setInterval(bullets_speed + 10);
    change_speed_bullets();
    timer_decrease_bullets->setInterval(bullets_speed);
}
void Hard_Game::Back_to_past_2(){
    XML_Reader xml_reader;
    xml_reader.Data_Changer("/home/emmanuel/CLionProjects/Proyecto_1_Datos_ll/Battlespace/Raged_Powers_XML2.xml", "5");
    xml_reader.Data_Changer("/home/emmanuel/CLionProjects/Proyecto_1_Datos_ll/Battlespace/Raged_Powers_XML3.xml", "10");
}
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
            if (typeid(*(colliding_items[i])) == typeid(Red_Enemy_Hard) || typeid(*(colliding_items[i])) == typeid(Blue_Enemy_Hard)){ //Checks if the red or blue enemy is colliding with the line

                decrease_health();
            }
        }
    }
}

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

void Hard_Game::change_speed_bullets()
{
    bullets_speed_label->setPlainText("Bullets Speed: " + QString::number(bullets_speed));
}

