/**
 * @file mainwindow.h
 * @author Michal Ľaš (xlasmi00)
 * @brief header file for mainwindow.cpp
 * 
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamepage.h"
#include "replaypage.h"


/**
 * @brief The MVPageCode enum application pages codes in MainView
 */
enum class MVPageCode
{
    GAME_LOBBY,
    REPLAY_LOBBY
};


/**
 * @brief The MVActionCode enum user action codes in MainView
 */
enum class MVActionCode
{
    CLICKED_BUTTON_GAME,
    CLICKED_BUTTON_REPLAY,
    CLICKED_BUTTON_QUIT
};


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, gamepage *GamePage = nullptr, replaypage *ReplayPage = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    gamepage *_GamePage;
    replaypage *_ReplayPage;


signals:
    /**
     * @brief NotifyUserAction Notify controller about acctions in View
     * @param code code of action
     */
    void NotifyUserAction(MVActionCode code);


public slots:
    /**
     * @brief MoveOnPage Change page of application
     * @param page code of the page where apllication should move
     */
    void MoveOnPage(MVPageCode page);

    /**
     * @brief QuitApp Quit the application window
     */
    void QuitApp();

private slots:
    void on_QuitButton_clicked();
    void on_PlayGameButton_clicked();
    void on_ReplayGameButton_clicked();

    /**
     * @brief MoveOnHomePage Change current page of application to Home page
     */
    void MoveOnHomePage();

};
#endif // MAINWINDOW_H
