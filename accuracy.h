#ifndef ACCURACY_H
#define ACCURACY_H

#include <QGraphicsTextItem>
#include <QObject>

class Accuracy : public QGraphicsTextItem
{
    Q_OBJECT
public:
    Accuracy();
    void addPercent(int percent);
private:
    int count;
    int total;
};

#endif // ACCURACY_H
