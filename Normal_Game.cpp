#include "Normal_Game.h"
#include "Red_Enemy.h"
#include "Blue_Enemy.h"
#include "Game_Over.h"
#include "Win_Window.h"
#include "XML_Reader.h"
#include <QPushButton>
#include <QGuiApplication>
#include <QGraphicsProxyWidget>
#include <QImage>
#include <QTimer>
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QFont>
#include <QList>
#include <QPixmap>
#include <QtWidgets>
#include <functional>
#include <unistd.h>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <unistd.h>
#include "SerialComm.h"

XML_Reader xml_reader;
/**
 * @brief Normal_Game::Normal_Game Constructor que genera la ventana del juego normal y facil
 * @param bullet_speed Velocidad de las balas
 * @param bullets Cantidad de balas
 * @param ships_number Cantidad de naves enemigas
 * @param health Cantidad de vida
 * @param parent Widget que hace posible usar qobjects en la escena
 */
Normal_Game::Normal_Game(int bullet_speed, int bullets, int ships_number, int health, bool Speed, bool Freeze, bool Bullet, bool Slow, QWidget *parent){
    Red_Enemy red_enemy;


    //Creation and configuration of the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    scene->setBackgroundBrush(QBrush(QImage(":/Images/background.jpg")));
    QFont font("Arial", 15, QFont::Helvetica);

    //Creation of the images
    QPixmap bullets_(":/Images/bullet.png");
    QGraphicsPixmapItem *myPixmapItem = new QGraphicsPixmapItem(bullets_);

    QPixmap heart(":/Images/heart");
    QGraphicsPixmapItem *myHeart = new QGraphicsPixmapItem(heart);

    //Declaration of the private variables
    this->bullets_speed = bullet_speed;
    this->bullets_number = bullets;
    this->health_number = health;
    this->enemy_speed = 5;
    Raged_Powers_Bullet_Speed =Speed;
    Raged_Powers_Bullet_Amount = Bullet;
    Raged_Powers_Enemy_Speed =Slow;
    Raged_Powers_Enemy_Freeze=Freeze;
    //Number of bullets label
    bullets_label = new QGraphicsTextItem("Bullets: " + QString::number(bullets_number));
    bullets_label->setFont(font);
    bullets_label->setDefaultTextColor(Qt::red);
    //Bullet collector label
    bullet_collector = new QGraphicsTextItem("Bullet Collector: " + QString::number(collector->size));
    bullet_collector->setFont(font);
    bullet_collector->setDefaultTextColor(Qt::red);
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
    scene->addItem(myPixmapItem);
    scene->addItem(myHeart);
    scene->addItem(bullets_label);
    scene->addItem(bullet_collector);
    scene->addItem(bullets_speed_label);
    scene->addItem(health_label);
    scene->addItem(wave_label);
    scene->addItem(fase_label);

    //Set positions of the items in the scene
    myPixmapItem->setPos(0,0);
    myHeart->setPos(50,0);
    bullets_label->setPos(0,50);
    bullet_collector->setPos(0,70);
    bullets_speed_label->setPos(0,90);
    health_label->setPos(0,110);
    wave_label->setPos(700,20);
    fase_label->setPos(700,0);

    //Make the player the focus of the view
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    player->setPos(0,150);
    player->set_enemies(ships_number);
    player->setCollector(collector);
    player->set_CollectorLabel(bullet_collector);

    //Spawn enemies at the beginning
    player->spawn_enemies(ships_number, scene);

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
    QObject::connect(timer_enemies,SIGNAL(timeout()),player,SLOT(conect()));
    timer_enemies->start(10000);

    //Timer to decrese the bullets label
    QObject::connect(timer_decrease_bullets,SIGNAL(timeout()),this,SLOT(decrease_bullets()));
    timer_decrease_bullets->start(bullet_speed);

    //Timer to check the Health of the player
    check = new QTimer;
    QObject::connect(check,SIGNAL(timeout()),this,SLOT(check_health()));
    check->start(50);

    check2 = new QTimer;
    QObject::connect(check2,SIGNAL(timeout()),player,SLOT(startSerialConnection()));
    check2->start(200);

    check3 = new QTimer;
    QObject::connect(check3,SIGNAL(timeout()),this,SLOT(Aduino_Movement()));
    check3->start(210);
    Aduino_Movement();

    check4 = new QTimer;
    QObject::connect(check4, SIGNAL(timeout()), this, SLOT(potenciometer()));
    check4->start(1000);

    wave_arduino_timer = new QTimer;
    QObject::connect(wave_arduino_timer,SIGNAL(timeout()),this, SLOT(enviar_Dato()));
    wave_arduino_timer->start(10010);
    enviar_Dato();

    show();
}


