#include "replaypage.h"
#include "ui_replaypage.h"

replaypage::replaypage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::replaypage)
{
    ui->setupUi(this);
}

replaypage::~replaypage()
{
    delete ui;
}

void replaypage::on_pushButton_clicked()
{
    emit GoOnHomePage();
}


void replaypage::on_PlayButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void replaypage::on_ReplayExitButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

