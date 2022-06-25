#include "score.h"
#include <QFont>

Score::Score()
{
    score = 0;
    setPlainText(QString::number(score));
    setDefaultTextColor(Qt::black);
    setFont(QFont("Consolas", 60));
}

void Score::increaseScore(int delta)
{
    score += delta;
    redraw();
}

void Score::redraw() {
    setPlainText(QString::number(score));
}
