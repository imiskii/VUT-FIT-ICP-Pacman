/**
 * @file ReplayModel.cpp
 * @author Michal Las (xlasmi00)
 * @brief Replay Model
 *
 */

#include "ReplayModel.h"

ReplayModel::ReplayModel(QObject *parent, replaypage *ReplayView)
    : QObject{parent}
{
    this->_ReplayView = ReplayView;

    connect(this, &ReplayModel::AddReplayToCombobox, this->_ReplayView, &replaypage::AddReplayName);
    // Load map names
    for (auto& item : LoadFileNamesFromDir("../../logs", "txt"))
    {
        emit AddReplayToCombobox(QString::fromStdString(item));
    }


    connect(this, &ReplayModel::DisplayMap, this->_ReplayView, &replaypage::ShowGameField);
    connect(this, &ReplayModel::ChangePage, this->_ReplayView, &replaypage::MoveOnPage);
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

        std::vector<std::string> fileLines;
        // Read lines from map file
        if (!ReadLinesFromFile(fileLines, map.toLocal8Bit().constData())) // reading operation failed
        {
            cerr << "Unable to find given map file !" << endl;
            return;
        }

        if (!this->_Map->loadMap(fileLines, mapName))
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
}

/* END OF FILE */
