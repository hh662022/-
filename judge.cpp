#include "judge.h"
#include "game.h"
#include "note.h"
#include <QFont>
#include <QDebug>

const char * judgements[windowCount+1] = {"PERFECT", "Perfect", "Great", "Good", "Bad", "Miss"};
const char * judgementImages[windowCount+1] = {":/Skin/mania-hit300g.png", ":/Skin/mania-hit300.png", ":/Skin/mania-hit200.png", ":/Skin/mania-hit100.png", ":/Skin/mania-hit50.png", ":/Skin/mania-hit0.png"};

const int judgementX = marginLeft + playFieldWidth/2, judgementY = marginUp + playFieldHeight/2 + 60;
const int judgementImageX = marginLeft + playFieldWidth/2, judgementImageY = marginUp + playFieldHeight/2;

Judge::Judge(QGraphicsScene *scene, Score * _score, Accuracy * _accuracy)
{
    scene->addItem(this);
    setPos(judgementX, judgementY);
    timer = new QTimer();
    score = _score;
    accuracy = _accuracy;
    setFont(QFont("times", 60));
    judgementImage = new QGraphicsPixmapItem(QPixmap(":/Skin/mania-hit0.png"));
    scene->addItem(judgementImage);
    judgementImage->setPos(judgementImageX, judgementImageY);
    setPlainText("Judgement\nArea");
    combo = 0;
    setTextWidth(500);
}

void Judge::judge(int cur, Note *note, double musicSpeed) {
    assert(canHit(cur, note, musicSpeed));
    note->isHit = true;
    for (int j = 0; j < windowCount; ++j) {
        if (abs(cur - note->time)*musicSpeed <= windows[j]) {
            showJudgement(j, (cur - note->time)*musicSpeed);
            accuracy->addPercent(accuracies[j]);
            // TODO: plot point on timeline
            // TODO: add special effect and sound effect
            // add score
            score->increaseScore(windowCount - j);
            return;
        }
    }
}

void Judge::showJudgement(int judgement, int offset)
{
    if (judgement < comboLimit) combo++;
    else combo = 0;
    // qDebug() << judgement << " " << QString(judgements[judgement]);
    judgementImage->setPixmap(QPixmap(judgementImages[judgement]));
    judgementImage->setPos(judgementImageX-judgementImage->boundingRect().width()/2, judgementImageY-judgementImage->boundingRect().height()/2);
    setHtml(QString("<center>") +
                (judgement != Miss ? QString::number(offset) + QString("ms<br/>") : QString("<br/>") ) +
                QString::number(combo) + QString(" COMBO") +
                QString("</center>")
    );
    // qDebug() << "aa" << textWidth();
    setPos(judgementX - textWidth()/2, judgementY);;
    // setPos(marginLeft + playFieldWidth/2 - textWidth()/2, marginUp + playFieldHeight/2);
    connect(timer, &QTimer::timeout, this, &Judge::hideJudgement);
    timer->start(persistTime);
}

bool Judge::canHit(int cur, Note * note, double musicSpeed) {
    return abs(cur - note->time)*musicSpeed <= windows[Bad];
}

bool Judge::hasMissed(int cur, Note * note, double musicSpeed) {
    return (cur - note->time)*musicSpeed > windows[Bad];
}

void Judge::hideJudgement() {
    setPlainText("");
}

Judge::~Judge()
{
    delete timer;
}
