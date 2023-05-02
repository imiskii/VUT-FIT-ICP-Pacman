/**
 * @file mainwindow.cpp
 * @author Michal Ľaš (xlasmi00)
 * @brief Main view
 * 
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent, gamepage *GamePage, replaypage *ReplayPage)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->_GamePage = GamePage;
    this->_ReplayPage = ReplayPage;

    // Set up pages
    // Game page index => 1
    // Replay page index => 2
    ui->stackedWidget->insertWidget(1, this->_GamePage);
    ui->stackedWidget->insertWidget(2, this->_ReplayPage);

    connect(_GamePage, &gamepage::GoOnHomePage, this, &MainWindow::MoveOnHomePage);
    connect(_ReplayPage, &replaypage::GoOnHomePage, this, &MainWindow::MoveOnHomePage);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::MoveOnHomePage()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::MoveOnPage(MVPageCode page)
{
    switch (page) {
    case MVPageCode::GAME_LOBBY:
        ui->stackedWidget->setCurrentIndex(1);
        break;
    case MVPageCode::REPLAY_LOBBY:
        ui->stackedWidget->setCurrentIndex(2);
        break;
    default:
        break;
    }
}


void MainWindow::QuitApp()
{
    this->close();
}


void MainWindow::on_QuitButton_clicked()
{
    emit NotifyUserAction(MVActionCode::CLICKED_BUTTON_QUIT);
}


void MainWindow::on_PlayGameButton_clicked()
{
    emit NotifyUserAction(MVActionCode::CLICKED_BUTTON_GAME);
}


void MainWindow::on_ReplayGameButton_clicked()
{
    emit NotifyUserAction(MVActionCode::CLICKED_BUTTON_REPLAY);
}


/* END OF FILE */