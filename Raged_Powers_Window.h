//
// Created by emmanuel on 07/04/23.
//

#ifndef BATTLESPACE_RAGED_POWERS_WINDOW_H
#define BATTLESPACE_RAGED_POWERS_WINDOW_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>

class Raged_Powers_Window: public QGraphicsView{
public:

    Raged_Powers_Window(std::string value, QWidget *parent=0);
    std::string difi;
    //Game dificulties
    void easy(bool Speed, bool Freeze, bool Bullet, bool Slow);
    void normal(bool Speed, bool Freeze, bool Bullet, bool Slow);
    void hard(bool Speed, bool Freeze, bool Bullet, bool Slow);
    void Chooser1();
    void Chooser2();
    void Chooser3();
    void Chooser4();

    QGraphicsScene * scene;
private:
    int width = 800;
    int height = 600;

};
#endif //BATTLESPACE_RAGED_POWERS_WINDOW_H