std::mutex mutex;
std::condition_variable cv;
/**
 * @brief Normal_Game::keyPressEvent Metodo que recibe los eventos del teclado y ejecuta funciones
 * @param event Evento del teclado recibido
 */
void Normal_Game::keyPressEvent(QKeyEvent *event) {
    Red_Enemy red_enemy;
    if (event->key() == Qt::Key_Up) {

        if (player->y() > 0) {

            player->setPos(player->x(), player->y() - 10);

        }
    } else if (event->key() == Qt::Key_Down) {
        if (player->y() < 500) {
            player->setPos(player->x(), player->y() + 10);
        }
    } else if (event->key() == Qt::Key_Q) {
        if (bullets_speed < 1200) {
            bullets_speed += 100;
            timer_bullets->setInterval(bullets_speed + 10);
            change_speed_bullets();
            timer_decrease_bullets->setInterval(bullets_speed);
        } else {
            return;
        }
    } else if (event->key() == Qt::Key_W) {
        if (bullets_speed > 200) {
            bullets_speed -= 100;
            timer_bullets->setInterval(bullets_speed + 10);
            change_speed_bullets();
            timer_decrease_bullets->setInterval(bullets_speed);
        } else {
            return;
        }
    } else if (event->key() == Qt::Key_P && Raged_Powers_Bullet_Speed ==true) {

        QTimer *timer = new QTimer;
        connect(timer,SIGNAL(timeout()),this,SLOT(Wait())); //conect method that repeats the method everytime it recives the signal
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
        timer->start(8000); //Signal every 50 miliseconds
    }
    else if (event->key() == Qt::Key_O && Raged_Powers_Enemy_Freeze ==true) {
        Raged_Powers_Enemy_Freeze=false;
        xml_reader.Data_Changer("/home/emmanuel/CLionProjects/Proyecto_1_Datos_ll/Battlespace/Raged_Powers_XML2.xml","0");
        xml_reader.Data_Changer("/home/emmanuel/CLionProjects/Proyecto_1_Datos_ll/Battlespace/Raged_Powers_XML3.xml","0");
        QTimer *timer = new QTimer;
        connect(timer, SIGNAL(timeout()), this,SLOT(Back_to_past_2())); //conect method that repeats the method everytime it recives the signal
        timer->start(8000); //Signal every 50 miliseconds
    }
    else{
        return;
    }
}
/**
 * @brief
 */
void Normal_Game::Wait(){
    xml_reader.XML_Data_Finder("/home/emmanuel/CLionProjects/Proyecto_1_Datos_ll/Battlespace/Raged_Powers_XML.xml");
    bullets_speed = xml_reader.newest_data;
    timer_bullets->setInterval(bullets_speed + 10);
    change_speed_bullets();
    timer_decrease_bullets->setInterval(bullets_speed);
    QTimer *timer = new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(Back_to_past())); //conect method that repeats the method everytime it recives the signal
    timer->start(5000); //Signal every 50 miliseconds

}
int nose = 1;
void Normal_Game::enviar_Dato(){

    // Convertir el número entero a una cadena de caracteres
    char c = '2'; // Carácter a enviar
    ssize_t bytes_written = write(player->fd, &c, 1);
    write(player->fd, &c, 1);
}

