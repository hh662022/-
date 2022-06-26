#include "accuracy.h"
#include "game.h"
#include <QFont>

Accuracy::Accuracy()
{
    setPos(marginLeft + playFieldWidth, 0);
    setFont(QFont("times", 60));
    setDefaultTextColor(Qt::black);
    setPlainText(QString("--.--%"));
    count = 0;
    total = 0;
}

void Accuracy::addPercent(int percent) {
    count++;
    total += percent;
    setPlainText(QString::number(float(total) / (3*count)) + QString("%"));
}
