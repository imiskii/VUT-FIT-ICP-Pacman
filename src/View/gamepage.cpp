/**
 * @file gamepage.cpp
 * @author Michal Ľaš (xlasmi00)
 * @brief Game View
 * 
 */

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


void gamepage::MoveOnPage(GVPageCode page)
{
    switch (page) {
    case GVPageCode::PLAY_GAME:
        ui->stackedWidget->setCurrentIndex(1);
        break;
    case GVPageCode::HOME:
        emit GoOnHomePage();
        break;
    case GVPageCode::GAME_END:
    case GVPageCode::GAME_EXIT:
        ui->stackedWidget->setCurrentIndex(0);
        break;
    default:
        break;
    }
}


void gamepage::on_GameBackButton_clicked()
{
    emit NotifyUserAction(GVActionCode::CLICKED_BUTTON_BACK);
}


void gamepage::on_PlayButton_clicked()
{
    emit NotifyUserAction(GVActionCode::CLICKED_BUTTON_PLAYGAME);
}


void gamepage::on_GameExitButton_clicked()
{
    emit NotifyUserAction(GVActionCode::CLICKED_BUTTON_EXIT);
}


void gamepage::on_EndContinueButton_clicked()
{
    emit NotifyUserAction(GVActionCode::CLICKED_BUTTON_CONTINUE);
}