void Normal_Game::potenciometer(){
    if (player->data21 == 'X'){
        bullets_speed = 200;

        timer_bullets->setInterval(bullets_speed);
        timer_decrease_bullets->setInterval(bullets_speed);
    }
    if (player->data21 == 'C'){
        bullets_speed =    300;
        timer_bullets->setInterval(bullets_speed);
        timer_decrease_bullets->setInterval(bullets_speed);
    }
    if (player->data21 == 'V'){
        bullets_speed =    400;
        timer_bullets->setInterval(bullets_speed);
        timer_decrease_bullets->setInterval(bullets_speed);
    }
    if (player->data21 == 'B'){
        bullets_speed =    500;
        timer_bullets->setInterval(bullets_speed);
        timer_decrease_bullets->setInterval(bullets_speed);
    }
    if (player->data21 == 'N'){
        bullets_speed +=    600;
        timer_bullets->setInterval(bullets_speed);
        timer_decrease_bullets->setInterval(bullets_speed);
    }
    if (player->data21 == 'M'){
        bullets_speed +=    700;
        timer_bullets->setInterval(bullets_speed);
        timer_decrease_bullets->setInterval(bullets_speed);
    }if (player->data21 == 'A'){
        bullets_speed +=    800;

        timer_bullets->setInterval(bullets_speed);
        timer_decrease_bullets->setInterval(bullets_speed);
    }
    if (player->data21 == 'S'){
        bullets_speed =    900;

        timer_bullets->setInterval(bullets_speed);
        timer_decrease_bullets->setInterval(bullets_speed);
    }
    if (player->data21 == 'D'){
        bullets_speed =    1000;
        timer_bullets->setInterval(bullets_speed);
        timer_decrease_bullets->setInterval(bullets_speed);
    }
}

void Normal_Game::Aduino_Movement(){
    if (player->data12 == 'U'){
        if (player->y() > 0) {

            player->setPos(player->x(), player->y() - 30);

        }
    }
    if (player->data12 == 'L'){
        if (player->y() < 500) {
            player->setPos(player->x(), player->y() + 30);
        }
    }
    if (player->data12 == 'F'){

        //std::cout<<"nothing to do";
    }


}
/**
 * @brief Normal_Game::decrease_bullets Metodo que disminuye el contador de balas
 */
void Normal_Game::decrease_bullets()
{
    if (bullets_number == 0){
        timer_decrease_bullets->stop();
    }
    else{
        bullets_number--;
        bullets_label->setPlainText("Bullets: " + QString::number(bullets_number));
    }
}
void Normal_Game::Back_to_past(){

    bullets_speed = 500;
    timer_bullets->setInterval(bullets_speed + 10);
    change_speed_bullets();
    timer_decrease_bullets->setInterval(bullets_speed);
}
void Normal_Game::Back_to_past_2(){
    xml_reader.Data_Changer("/home/emmanuel/CLionProjects/Proyecto_1_Datos_ll/Battlespace/Raged_Powers_XML2.xml", "5");
    xml_reader.Data_Changer("/home/emmanuel/CLionProjects/Proyecto_1_Datos_ll/Battlespace/Raged_Powers_XML3.xml", "10");
}
/**
 * @brief Normal_Game::decrease_health Metodo que disminuye la vida del jugador
 */
void Normal_Game::decrease_health()
{
    if (health_number == 0){
        return;
    }
    else{
        health_number--;
        health_label->setPlainText("Health: " + QString::number(health_number));
    }
}
/**
 * @brief Hard_Game::check_health Revisa si los enemigos llegaron al final para quitar una vida y en caso de llegar a 0 se abre la ventana de perdiste
 */
void Normal_Game::check_health()
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
            if (typeid(*(colliding_items[i])) == typeid(Red_Enemy)){ //Checks if the red enemy is colliding with the line
                Red_Enemy *red_ne =  qgraphicsitem_cast<Red_Enemy *>(colliding_items[i]);
                //player->enemies_list->printList();
                player->enemies_list->deleteNode(red_ne);
                decrease_health();
            }
            else if (typeid(*(colliding_items[i])) == typeid(Blue_Enemy)){ //Checks if the blue enemy is colliding with the line
                Blue_Enemy *blue_ne =  qgraphicsitem_cast<Blue_Enemy *>(colliding_items[i]);

                player->enemies_list->deleteNode(blue_ne);
                decrease_health();
            }
        }
    }

}
/**
 * @brief Hard_Game::increase_wave Aumenta la oleada del juego
 */
void Normal_Game::increase_wave()
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

/**
 * @brief Hard_Game::increase_fase Aumenta la fase y revisa se gano el juego
 */
void Normal_Game::increase_fase()
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
/**
 * @brief Hard_Game::change_speed_bullets Cambia la velocidad de las balas en el label
 */
void Normal_Game::change_speed_bullets()
{
    bullets_speed_label->setPlainText("New Bullets Speed is: " + QString::number(bullets_speed));
}

int Normal_Game::get_enemy_speed() {
    return this->enemy_speed;
}