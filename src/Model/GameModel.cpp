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
    // @TODO: Load map
    // @TODO: emit signal to View to display it or emit signal that there is a problem

    if (!map.contains("/")) // it is not full path
    {
        map = "../../examples/maps/" + map + ".txt";
    }

    if (!this->_Map.loadMap(map.toLocal8Bit().constData()))
    {
        emit DisplayMessage("The map file is corrupted !");
        return;
    }

    std::vector<std::vector<char>> mapField = this->_Map.getMapField();

    emit DisplayMap(mapField);
    emit ChangePage(GVPageCode::PLAY_GAME);

}
