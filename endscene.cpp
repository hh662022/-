#include "endscene.h"
#include "ui_endscene.h"

EndScene::EndScene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EndScene)
{
    ui->setupUi(this);
}

EndScene::~EndScene()
{
    delete ui;
}
