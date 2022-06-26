#ifndef CHOOSESCENE_H
#define CHOOSESCENE_H

#include <QWidget>

namespace Ui {
class ChooseScene;
}

class ChooseScene : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseScene(QWidget *parent = nullptr);
    ~ChooseScene();

private:
    Ui::ChooseScene *ui;
};

#endif // CHOOSESCENE_H
