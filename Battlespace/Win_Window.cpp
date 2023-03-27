#include "Win_Window.h"
#include "Dificulties_Window.h"
#include <QLabel>
#include <QGraphicsProxyWidget>
#include <QPushButton>

Win_Window::Win_Window(QWidget *parent)
{
    //Creation of the scene
    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    int width = 800;
    int height = 600;

    //Creation and configuration of the title
    QLabel *label = new QLabel("You Win");
    QGraphicsProxyWidget *proxy_label = new QGraphicsProxyWidget();
    proxy_label->setWidget(label);
    QFont font("Arial", 45, QFont::Helvetica);
    label->setFont(font);
    label->setStyleSheet("background-color: white");
    scene->addItem(proxy_label);
    proxy_label->setPos(250, 200);

    //Creaction and configuration of normal mode button
    QPushButton * normal_mode = new QPushButton("Regresar a la pantalla inicial");
    normal_mode->setGeometry(0,0,210,70);
    QGraphicsProxyWidget *proxy_normal = new QGraphicsProxyWidget();
    proxy_normal->setWidget(normal_mode);
    scene->addItem(proxy_normal);
    proxy_normal->setPos(285,300);
    connect(normal_mode, &QPushButton::released, this, &Win_Window::main_menu);

    setScene(scene);

    show();
}

void Win_Window::main_menu()
{
    Dificulties *window = new Dificulties();
    window->show();
    this->close();
}
