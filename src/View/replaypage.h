/**
 * @file replaypage.h
 * @author
 * @brief header file for replaypage.cpp
 *
 */

#ifndef REPLAYPAGE_H
#define REPLAYPAGE_H

#include <QWidget>
#include "gamepage.h"

/**
 * @brief The RVPageCode enum application pages codes in ReplayView
 */
enum class RVPageCode
{
    HOME,           //< Home page
    REPLAY_GAME,    //< Replay page
    REPLAY_LOBBY    //< before replay lobby page
};


/**
 * @brief The RVActionCode enum user action codes in ReplayView
 */
enum class RVActionCode
{
    CLICKED_BUTTON_BACK,        //< Back button
    CLICKED_BUTTON_REPLAYGAME,  //< Replay button
    CLICKED_BUTTON_EXIT,        //< Exit button
    CLICKED_BUTTON_CHOOSEREPLAY //< Choose Replay button
};


namespace Ui {
class replaypage;
}

/**
 * @brief The replaypage class pacman Replay View
 */
class replaypage : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief replaypage constructor
     * @param parent
     */
    explicit replaypage(QWidget *parent = nullptr);
    ~replaypage();

private:
    Ui::replaypage *ui;


signals:
    /**
     * @brief NotifyUserAction Notify controller about acctions in GameView
     * @param code code of action
     */
    void NotifyUserAction(RVActionCode code);
    /**
     * @brief GoOnHomePage signal to change page on home page
     */
    void GoOnHomePage();


public slots:
    /**
     * @brief MoveOnPage Change page of application
     * @param page code of the page where apllication should move
     */
    void MoveOnPage(RVPageCode page);
    /**
     * @brief AddReplayName add new replay name to combobox
     * @param replayName name of new replay
     */
    void AddReplayName(QString replayName);


private slots:
    /**
     * @brief on_ReplayExitButton_clicked sends signal to Controller that 'Exit' button was clicked
     */
    void on_ReplayExitButton_clicked();
    /**
     * @brief on_ReplayButton_clicked sends signal to Controller that 'Replay' button was clicked
     */
    void on_ReplayButton_clicked();
    /**
     * @brief on_BackButton_clicked sends signal to Controller that 'Back' button was clicked
     */
    void on_BackButton_clicked();
    /**
     * @brief on_ChooseReplayFileButton_clicked sends signal to Controller that 'Choose Replay' button was clicked
     */
    void on_ChooseReplayFileButton_clicked();
};

#endif // REPLAYPAGE_H


/* END OF FILE */
