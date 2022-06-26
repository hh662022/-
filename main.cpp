#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsView>
#include "game.h"
#include "ui_form.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game * game = new Game();

    int ret = a.exec();
    return ret;
}