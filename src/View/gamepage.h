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
    HOME,       //< Home page
    PLAY_GAME,  //< Game page
    GAME_END,   //< Final page after game ends
    GAME_LOBBY  //< Before game lobby page
};


/**
 * @brief The GVActionCode enum user action codes in GameView
 */
enum class GVActionCode
{
    CLICKED_BUTTON_BACK,        //< Back button
    CLICKED_BUTTON_PLAYGAME,    //< PLAY button
    CLICKED_BUTTON_EXIT,        //< Exit button
    CLICKED_BUTTON_CONTINUE,    //< Continue button
    CLICKED_BUTTON_CHOOSEMAP    //< Choose Map button
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
    Ui::gamepage *ui; //< GamePage UI


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
    /**
     * @brief AddMapFile Add new map name to combobox
     * @param mapFile name of new map
     */
    void AddMapName(QString mapName);


private slots:
    /**
     * @brief on_GameBackButton_clicked sends signal to Controller that 'Back' button was clicked
     */
    void on_GameBackButton_clicked();
    /**
     * @brief on_PlayButton_clicked sends signal to Controller that 'PLAY' button was clicked
     */
    void on_PlayButton_clicked();
    /**
     * @brief on_GameExitButton_clicked sends signal to Controller that 'Exit' button was clicked
     */
    void on_GameExitButton_clicked();
    /**
     * @brief on_EndContinueButton_clicked sends signal to Controller that 'Continue' button was clicked
     */
    void on_EndContinueButton_clicked();
    /**
     * @brief on_ChooseMapFileButton_clicked sends signal to Controller that 'Choose Map' button was clicked
     */
    void on_ChooseMapFileButton_clicked();
};

#endif // GAMEPAGE_H
