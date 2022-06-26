#include "beginscene.h"
#include "ui_beginscene.h"

BeginScene::BeginScene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BeginScene)
{
    ui->setupUi(this);
}

BeginScene::~BeginScene()
{
    delete ui;
}
