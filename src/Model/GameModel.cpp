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

    connect(this, &GameModel::AddMapNameToCombobox, this->_GameView, &gamepage::AddMapName);
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
