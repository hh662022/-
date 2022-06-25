#ifndef NOTE_H
#define NOTE_H

#include <QGraphicsRectItem>
#include <QMediaPlayer>

class Note : public QGraphicsPixmapItem
{
public:
    int x, y, time, type, hitSound, endTime;
    QMediaPlayer * player;
    bool isHit;
    Note(int _x, int _y, int _time, int _type, int _hitSound, int _endTime);
    bool keyPress();
    bool keyRelease();
private:
};

#endif // NOTE_H
