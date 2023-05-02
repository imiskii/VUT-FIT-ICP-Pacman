/**
 * @file gamepage.h
 * @author Michal Ľaš (xlasmi00)
 * @brief header file for gamepage.cpp
 */

#ifndef GAMEPAGE_H
#define GAMEPAGE_H

#include <QWidget>
#include <QGraphicsScene>
#include <vector>
#include "../consts.h"
#include "ui_gamepage.h"
#include "GameItems.h"


/**
 * @brief The GVPageCode enum application pages codes in GameView
 */
enum class GVPageCode
{
    HOME,       ///< Home page
    PLAY_GAME,  ///< Game page
    GAME_END,   ///< Final page after game ends
    GAME_LOBBY  ///< Before game lobby page
};


/**
 * @brief The GVActionCode enum user action codes in GameView
 */
enum class GVActionCode
{
    CLICKED_BUTTON_BACK,        ///< Back button
    CLICKED_BUTTON_PLAYGAME,    ///< PLAY button
    CLICKED_BUTTON_EXIT,        ///< Exit button
    CLICKED_BUTTON_NEXTLEVEL,   ///< Continue button
    CLICKED_BUTTON_CHOOSEMAP    ///< Choose Map button
};


namespace Ui {
class gamepage;
}

/**
 * @brief The gamepage class Pacman Game View
 */
class gamepage : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief gamepage constructor
     * @param parent
     */
    explicit gamepage(QWidget *parent = nullptr);
    ~gamepage();


private:
    Ui::gamepage *ui;                   ///< GamePage UI
    QGraphicsScene *_scene;             ///< Game scene
    unsigned _mapRowCount;              ///< number of rows in map
    unsigned _mapColumnCount;           ///< number of columns in map
    PacmanItem *_pacman;                ///< Pacman view object
    std::vector<GhostItem*> _ghosts;    ///< Vector with ghost objects
    std::vector<KeyItem*> _keys;        ///< Vector with keys objects
    TargetItem *_target;                ///< Target item
    qreal _cellSize;                    ///< Size of one cell in GraphicView


protected:
    /**
     * @brief resizeEvent override of QWidget resizeEvent
     * @param event
     */
    void resizeEvent(QResizeEvent* event) override;
    /**
     * @brief updateSceneItemsSize resize all items in QGraphicsView
     * @param newSize new size of items in QGraphicsView
     */
    void updateSceneItemsSize();


signals:
    /**
     * @brief PlayButtonClicked Notify controller that player want to play a game
     * @param choosenMap name of map selected by user
     */
    void PlayButtonClicked(QString choosenMap);
    /**
     * @brief NotifyUserAction Notify controller about acctions in GameView
     * @param code code of action
     */
    void NotifyUserAction(GVActionCode code);
    /**
     * @brief GoOnHomePage signal to change page on home page
     */
    void GoOnHomePage();
    /**
     * @brief MoveFinished notify Model that pacman movement was finished
     */
    void PacmanMoveFinished();


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
    /**
     * @brief ShowGameField Create new game field and add it to scene
     * @param gameField 2D array representing game field
     */
    void ShowGameField(std::vector<std::vector<char>> &gameField);
    /**
     * @brief ShowMessage Show message in game lobby
     * @param msg Message that will be displayed
     */
    void ShowMessage(QString msg);
    /**
     * @brief UpdatePacmanPosition update position of pacman object on scene
     * @param dr direction of new pacman position
     */
    void UpdatePacmanPosition(direction dr, int speed);
    /**
     * @brief PacmanMovementFinished handeling signal from PacmanItem that animation of movement was finished
     */
    void PacmanMovementFinished();
    /**
     * @brief deleteKeyFromMap delete KeyItem from map on given index
     * @param index index of KeyItem
     */
    void deleteKeyFromMap(int index);
    /**
     * @brief deleteScene delete current displayed scene
     */
    void deleteScene();


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
     * @brief on_EndContinueButton_clicked sends signal to Controller that 'Exit' button was clicked
     */
    void on_ExitGameButton_clicked();
    /**
     * @brief on_ChooseMapFileButton_clicked sends signal to Controller that 'Choose Map' button was clicked
     */
    void on_ChooseMapFileButton_clicked();
    /**
     * @brief on_NextGame_clicked sends signal to Controller that 'NEXT LEVEL' button was clicked
     */
    void on_NextGame_clicked();
};


#endif // GAMEPAGE_H


/* END OF FILE */