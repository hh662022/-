#ifndef ENDSCENE_H
#define ENDSCENE_H

#include <QWidget>

namespace Ui {
class EndScene;
}

class EndScene : public QWidget
{
    Q_OBJECT

public:
    explicit EndScene(QWidget *parent = nullptr);
    ~EndScene();

private:
    Ui::EndScene *ui;
};

#endif // ENDSCENE_H
