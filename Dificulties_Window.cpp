#include "Dificulties_Window.h"
#include "Normal_Game.h"
#include "Hard_Game.h"
#include "Raged_Powers_Window.h"
#include <QPushButton>
#include <QLabel>
#include <QGraphicsProxyWidget>
#include <QRectF>
/**
 * @brief Dificulties::easy Funcion que incia el juego en dificultad facil
 */
void Dificulties::easy()
{
    Raged_Powers_Window* easy = new  Raged_Powers_Window("easy");
    //Normal_Game * easy = new  Normal_Game(800, 200, 1, 8);
    easy->show();
    difi = "easy";
    this->close();

}

/**
 * @brief Dificulties::easy Funcion que incia el juego en dificultad normal
 */
void Dificulties::normal()
{
    Raged_Powers_Window* normal = new  Raged_Powers_Window("normal");
    //Normal_Game * normal = new Normal_Game(1000, 150, 2, 5);
    normal->show();
    difi = "normal";
    this->close();

}

/**
 * @brief Dificulties::easy Funcion que incia el juego en dificultad dificil
 */
void Dificulties::hard()
{
    Raged_Powers_Window* hard = new  Raged_Powers_Window("hard");
    //Hard_Game * hard = new Hard_Game(1000, 120, 2, 3);
    hard->show();
    difi = "hard";
    this->close();
}
/**
 * @brief Dificulties::Dificulties Constructor de la clase de la ventana de las dificultadoes
 * @param parent WIdget que hace posible que se incie la ventana
 */
Dificulties::Dificulties(QWidget *parent)
{

    //Creation of the scene
    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    scene->setBackgroundBrush(QBrush(QImage("/home/emmanuel/CLionProjects/Proyecto_1_Datos_ll/Battlespace/mainwdw_background.png")));

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
    QPushButton * easy_mode = new QPushButton("Easy");
    easy_mode->setGeometry(0,0,170,50);
    QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget(); //Widget that makes posible to use a QPushButton in a QGraphicsscene
    proxy->setWidget(easy_mode);
    scene->addItem(proxy);
    proxy->setPos(320,150);
    connect(easy_mode, &QPushButton::released, this, &Dificulties::easy); //Method that will activated when the button is released

    //Creaction and configuration of normal mode button
    QPushButton * normal_mode = new QPushButton("Normal");
    normal_mode->setGeometry(0,0,170,50);
    QGraphicsProxyWidget *proxy_normal = new QGraphicsProxyWidget(); //Widget that makes posible to use a QPushButton in a QGraphicsscene
    proxy_normal->setWidget(normal_mode);
    scene->addItem(proxy_normal);
    proxy_normal->setPos(320,240);
    connect(normal_mode, &QPushButton::released, this, &Dificulties::normal); //Method that will activated when the button is released

    //Creaction and configuration of hard mode button
    QPushButton * hard_mode = new QPushButton("Hard");
    hard_mode->setGeometry(0,0,170,50);
    QGraphicsProxyWidget *proxy_hard = new QGraphicsProxyWidget(); //Widget that makes posible to use a QPushButton in a QGraphicsscene
    proxy_hard->setWidget(hard_mode);
    scene->addItem(proxy_hard);
    proxy_hard->setPos(320,330);
    connect(hard_mode, &QPushButton::released, this, &Dificulties::hard); //Method that will activated when the button is released

    //Configuration of the scene
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    show();
}
