/**
 * @file ReplayModel.cpp
 * @author 
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
    for (auto& item : LoadFileNamesFromDir("../../examples/replays", "txt"))
    {
        emit AddReplayToCombobox(QString::fromStdString(item));
    }
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


/* END OF FILE */