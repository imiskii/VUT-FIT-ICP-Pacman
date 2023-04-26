#include "GameModel.h"

GameModel::GameModel(QObject *parent, gamepage *GameView)
    : QObject{parent}
{
    this->_GameView = GameView;
}


GameModel::~GameModel()
{

}
