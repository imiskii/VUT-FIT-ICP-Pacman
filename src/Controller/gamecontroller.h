/**
 * @file gamecontroller.h
 * @author Michal Ľaš (xlasmi00)
 * @brief header file for gamecontroller.cpp
 *
 */

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <qobject.h>
#include "../View/mainwindow.h"
#include "../View/gamepage.h"
#include "../View/replaypage.h"
#include "../Model/GameModel.h"
#include "Model/ReplayModel.h"


/**
 * @brief The GameController class for handeling signals from View and user input
 */
class GameController : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief GameController constructor
     * @param parent parent item
     * @param MainView pointer to main page
     * @param GameView pointer to game page
     * @param ReplayView pointer to replay page
     * @param GameM pointer to game model
     * @param ReplayM pointer to replay model
     */
    explicit GameController(QObject *parent = nullptr, MainWindow *MainView = nullptr, gamepage *GameView = nullptr, replaypage *ReplayView = nullptr,
                            GameModel *GameM = nullptr, ReplayModel *ReplayM = nullptr);
    ~GameController();


private:
    MainWindow *_MainView;                  ///< pointer to Main View
    gamepage *_GameView;                    ///< pointer to Game View
    replaypage *_ReplayView;                ///< pointer to Replay View
    GameModel *_GameM;                      ///< pointer to Game Model
    ReplayModel *_ReplayM;                  ///< pointer to Replay Model
    /**
     * @brief _KeyPressEvent method for handeling pressed keys
     * @param event
     */
    void _KeyPressEvent(QKeyEvent *event);


protected:
    bool eventFilter(QObject *obj, QEvent *event) override;


signals:
    /**
     * @brief notify Main View to change page
     * @param page page to change to
     */
    void ChangeMVPage(MVPageCode page);
    /**
     * @brief notify Game View to change page
     * @param page to change to
     */
    void ChangeGVPage(GVPageCode page);
    /**
     * @brief notify Replay View to change page
     * @param page to change to
     */
    void ChangeRVPage(RVPageCode page);
    /**
     * @brief notify Main View to close the application
     */
    void QuitApp();
    /**
     * @brief notify Game Model to choose the map file
     */
    void ChooseMapFile();
    /**
     * @brief notify Replay Model to choose the replay file
     */
    void ChooseReplayFile();
    /**
     * @brief notify model to strat a new game
     * @param map map to be played
     */
    void StartGame(QString map);
    /**
     * @brief notify model that key that should force move action is pressed
     * @param dr direction of movement that should be done
     */
    void MoveAction(direction dr);
    /**
     * @brief notify model to exit the game
     */
    void ExitGame();
    /**
     * @brief notify model to start a new game
     */
    void NextGame();

    void ReplayGame(QString chosenMap);



public slots:
    /**
     * @brief handling actions for Main View
     * @param code code of action
     */
    void MVHandleAction(MVActionCode code);
    /**
     * @brief handling actions for Game View
     * @param code
     */
    void GVHandleAction(GVActionCode code);
    /**
     * @brief handling actions for Replay View
     * @param code
     */
    void RVHandleAction(RVActionCode code);
    /**
     * @brief handling signal to play the game
     * @param choosenMap map choosen by user
     */
    void PlayButtonAction(QString choosenMap);

    void ReplayButtonAction(QString chosenMap);
};

#endif // GAMECONTROLLER_H


/* END OF FILE */
