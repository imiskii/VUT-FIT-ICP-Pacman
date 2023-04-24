#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set up pages
    // Game page index => 1
    // Replay page index => 2
    ui->stackedWidget->insertWidget(1, &_GamePage);
    ui->stackedWidget->insertWidget(2, &_ReplayPage);

    connect(&_GamePage, SIGNAL(GoOnHomePage()), this, SLOT(MoveOnHomePage()));
    connect(&_ReplayPage, SIGNAL(GoOnHomePage()), this, SLOT(MoveOnHomePage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_QuitButton_clicked()
{
    this->close();
}


void MainWindow::on_PlayGameButton_clicked()
{
    // move on Game page
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_ReplayGameButton_clicked()
{
    // move on Replay page
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::MoveOnHomePage()
{
    ui->stackedWidget->setCurrentIndex(0);
}

