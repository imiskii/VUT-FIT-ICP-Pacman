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



public slots:
    /**
     * @brief MVHandleAction handeling actions for Main View
     * @param code code of action
     */
    void MVHandleAction(MVActionCode code);
    /**
     * @brief GVHandleAction handeling actions for Game View
     * @param code
     */
    void GVHandleAction(GVActionCode code);
    /**
     * @brief RVHandleAction handeling actions for Replay View
     * @param code
     */
    void RVHandleAction(RVActionCode code);
};

#endif // GAMECONTROLLER_H
