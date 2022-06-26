#include "choosescene.h"
#include "ui_choosescene.h"

ChooseScene::ChooseScene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseScene)
{
    ui->setupUi(this);
}

ChooseScene::~ChooseScene()
{
    delete ui;
}
