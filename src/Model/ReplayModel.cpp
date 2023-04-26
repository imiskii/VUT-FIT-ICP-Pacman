#include "ReplayModel.h"

ReplayModel::ReplayModel(QObject *parent, replaypage *ReplayView)
    : QObject{parent}
{
    this->_ReplayView = ReplayView;
}


ReplayModel::~ReplayModel()
{

}
