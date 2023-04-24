#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamepage.h"
#include "replaypage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_QuitButton_clicked();
    void on_PlayGameButton_clicked();
    void on_ReplayGameButton_clicked();
    void MoveOnHomePage();

private:
    Ui::MainWindow *ui;
    gamepage _GamePage;
    replaypage _ReplayPage;
};
#endif // MAINWINDOW_H
