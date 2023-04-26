/**
 * @file replaypage.h
 * @author Michal Ľaš (xlasmi00)
 * @brief header file for replaypage.cpp
 * 
 */

#ifndef REPLAYPAGE_H
#define REPLAYPAGE_H

#include <QWidget>


/**
 * @brief The RVPageCode enum application pages codes in ReplayView
 */
enum class RVPageCode
{
    HOME,
    REPLAY_GAME,
    REPLAY_EXIT
};


/**
 * @brief The RVActionCode enum user action codes in ReplayView
 */
enum class RVActionCode
{
    CLICKED_BUTTON_BACK,
    CLICKED_BUTTON_REPLAYGAME,
    CLICKED_BUTTON_EXIT
};


namespace Ui {
class replaypage;
}

class replaypage : public QWidget
{
    Q_OBJECT

public:
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


private slots:
    void on_ReplayExitButton_clicked();
    void on_ReplayButton_clicked();
    void on_BackButton_clicked();
};

#endif // REPLAYPAGE_H
