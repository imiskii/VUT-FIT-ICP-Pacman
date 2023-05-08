/**
 * @file GameModel.cpp
 * @author Michal Ľaš (xlasmi00), Adam Lazik (xlazik00)
 * @brief Game Model
 *
 */

#include "GameModel.h"

GameModel::GameModel(QObject *parent, gamepage *GameView)
    : QObject{parent}
{
    this->_GameView = GameView;
    this->_Map = nullptr;
    this->_Pacman = nullptr;
    this->_gameLevel = 1;
    this->_PacmanSpeed = LEVEL_1_SPEED;
    this->_GhostsSpeed = LEVEL_1_SPEED;
    _score = 0;
    _lives = 3;

    // Animation needs 15 extra miliseconds to finish and be ready for the next movement
    GhostTimer.setInterval(_GhostsSpeed + 15);
    connect(&GhostTimer, &QTimer::timeout, this, &GameModel::MoveGhosts);

    connect(this, &GameModel::AddMapNameToCombobox, this->_GameView, &gamepage::AddMapName);
    connect(this, &GameModel::DisplayMap, this->_GameView, &gamepage::ShowGameField);
    connect(this, &GameModel::DisplayMessage, this->_GameView, &gamepage::ShowMessage);
    connect(this, &GameModel::ChangePage, this->_GameView, &gamepage::MoveOnPage);
    connect(this, &GameModel::ChangePacmanPosition, this->_GameView, &gamepage::UpdatePacmanPosition);
    connect(this, &GameModel::NextMove, this, &GameModel::MovePacman);
    connect(this, &GameModel::KeyCollected, this->_GameView, &gamepage::deleteKeyFromMap);
    connect(this, &GameModel::DeleteMap, this->_GameView, &gamepage::deleteScene);
    connect(this->_GameView, &gamepage::PacmanMoveFinished, this, &GameModel::KeepPacmanMoving);
    connect(this, &GameModel::ChangeGhostPositions, _GameView, &gamepage::updateGhostPositions);
    connect(this, &GameModel::Death, _GameView, &gamepage::PacManDeath);
    connect(this, &GameModel::updateScore, _GameView, &gamepage::updateScore);

    srand(time(nullptr)); // seed randomized ghost movement

    // Load map names
    for (auto& item : LoadFileNamesFromDir(_MAP_FILES, _MAP_REPLAY_FILE_EXT))
    {
        emit AddMapNameToCombobox(QString::fromStdString(item));
    }
}


GameModel::~GameModel()
{
    delete this->_Map;
    delete this->_Pacman;
}


void GameModel::SelectMapFile()
{
    QString fileName = QFileDialog::getOpenFileName(this->_GameView, "Choose Map File", QDir::homePath(), "*.txt");
    if (!fileName.isEmpty())
    {
        emit AddMapNameToCombobox(fileName);
    }
}


void GameModel::BuildMap(QString map)
{
    if (this->_Map == nullptr)
    {
        this->_Map = new GameMap();
    }

    string mapName = map.toStdString();
    // check if map is not already loaded
    if (!(mapName == this->_Map->getMapName())) // if different map is loaded
    {
        // delete old map
        delete this->_Map;
        this->_Map = new GameMap();

        if (!map.contains("/")) // it is not full path
        {
            map = _MAP_FILES + map + "." + _MAP_REPLAY_FILE_EXT;
        }

        std::vector<std::string> fileLines;
        // Read lines from map file
        if (!ReadLinesFromFile(fileLines, map.toLocal8Bit().constData())) // reading operation failed
        {
            emit DisplayMessage("Unable to find given map file !");
            return;
        }

        if (!this->_Map->loadMap(fileLines, mapName))
        {
            emit DisplayMessage("The map file is corrupted !");
            return;
        }

        logger.createLogFile(fileLines);
    }

    MapItems itemsPos = this->_Map->getMapItems();
    this->_Pacman = new Entity(itemsPos.startPos.first, itemsPos.startPos.second);
    logger.log("P " + to_string(_Pacman->x()) + " " + to_string(_Pacman->y()));
    for (size_t i = 0; i < itemsPos.ghostsPos.size(); ++i) {
        auto &ghost = itemsPos.ghostsPos[i];
        Entity GhostModel(ghost.first, ghost.second);
        GhostModel.assignNumber(i);
        logger.log("G " + to_string(i) + " " + to_string(ghost.first) + " " + to_string(ghost.second));
        Ghosts.push_back(GhostModel);
    }
    this->_keysPos = itemsPos.keysPos;

    emit DisplayMap(this->_Map->getMapField());
    emit ChangePage(GVPageCode::PLAY_GAME);
    GhostTimer.start();
}


