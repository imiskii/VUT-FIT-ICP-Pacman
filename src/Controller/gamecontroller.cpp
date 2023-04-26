#include "gamecontroller.h"


GameController::GameController(QObject *parent, MainWindow *MainView, gamepage *GameView, replaypage *ReplayView, GameModel *GameM, ReplayModel *ReplayM)
    : QObject{parent}
{
    this->_MainView = MainView;
    this->_GameView = GameView;
    this->_ReplayView = ReplayView;
    this->_GameM = GameM;
    this->_ReplayM = ReplayM;

    /* View Connections */

    connect(this->_MainView, &MainWindow::NotifyUserAction, this, &GameController::MVHandleAction);
    connect(this->_GameView, &gamepage::NotifyUserAction, this, &GameController::GVHandleAction);
    connect(this->_ReplayView, &replaypage::NotifyUserAction, this, &GameController::RVHandleAction);

    connect(this, &GameController::ChangeMVPage, this->_MainView, &MainWindow::MoveOnPage);
    connect(this, &GameController::QuitApp, this->_MainView, &MainWindow::QuitApp);

    connect(this, &GameController::ChangeGVPage, this->_GameView, &gamepage::MoveOnPage);

    connect(this, &GameController::ChangeRVPage, this->_ReplayView, &replaypage::MoveOnPage);

    /* Model Connections */

    connect(this, &GameController::ChooseMapFile, this->_GameM, &GameModel::SelectMapFile);
    connect(this, &GameController::ChooseReplayFile, this->_ReplayM, &ReplayModel::SelectReplayFile);
}


GameController::~GameController()
{

}


void GameController::MVHandleAction(MVActionCode code)
{
    switch (code) {
    case MVActionCode::CLICKED_BUTTON_GAME:
        emit ChangeMVPage(MVPageCode::GAME_LOBBY);
        break;
    case MVActionCode::CLICKED_BUTTON_REPLAY:
        emit ChangeMVPage(MVPageCode::REPLAY_LOBBY);
        break;
    case MVActionCode::CLICKED_BUTTON_QUIT:
        emit QuitApp();
        break;
    default:
        break;
    }
}


void GameController::GVHandleAction(GVActionCode code)
{
    switch (code) {
    case GVActionCode::CLICKED_BUTTON_PLAYGAME:
        emit ChangeGVPage(GVPageCode::PLAY_GAME);
        break;
    case GVActionCode::CLICKED_BUTTON_EXIT:
        emit ChangeGVPage(GVPageCode::GAME_LOBBY);
        break;
    case GVActionCode::CLICKED_BUTTON_CONTINUE:
        emit ChangeGVPage(GVPageCode::GAME_LOBBY);
        break;
    case GVActionCode::CLICKED_BUTTON_BACK:
        emit ChangeGVPage(GVPageCode::HOME);
        break;
    case GVActionCode::CLICKED_BUTTON_CHOOSEMAP:
        emit ChooseMapFile();
        break;
    default:
        break;
    }
}


void GameController::RVHandleAction(RVActionCode code)
{
    switch (code) {
    case RVActionCode::CLICKED_BUTTON_REPLAYGAME:
        emit ChangeRVPage(RVPageCode::REPLAY_GAME);
        break;
    case RVActionCode::CLICKED_BUTTON_EXIT:
        emit ChangeRVPage(RVPageCode::REPLAY_LOBBY);
        break;
    case RVActionCode::CLICKED_BUTTON_BACK:
        emit ChangeRVPage(RVPageCode::HOME);
        break;
    case RVActionCode::CLICKED_BUTTON_CHOOSEREPLAY:
        emit ChooseReplayFile();
        break;
    default:
        break;
    }
}


