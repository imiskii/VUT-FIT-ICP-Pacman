#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <qobject.h>
#include "../View/mainwindow.h"
#include "../View/gamepage.h"
#include "../View/replaypage.h"
#include "../Model/GameModel.h"
#include "Model/ReplayModel.h"


class GameController : public QObject
{
    Q_OBJECT
public:
    explicit GameController(QObject *parent = nullptr, MainWindow *MainView = nullptr, gamepage *GameView = nullptr, replaypage *ReplayView = nullptr,
                            GameModel *GameM = nullptr, ReplayModel *ReplayM = nullptr);
    ~GameController();


private:
    MainWindow *_MainView;      //< pointer to Main View
    gamepage *_GameView;        //< pointer to Game View
    replaypage *_ReplayView;    //< pointer to Replay View
    GameModel *_GameM;          //< pointer to Game Model
    ReplayModel *_ReplayM;      //< pointer to Replay Model
    void _KeyPressEvent(QKeyEvent *event); //< functions for handeling pressed keys


protected:
    bool eventFilter(QObject *obj, QEvent *event) override;


signals:
    /**
     * @brief ChangeMVPage notify Main View to change page
     * @param page page to change to
     */
    void ChangeMVPage(MVPageCode page);
    /**
     * @brief ChangeGVPage notify Game View to change page
     * @param page to change to
     */
    void ChangeGVPage(GVPageCode page);
    /**
     * @brief ChangeRVPage notify Replay View to change page
     * @param page to change to
     */
    void ChangeRVPage(RVPageCode page);
    /**
     * @brief QuitApp notify Main View to close the application
     */
    void QuitApp();
    /**
     * @brief ChooseMapFile notify Game Model to choose the map file
     */
    void ChooseMapFile();
    /**
     * @brief ChooseReplayFile notify Replay Model to choose the replay file
     */
    void ChooseReplayFile();
    /**
     * @brief StartGame notify model to strat a new game
     * @param map map to be played
     */
    void StartGame(QString map);
    /**
     * @brief MoveAction notify model that key that should force move action is pressed
     * @param dr direction of movement that should be done
     */
    void MoveAction(direction dr);



public slots:
    /**
     * @brief MVHandleAction handling actions for Main View
     * @param code code of action
     */
    void MVHandleAction(MVActionCode code);
    /**
     * @brief GVHandleAction handling actions for Game View
     * @param code
     */
    void GVHandleAction(GVActionCode code);
    /**
     * @brief RVHandleAction handling actions for Replay View
     * @param code
     */
    void RVHandleAction(RVActionCode code);
    /**
     * @brief PlayButtonAction handling signal to play the game
     * @param choosenMap map choosen by user
     */
    void PlayButtonAction(QString choosenMap);
};

#endif // GAMECONTROLLER_H
