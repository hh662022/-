#ifndef BEGINSCENE_H
#define BEGINSCENE_H

#include <QWidget>

namespace Ui {
class BeginScene;
}

class BeginScene : public QWidget
{
    Q_OBJECT

public:
    explicit BeginScene(QWidget *parent = nullptr);
    ~BeginScene();

private:
    Ui::BeginScene *ui;
};

#endif // BEGINSCENE_H
