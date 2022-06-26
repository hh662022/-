#include "playscene.h"
#include "ui_playscene.h"

PlayScene::PlayScene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayScene)
{
    ui->setupUi(this);
}

PlayScene::~PlayScene()
{
    delete ui;
}
