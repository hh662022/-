#ifndef JUDGE_H
#define JUDGE_H

#include <QGraphicsTextItem>
#include <QObject>
#include "note.h"
#include "score.h"
#include "accuracy.h"
#include <QTimer>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

const int persistTime = 1000;
const int accuracies[] = {300, 300, 200, 100, 50, 0};
// reference: https://www.reddit.com/r/osugame/comments/6phntt/difficulty_settings_table_with_all_values/
const int OD = 10, windowCount = 5, windows[windowCount] = { 16,  64 - OD * 3 , 97 - OD * 3, 127 - OD * 3, 151 - OD * 3 };
enum Judgement {Max, Perfect, Great, Good, Bad, Miss};
const int comboLimit = 4;

class Judge : public QGraphicsTextItem
{
    Q_OBJECT
public:
    Judge(QGraphicsScene * scene, Score * _score, Accuracy * _accuracy);
    void showJudgement(int judgement, int offset = 0);
    bool hasMissed(int cur, Note * note, double musicSpeed);
    void judge(int cur, Note * note, double musicSpeed);
    bool canHit(int cur, Note * note, double musicSpeed);
    QGraphicsPixmapItem * judgementImage;
        ~Judge();
public slots:
    void hideJudgement();
private:
    int combo;
    Score * score;
    Accuracy * accuracy;
    QTimer * timer;
};

#endif // JUDGE_H
