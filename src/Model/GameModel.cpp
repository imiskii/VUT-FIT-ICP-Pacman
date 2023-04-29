/**
 * @file GameModel.cpp
 * @author Michal Ľaš (xlasmi00)
 * @brief Game Model
 * 
 */

#include "GameModel.h"


GameModel::GameModel(QObject *parent, gamepage *GameView)
    : QObject{parent}
{
    this->_GameView = GameView;
    this->_Map = GameMap();
    this->_Pacman = Pacman();

    connect(this, &GameModel::AddMapNameToCombobox, this->_GameView, &gamepage::AddMapName);
    connect(this, &GameModel::DisplayMap, this->_GameView, &gamepage::ShowGameField);
    connect(this, &GameModel::DisplayMessage, this->_GameView, &gamepage::ShowMessage);
    connect(this, &GameModel::ChangePage, this->_GameView, &gamepage::MoveOnPage);
    connect(this, &GameModel::ChangePacmanPosition, this->_GameView, &gamepage::UpdatePacmanPosition);

    // Load map names
    for (auto& item : LoadFileNamesFromDir("../../examples/maps", "txt"))
    {
        emit AddMapNameToCombobox(QString::fromStdString(item));
    }
}


GameModel::~GameModel()
{

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
    if (!map.contains("/")) // it is not full path
    {
        map = "../../examples/maps/" + map + ".txt";
    }

    std::vector<std::string> fileLines;
    // Read lines from map file
    if (!ReadLinesFromFile(fileLines, map.toLocal8Bit().constData())) // reading operation failed
    {
        emit DisplayMessage("Unable to find given map file !");
        return;
    }

    if (!this->_Map.loadMap(fileLines))
    {
        emit DisplayMessage("The map file is corrupted !");
        return;
    }

    emit DisplayMap(this->_Map.getMapField());
    emit ChangePage(GVPageCode::PLAY_GAME);

}


void GameModel::MovePacman(direction dr)
{
    emit ChangePacmanPosition(dr);
}
