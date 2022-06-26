#include "note.h"
#include <QtMultimedia>
#include "game.h"

Note::Note(int _x, int _y, int _time, int _type, int _hitSound, int _endTime)
{
    int lane = _x * columnCount / 512;
    setPixmap(QPixmap(lane == 1 || lane == 2 ? ":/Skin/mania-note2.png" : ":/Skin/mania-note1.png").scaledToWidth(noteWidth));
    x = _x;
    y = _y;
    time = _time;
    type = _type;
    hitSound = _hitSound;
    endTime = _endTime;
    isHit = false;
}

bool Note::keyPress()
{
    // Check if missed
    int cur = player->position();
    return false;
}

bool Note::keyRelease()
{
    return false;
}
