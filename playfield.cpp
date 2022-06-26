#include "playfield.h"
#include "game.h"
#include <QKeyEvent>
#include <QDebug>

const int keyCount = 4, keys[] = {Qt::Key_D, Qt::Key_F, Qt::Key_J, Qt::Key_K};

PlayField::PlayField(QGraphicsItem * parent) : QGraphicsRectItem(parent)
{
}

void PlayField::keyPressEvent(QKeyEvent *event)
{
    qDebug() << event->key();
    for (int i = 0; i < keyCount; ++i) {
        if (event->key() == keys[i]) {
            game->keyPress(i);
        }
    }
}

