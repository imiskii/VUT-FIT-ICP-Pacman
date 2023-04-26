/**
 * @file gamepage.h
 * @author Michal Ľaš (xlasmi00)
 * @brief header file for gamepage.cpp
 */

#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QWidget>


/**
 * @brief The GVPageCode enum application pages codes in GameView
 */
enum class GVPageCode
{
    HOME,
    PLAY_GAME,
    GAME_END,
    GAME_EXIT
};


/**
 * @brief The GVActionCode enum user action codes in GameView
 */
enum class GVActionCode
{
    CLICKED_BUTTON_BACK,
    CLICKED_BUTTON_PLAYGAME,
    CLICKED_BUTTON_EXIT,
    CLICKED_BUTTON_CONTINUE
};


namespace Ui {
class gamepage;
}

class gamepage : public QWidget
{
    Q_OBJECT

public:
    explicit gamepage(QWidget *parent = nullptr);
    ~gamepage();


private:
    Ui::gamepage *ui;


signals:
    /**
     * @brief NotifyUserAction Notify controller about acctions in GameView
     * @param code code of action
     */
    void NotifyUserAction(GVActionCode code);
    /**
     * @brief GoOnHomePage signal to change page on home page
     */
    void GoOnHomePage();


public slots:
    /**
     * @brief MoveOnPage Change page of application
     * @param page code of the page where apllication should move
     */
    void MoveOnPage(GVPageCode page);


private slots:
    void on_GameBackButton_clicked();
    void on_PlayButton_clicked();
    void on_GameExitButton_clicked();
    void on_EndContinueButton_clicked();


};

#endif // GAMEPAGE_H
