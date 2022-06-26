#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

class Score : public QGraphicsTextItem
{
public:
    int score;
    Score();
    void increaseScore(int delta);
    void redraw();
};

#endif // SCORE_H
