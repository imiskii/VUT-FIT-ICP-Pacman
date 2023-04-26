#include "gamecontroller.h"


GameController::GameController(QObject *parent, MainWindow *MainView, gamepage *GameView, replaypage *ReplayView)
    : QObject{parent}
{
    this->_MainView = MainView;
    this->_GameView = GameView;
    this->_ReplayView = ReplayView;

    connect(this->_MainView, &MainWindow::NotifyUserAction, this, &GameController::MVHandleAction);
    connect(this->_GameView, &gamepage::NotifyUserAction, this, &GameController::GVHandleAction);
    connect(this->_ReplayView, &replaypage::NotifyUserAction, this, &GameController::RVHandleAction);

    connect(this, &GameController::ChangeMVPage, this->_MainView, &MainWindow::MoveOnPage);
    connect(this, &GameController::QuitApp, this->_MainView, &MainWindow::QuitApp);

    connect(this, &GameController::ChangeGVPage, this->_GameView, &gamepage::MoveOnPage);

    connect(this, &GameController::ChangeRVPage, this->_ReplayView, &replaypage::MoveOnPage);
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
        emit ChangeGVPage(GVPageCode::GAME_EXIT);
        break;
    case GVActionCode::CLICKED_BUTTON_CONTINUE:
        emit ChangeGVPage(GVPageCode::GAME_EXIT);
        break;
    case GVActionCode::CLICKED_BUTTON_BACK:
        emit ChangeGVPage(GVPageCode::HOME);
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
        emit ChangeRVPage(RVPageCode::REPLAY_EXIT);
        break;
    case RVActionCode::CLICKED_BUTTON_BACK:
        emit ChangeRVPage(RVPageCode::HOME);
        break;
    default:
        break;
    }
}


