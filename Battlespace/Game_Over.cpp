#include "Game_Over.h"
#include "Dificulties_Window.h"
#include <QLabel>
#include <QGraphicsProxyWidget>
#include <QPushButton>

/**
 * @brief Game_Over::Game_Over Constructor de la ventana de perdiste
 * @param parent Widget que hace posible que la ventana se corra
 */
Game_Over::Game_Over(QWidget *parent)
{
    //Creation of the scene
    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    int width = 800;
    int height = 600;

    //Creation and configuration of the title
    QLabel *label = new QLabel("Game Over");
    QGraphicsProxyWidget *proxy_label = new QGraphicsProxyWidget(); //Widget that makes posible to use a QLabel in a QGraphicsscene
    proxy_label->setWidget(label);
    QFont font("Arial", 45, QFont::Helvetica);
    label->setFont(font);
    label->setStyleSheet("background-color: white");
    scene->addItem(proxy_label);
    proxy_label->setPos(250, 200);

    //Creation and configuration of normal mode button
    QPushButton * normal_mode = new QPushButton("Regresar a la pantalla inicial");
    normal_mode->setGeometry(0,0,210,70);
    QGraphicsProxyWidget *proxy_normal = new QGraphicsProxyWidget(); //Widget that makes posible to use a QPushButton in a QGraphicsscene
    proxy_normal->setWidget(normal_mode);
    scene->addItem(proxy_normal);
    proxy_normal->setPos(285,300);
    connect(normal_mode, &QPushButton::released, this, &Game_Over::main_menu); //Method that will activated when the button is released

    setScene(scene);

    show();
}

/**
 * @brief Game_Over::main_menu Funcion que al apretar el boton te devuelve a la ventana de dificultades
 *
 */
void Game_Over::main_menu()
{
    Dificulties *window = new Dificulties();
    window->show();
    this->close();
}