void GameModel::MovePacman(direction dr)
{
    direction currentPacmanDirection = this->_Pacman->getCurrDirection();
    if (!_Pacman->isMovable())
    {
        return; // PacMan cannot move after death
    }
    // check if pacman is moving
    if (this->_Pacman->isMoving())
    {
        // save next change
        this->_Pacman->setNextDirection(dr);
        // if it is a direction change
        if (currentPacmanDirection != dr)
        {
            // immediate change if the movement is opposite to the current movement direction
            // opposite directions are assigned opposite numbers, resulting in 0
            // when adding them
            if (currentPacmanDirection + dr == 0)
            {
                this->_Pacman->setCurrDirection(dr);
                this->_Pacman->setNextDirection(direction::NONE);
                int t_x = this->_Pacman->next_x();
                int t_y = this->_Pacman->next_y();
                this->_setNewPosition(dr, t_x, t_y);
                this->_Pacman->setNextPos(t_x, t_y);
                emit ChangePacmanPosition(dr, this->_PacmanSpeed);
            }
        }
    }
    // start new movement
    else
    {
        // check if it possible to move to given direction
        int t_x = this->_Pacman->x();
        int t_y = this->_Pacman->y();
        this->_setNewPosition(dr, t_x, t_y);
        if (!this->_Map->isWall(t_x, t_y))
        {
            // reset next direction if movement to next direction was successful
            if (dr == this->_Pacman->getNextDirection())
                this->_Pacman->setNextDirection(direction::NONE);
            this->_Pacman->setCurrDirection(dr);
            this->_Pacman->setNextPos(t_x, t_y);
            this->_Pacman->setMoving(true);
            emit ChangePacmanPosition(dr, this->_PacmanSpeed);
        }
        // try to move it in current direction
        else
        {
            t_x = this->_Pacman->x();
            t_y = this->_Pacman->y();
            this->_setNewPosition(currentPacmanDirection, t_x, t_y);
            if (!this->_Map->isWall(t_x, t_y) && currentPacmanDirection != NONE)
            {
                this->_Pacman->setNextPos(t_x, t_y);
                this->_Pacman->setMoving(true);
                emit ChangePacmanPosition(currentPacmanDirection, this->_PacmanSpeed);
            }
            else
            {
                // reset next direction because pacman stops
                this->_Pacman->setNextDirection(direction::NONE);
            }
        }
    }
}


void GameModel::KeepPacmanMoving()
{
    // write new positionthis->_Pacman->setMoving(false);
    this->_Pacman->setCurrPos(this->_Pacman->next_x(), this->_Pacman->next_y());
    this->_checkPosition(this->_Pacman->x(), this->_Pacman->y());
    this->_Pacman->setMoving(false);
    if (this->_Pacman->getNextDirection() != direction::NONE)
    {
        emit NextMove(this->_Pacman->getNextDirection());
    }
    else
    {
        emit NextMove(this->_Pacman->getCurrDirection());
    }
}


void GameModel::_setNewPosition(direction dr, int &x, int &y)
{
    switch (dr)
    {
    case direction::DOWN:
        y += 1;
        break;
    case direction::LEFT:
        x -= 1;
        break;
    case direction::RIGHT:
        x += 1;
        break;
    case direction::UP:
        y -= 1;
        break;
    default:
        break;
    }
}


void GameModel::_checkPosition(int x, int y)
{
    char item = this->_Map->isOnPosition(x, y);

    if (item == 'K')
    {
        auto it = std::find(this->_keysPos.begin(), this->_keysPos.end(), std::pair(x, y));
        if (it != _keysPos.end())
        {
            int index = std::distance(this->_keysPos.begin(), it);
            this->_keysPos.erase(this->_keysPos.begin() + index);
            emit KeyCollected(index);
        }
    }
    else if (item == 'T' && this->_keysPos.empty())
    {
        // Game ends
        _score += 1;
        emit updateScore(_score);
        emit ChangePage(GVPageCode::GAME_END);
    }
}


