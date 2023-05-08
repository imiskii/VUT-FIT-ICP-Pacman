/**
 * @file ReplayModel.cpp
 * @author Adam Lazík (xlazik00)
 * @brief Replay Model
 *
 */

#include "ReplayModel.h"

ReplayModel::ReplayModel(QObject *parent, replaypage *ReplayView)
    : QObject{parent}
{
    this->_ReplayView = ReplayView;
    _Map = nullptr;

    connect(this, &ReplayModel::AddReplayToCombobox, this->_ReplayView, &replaypage::AddReplayName);
    // Load map names
    for (auto& item : LoadFileNamesFromDir("../../logs", "txt"))
    {
        emit AddReplayToCombobox(QString::fromStdString(item));
    }


    connect(this, &ReplayModel::DisplayMap, this->_ReplayView, &replaypage::ShowGameField);
    connect(this, &ReplayModel::ChangePage, this->_ReplayView, &replaypage::MoveOnPage);
    connect(this, &ReplayModel::ChangePacmanPosition, this->_ReplayView, &replaypage::UpdatePacmanPosition);

    connect(&GhostTimer, &QTimer::timeout, this, &ReplayModel::MoveGhosts);
}


ReplayModel::~ReplayModel()
{

}


void ReplayModel::SelectReplayFile()
{
    QString fileName = QFileDialog::getOpenFileName(this->_ReplayView, "Choose Replay File", QDir::homePath(), "*.txt");
    if (!fileName.isEmpty())
    {
        emit AddReplayToCombobox(fileName);
    }
}


void ReplayModel::BuildMap(QString map)
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
            map = "../../logs/" + map + "." + _MAP_REPLAY_FILE_EXT;
        }

        // Read lines from map file
        if (!ReadLinesFromFile(_game, map.toLocal8Bit().constData())) // reading operation failed
        {
            cerr << "Unable to find given map file !" << endl;
            return;
        }

        if (!this->_Map->loadMap(_game, mapName))
        {
            cerr << "The map file is corrupted !" << endl;
            return;
        }
    }

    MapItems itemsPos = this->_Map->getMapItems();
    this->_Pacman = new Entity(itemsPos.startPos.first, itemsPos.startPos.second);
    for (size_t i = 0; i < itemsPos.ghostsPos.size(); ++i) {
        auto &ghost = itemsPos.ghostsPos[i];
        Entity GhostModel(ghost.first, ghost.second);
        GhostModel.assignNumber(i);
        Ghosts.push_back(GhostModel);
    }
    this->_keysPos = itemsPos.keysPos;

    emit DisplayMap(this->_Map->getMapField());
    emit ChangePage(RVPageCode::REPLAY_GAME);

    _index = stoi(_game[0].substr(0, _game[0].find(' '))) + 1; // line with first instruction
    _PacmanSpeed = _GhostsSpeed = stoi(_game[_index++]); // extract entity speed

    GhostTimer.setInterval(_GhostsSpeed + 15);

    GhostTimer.start();
}

direction ReplayModel::directionDecode(char d)
{
    switch(d)
    {
    case 'U':
        return UP;
    case 'D':
        return DOWN;
    case 'L':
        return LEFT;
    case 'R':
        return RIGHT;
    default:
        return NONE;
    }
}

void ReplayModel::MoveGhosts()
{
    while (_index < _game.size())
    {
        string &line = _game[_index];
        string tmp;
        switch(line[0])
        {
        case 'P':
            emit ChangePacmanPosition(directionDecode(line[3]), _PacmanSpeed);
            break;
        case 'T':
            ++_index;
            return;
        }
        ++_index;
    }
    GhostTimer.stop();
}

/* END OF FILE */
