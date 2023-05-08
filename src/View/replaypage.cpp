/**
 * @file replaypage.cpp
 * @author Michal Las (xlasmi00)
 * @brief Replay view
 *
 */

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


void replaypage::MoveOnPage(RVPageCode page)
{
    switch (page) {
    case RVPageCode::REPLAY_GAME:
        ui->stackedWidget->setCurrentIndex(1);
        break;
    case RVPageCode::HOME:
        emit GoOnHomePage();
        break;
    case RVPageCode::REPLAY_LOBBY:
        ui->stackedWidget->setCurrentIndex(0);
        break;
    default:
        break;
    }
}

void replaypage::AddReplayName(QString replayName)
{
    ui->ReplayComboBox->addItem(replayName);
    ui->ReplayComboBox->setCurrentText(replayName);
}


void replaypage::on_ReplayButton_clicked()
{
    emit NotifyUserAction(RVActionCode::CLICKED_BUTTON_REPLAYGAME);
}


void replaypage::on_ReplayExitButton_clicked()
{
    emit NotifyUserAction(RVActionCode::CLICKED_BUTTON_EXIT);
}


void replaypage::on_BackButton_clicked()
{
    emit NotifyUserAction(RVActionCode::CLICKED_BUTTON_BACK);
}


void replaypage::on_ChooseReplayFileButton_clicked()
{
    emit NotifyUserAction(RVActionCode::CLICKED_BUTTON_CHOOSEREPLAY);
}

/* END OF FILE */