void GameModel::LeaveGame()
{
    GhostTimer.stop();
    delete this->_Pacman;
    this->_PacmanSpeed = LEVEL_1_SPEED;
    this->_GhostsSpeed = LEVEL_1_SPEED;
    this->_gameLevel = 1;
    // Animation needs 15 extra miliseconds to finish and be ready for the next movement
    GhostTimer.setInterval(_GhostsSpeed + 15);
    emit DeleteMap();
    emit ChangePage(GVPageCode::GAME_LOBBY);
}


void GameModel::GoOnNextLevel()
{
    GhostTimer.stop();
    if (this->_gameLevel <= MAX_GAME_LEVEL)
    {
        this->_PacmanSpeed -= LEVEL_DIFF;
        this->_GhostsSpeed -= LEVEL_DIFF;
        // Animation needs 15 extra miliseconds to finish and be ready for the next movement
        GhostTimer.setInterval(_GhostsSpeed + 15);
    }

    MapItems itemsPos = this->_Map->getMapItems();
    this->_Pacman = new Entity(itemsPos.startPos.first, itemsPos.startPos.second);
    Ghosts.clear();
    for (auto &ghost: itemsPos.ghostsPos) {
        Ghosts.push_back(Entity(ghost.first, ghost.second));
    }
    this->_keysPos = itemsPos.keysPos;
    emit DeleteMap();
    emit DisplayMap(this->_Map->getMapField());
    emit ChangePage(GVPageCode::PLAY_GAME);
    GhostTimer.start();
}

vector<pair<int, int>> GameModel::GetFreeNeighbors(int x, int y)
{
    vector<pair<int, int>> freeNeighbors;
    for (auto pos: vector<pair<int, int>>{{x, y+1}, {x, y-1}, {x+1, y}, {x-1, y}})
    {
        if (!_Map->isWall(pos.first, pos.second))
        {
            freeNeighbors.push_back(pos);
        }
    }
    return freeNeighbors;
}

void GameModel::MoveGhosts()
{
    logger.log("T"); // Indicate that positions are in a new "tick"
    logger.log("P " + to_string(_Pacman->next_x()) + " " + to_string(_Pacman->next_y())); // log pacman movement together with ghost movement
    vector<pair<int ,int>> newpos;
    for(auto &ghost: Ghosts)
    {
        vector <pair<int, int>> freeNeighbors = GetFreeNeighbors(ghost.x(), ghost.y());
        int random_index = rand() % freeNeighbors.size();
        auto &newghostpos = freeNeighbors[random_index];
        ghost.setCurrPos(newghostpos.first, newghostpos.second);
        logger.log("G " + to_string(ghost.getNumber()) + " "
            + to_string(ghost.x()) + " " + to_string(ghost.y()));
        if(newghostpos == _Pacman->getCurrPos() || newghostpos == _Pacman->getNextPos())
        {
            _Pacman->setMovable(false);
            GhostTimer.stop();
            emit Death();

            QTimer::singleShot(2000, this, [=]() {
                _lives -= 1;
                emit updateLives(_lives);
                if (_lives == 0) {
                    _score = 0;
                    emit updateScore(_score);
                }
                MapItems itemsPos = this->_Map->getMapItems();
                delete this->_Pacman;
                this->_Pacman = new Entity(itemsPos.startPos.first, itemsPos.startPos.second);
                Ghosts.clear();
                for (auto &ghost: itemsPos.ghostsPos) {
                    Ghosts.push_back(Entity(ghost.first, ghost.second));
                }
                this->_keysPos = itemsPos.keysPos;
                emit DeleteMap();
                emit DisplayMap(this->_Map->getMapField());
                emit ChangePage(GVPageCode::PLAY_GAME);
                GhostTimer.start();
                _Pacman->setMovable(true);
            });
        }
        newpos.push_back(newghostpos);
    }
    emit ChangeGhostPositions(newpos, _GhostsSpeed);
}

/* END OF FILE */
