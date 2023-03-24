#include "Dificulties_Window.h"
#include "Easy_game.h"
#include "Normal_Game.h"
#include "Hard_Game.h"
#include <QPushButton>
#include <QLabel>
#include <QGraphicsProxyWidget>
#include <QRectF>

void Dificulties::easy()
{
    Easy_game * easy = new Easy_game();
    easy->show();
    this->close();
}

void Dificulties::normal()
{
    Normal_Game * normal = new Normal_Game();
    normal->show();
    this->close();
}

void Dificulties::hard()
{
    Hard_Game * hard = new Hard_Game();
    hard->show();
    this->close();
}


Dificulties::Dificulties(QWidget *parent)
{
    //Creation of the scene
    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    int width = 800;
    int height = 600;

    //Creation and configuration of the title
    QLabel *label = new QLabel("BattleSpace");
    QGraphicsProxyWidget *proxy_label = new QGraphicsProxyWidget();
    proxy_label->setWidget(label);
    QFont font("Arial", 20, QFont::Helvetica);
    label->setFont(font);
    scene->addItem(proxy_label);
    proxy_label->setPos(330, 20);

    //Creaction and configuration of easy mode button
    QPushButton * easy_mode = new QPushButton("Easy");
    easy_mode->setGeometry(0,0,170,50);
    QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget();
    proxy->setWidget(easy_mode);
    scene->addItem(proxy);
    proxy->setPos(320,150);
    connect(easy_mode, &QPushButton::released, this, &Dificulties::easy);

    //Creaction and configuration of normal mode button
    QPushButton * normal_mode = new QPushButton("Normal");
    normal_mode->setGeometry(0,0,170,50);
    QGraphicsProxyWidget *proxy_normal = new QGraphicsProxyWidget();
    proxy_normal->setWidget(normal_mode);
    scene->addItem(proxy_normal);
    proxy_normal->setPos(320,240);
    connect(normal_mode, &QPushButton::released, this, &Dificulties::normal);

    //Creaction and configuration of hard mode button
    QPushButton * hard_mode = new QPushButton("Hard");
    hard_mode->setGeometry(0,0,170,50);
    QGraphicsProxyWidget *proxy_hard = new QGraphicsProxyWidget();
    proxy_hard->setWidget(hard_mode);
    scene->addItem(proxy_hard);
    proxy_hard->setPos(320,330);
    connect(hard_mode, &QPushButton::released, this, &Dificulties::hard);

    //Configuration of the scene
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    show();
}
