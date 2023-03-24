#include <QApplication>
#include "Dificulties_Window.h"

Dificulties * difi;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    difi = new Dificulties();
    difi->show();

    return a.exec();
}
