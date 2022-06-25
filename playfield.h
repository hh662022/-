#ifndef PLAYFIELD_H
#define PLAYFIELD_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>

class Game;

class PlayField : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Game * game;
    PlayField(QGraphicsItem * parent = nullptr);
    void keyPressEvent(QKeyEvent * event);
};

#endif // PLAYFIELD_H
