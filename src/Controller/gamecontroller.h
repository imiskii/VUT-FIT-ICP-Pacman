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
    MainWindow *_MainView;
    gamepage *_GameView;
    replaypage *_ReplayView;
    GameModel *_GameM;
    ReplayModel *_ReplayM;


signals:
    void ChangeMVPage(MVPageCode page);
    void ChangeGVPage(GVPageCode page);
    void ChangeRVPage(RVPageCode page);
    void QuitApp();



public slots:
    void MVHandleAction(MVActionCode code);
    void GVHandleAction(GVActionCode code);
    void RVHandleAction(RVActionCode code);
};

#endif // GAMECONTROLLER_H
