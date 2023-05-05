/**
 * @file gamecontroller.h
 * @author Michal Ľaš (xlasmi00)
 * @brief controller for pacman game - handeling view signals and user input
 *
 */


#include "gamecontroller.h"


GameController::GameController(QObject *parent, MainWindow *MainView, gamepage *GameView, replaypage *ReplayView, GameModel *GameM, ReplayModel *ReplayM)
    : QObject{parent}
{
    this->_MainView = MainView;
    this->_GameView = GameView;
    this->_ReplayView = ReplayView;
    this->_GameM = GameM;
    this->_ReplayM = ReplayM;

    this->_MainView->installEventFilter(this);

    /* View Connections */

    connect(this->_MainView, &MainWindow::NotifyUserAction, this, &GameController::MVHandleAction);
    connect(this->_GameView, &gamepage::NotifyUserAction, this, &GameController::GVHandleAction);
    connect(this->_GameView, &gamepage::PlayButtonClicked, this, &GameController::PlayButtonAction);
    connect(this->_ReplayView, &replaypage::NotifyUserAction, this, &GameController::RVHandleAction);

    connect(this, &GameController::ChangeMVPage, this->_MainView, &MainWindow::MoveOnPage);
    connect(this, &GameController::QuitApp, this->_MainView, &MainWindow::QuitApp);

    connect(this, &GameController::ChangeGVPage, this->_GameView, &gamepage::MoveOnPage);

    connect(this, &GameController::ChangeRVPage, this->_ReplayView, &replaypage::MoveOnPage);

    /* Model Connections */

    connect(this, &GameController::ChooseMapFile, this->_GameM, &GameModel::SelectMapFile);
    connect(this, &GameController::StartGame, this->_GameM, &GameModel::BuildMap);
    connect(this, &GameController::MoveAction, this->_GameM, &GameModel::MovePacman);
    connect(this, &GameController::ExitGame, this->_GameM, &GameModel::LeaveGame);
    connect(this, &GameController::NextGame, this->_GameM, &GameModel::GoOnNextLevel);
    connect(this, &GameController::ChooseReplayFile, this->_ReplayM, &ReplayModel::SelectReplayFile);
}


GameController::~GameController()
{

}


bool GameController::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        this->_KeyPressEvent(keyEvent);
    }
    return QObject::eventFilter(obj, event);
}


void GameController::_KeyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_W:
    case Qt::Key_Up:
        emit MoveAction(direction::UP);
        break;
    case Qt::Key_A:
    case Qt::Key_Left:
        emit MoveAction(direction::LEFT);
        break;
    case Qt::Key_S:
    case Qt::Key_Down:
        emit MoveAction(direction::DOWN);
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
        emit MoveAction(direction::RIGHT);
        break;
    default:
        break;
    }
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
    case GVActionCode::CLICKED_BUTTON_EXIT:
        emit ExitGame();
        break;
    case GVActionCode::CLICKED_BUTTON_NEXTLEVEL:
        emit NextGame();
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


void GameController::PlayButtonAction(QString choosenMap)
{
    emit StartGame(choosenMap);
}


/* END OF FILE */
