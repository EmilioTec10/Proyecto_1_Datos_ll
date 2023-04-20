#include <QApplication>
#include "Dificulties_Window.h"
#include <QGuiApplication>
#include <QPixmap>
#include "SerialComm.h"
#include "Normal_Game.h"

Dificulties * difi;
Normal_Game *nor;

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    difi = new Dificulties();
    difi->show();

    return a.exec();
}
