/**
 * @file ReplayModel.h
 * @author
 * @brief header file for ReplayModel.cpp
 * 
 */

#ifndef REPLAYMODEL_H
#define REPLAYMODEL_H

#include <QObject>
#include <QFileDialog>
#include "../View/replaypage.h"
#include "FileLoader.h"

class ReplayModel : public QObject
{
    Q_OBJECT

public:
    explicit ReplayModel(QObject *parent = nullptr, replaypage *ReplayModel = nullptr);
    ~ReplayModel();


private:
    replaypage *_ReplayView; ///< Replay View


signals:
    /**
     * @brief AddReplayToCombobox notify View to update combobox with available replays
     * @param replayName name of replay
     */
    void AddReplayToCombobox(QString replayName);


public slots:
    /**
     * @brief SelectReplayFile open File Dialog to choose replay file and notify view to display it
     */
    void SelectReplayFile();

};

#endif // REPLAYMODEL_H


/* END OF FILE */