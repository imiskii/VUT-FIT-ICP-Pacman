#include "gamepage.h"
#include "ui_gamepage.h"

gamepage::gamepage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gamepage)
{
    ui->setupUi(this);
}

gamepage::~gamepage()
{
    delete ui;
}

void gamepage::on_GameBackButton_clicked()
{
    emit GoOnHomePage();
}


void gamepage::on_PlayButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void gamepage::on_GameExitButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void gamepage::on_EndContinueButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

