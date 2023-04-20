//
// Created by emmanuel on 07/04/23.
//

#include <QLabel>
#include "Raged_Powers_Window.h"
#include "Normal_Game.h"
#include "Hard_Game.h"
#include "Dificulties_Window.h"
#include <QGraphicsProxyWidget>
#include <QPushButton>
#include <string>

void Raged_Powers_Window::easy(bool Speed, bool Freeze, bool Bullet, bool Slow)
{

    Normal_Game * easy = new  Normal_Game(800, 200, 1, 8,Speed,Freeze,Bullet,Slow);
    easy->show();
    this->close();
}

void Raged_Powers_Window::normal(bool Speed, bool Freeze, bool Bullet, bool Slow)
{
    Normal_Game * normal = new Normal_Game(1000, 150, 2, 5,Speed,Freeze,Bullet,Slow);
    normal->show();
    this->close();
}

void Raged_Powers_Window::hard(bool Speed, bool Freeze, bool Bullet, bool Slow)
{
    Hard_Game * hard = new Hard_Game(1000, 120, 2, 3,Speed,Freeze,Bullet,Slow);
    hard->show();
    this->close();
}
void Raged_Powers_Window::Chooser1(){

    if(difi == "easy"){
        easy(true,false,true,false);
    }
    if(difi == "normal"){
        normal(true,false,true,false);
    }
    if(difi == "hard"){
        hard(true,false,true,false);
    }
}
void Raged_Powers_Window::Chooser2(){

    if(difi == "easy"){
        easy(false,true,false,true);
    }
    if(difi == "normal"){
        normal(false,true,false,true);
    }
    if(difi == "hard"){
        hard(false,true,false,true);
    }
}
void Raged_Powers_Window::Chooser3(){

    if(difi == "easy"){
        easy(false,false,true,true);
    }
    if(difi == "normal"){
        normal(false,false,true,true);
    }
    if(difi == "hard"){
        hard(false,false,true,true);
    }
}
void Raged_Powers_Window::Chooser4(){

    if(difi == "easy"){
        easy(true,true,false,false);
    }
    if(difi == "normal"){
        normal(true,true,false,false);
    }
    if(difi == "hard"){
        hard(true,true,false,false);
    }
}
Raged_Powers_Window::Raged_Powers_Window( std::string value, QWidget *parent)
{
    difi= value;
    //Creation of the scene
    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    scene->setBackgroundBrush(QBrush(QImage("/home/emmanuel/CLionProjects/Proyecto_1_Datos_ll/Battlespace/battlespace3.jpg")));

    //Creation and configuration of the title
    QLabel *label = new QLabel("BattleSpace");
    QGraphicsProxyWidget *proxy_label = new QGraphicsProxyWidget(); //Widget that makes posible to use a QLabel in a QGraphicsscene
    proxy_label->setWidget(label);
    QFont font("Arial", 20, QFont::Helvetica);
    label->setStyleSheet("background-color: transparent; color: #ffffff;");
    label->setFont(font);
    scene->addItem(proxy_label);
    proxy_label->setPos(330, 20);

    //Creation and configuration of easy mode button
    QPushButton * Frenzied_Bullet = new QPushButton("Frenzied Bullet");
    Frenzied_Bullet->setGeometry(0,0,170,50);
    QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget(); //Widget that makes posible to use a QPushButton in a QGraphicsscene
    proxy->setWidget(Frenzied_Bullet);
    scene->addItem(proxy);
    proxy->setPos(320,150);
    connect(Frenzied_Bullet, &QPushButton::released, this, &Raged_Powers_Window::Chooser1); //Method that will activated when the button is released

    //Creaction and configuration of normal mode button
    QPushButton * Freezer = new QPushButton("Freezer");
    Freezer->setGeometry(0,0,170,50);
    QGraphicsProxyWidget *proxy_normal = new QGraphicsProxyWidget(); //Widget that makes posible to use a QPushButton in a QGraphicsscene
    proxy_normal->setWidget(Freezer);
    scene->addItem(proxy_normal);
    proxy_normal->setPos(320,240);
    connect(Freezer, &QPushButton::released, this, &Raged_Powers_Window::Chooser2); //Method that will activated when the button is released

    //Creaction and configuration of hard mode button
    QPushButton * Slower = new QPushButton("Slower");
    Slower->setGeometry(0,0,170,50);
    QGraphicsProxyWidget *proxy_hard = new QGraphicsProxyWidget(); //Widget that makes posible to use a QPushButton in a QGraphicsscene
    proxy_hard->setWidget(Slower);
    scene->addItem(proxy_hard);
    proxy_hard->setPos(320,330);
    connect(Slower, &QPushButton::released, this, &Raged_Powers_Window::Chooser3); //Method that will activated when the button is released
    //Creaction and configuration of hard mode button
    QPushButton * Lightning_Shot = new QPushButton("Lightning Shot");
    Lightning_Shot->setGeometry(0,0,170,50);
    QGraphicsProxyWidget *proxy_hardd = new QGraphicsProxyWidget(); //Widget that makes posible to use a QPushButton in a QGraphicsscene
    proxy_hardd->setWidget(Lightning_Shot);
    scene->addItem(proxy_hardd);
    proxy_hardd->setPos(320,420);
    connect(Lightning_Shot, &QPushButton::released, this, &Raged_Powers_Window::Chooser4); //Method that will activated when the button is released

    //Configuration of the scene
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    show();
}