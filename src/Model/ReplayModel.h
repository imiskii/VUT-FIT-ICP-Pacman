/**
 * @file ReplayModel.h
 * @author Adam Lazík (xlazik00)
 * @brief header file for ReplayModel.cpp
 *
 */

#ifndef REPLAYMODEL_H
#define REPLAYMODEL_H

#include <QObject>
#include <QFileDialog>
#include <iostream>
#include <sstream>
#include <QTimer>
#include "../View/replaypage.h"
#include "FileLoader.h"
#include "GameMap.h"
#include "Entity.h"

class ReplayModel : public QObject
{
    Q_OBJECT

public:
    explicit ReplayModel(QObject *parent = nullptr, replaypage *ReplayModel = nullptr);
    ~ReplayModel();


private:
    replaypage *_ReplayView; ///< Replay View
    GameMap *_Map; ///< Game Map
    Entity *_Pacman;
    vector<Entity> Ghosts;          ///< vector of ghost positions in model
    int _PacmanSpeed;               ///< pacman transition time to a new field in milliseconds
    int _GhostsSpeed;               ///< ghosts transition time to a new field in milliseconds
    vector<pair<int, int>> _keysPos;///< positions of keys in map
    vector<string> _game;           ///< loaded log file of the game
    stringstream _moves;            ///< logged moves loaded from the log
    QTimer GhostTimer;              ///< timer controlling ghost movement
    size_t _index;                  ///< index to line in log file

    direction directionDecode(char d);

signals:
    /**
     * @brief notify View to update combobox with available replays
     * @param replayName name of replay
     */
    void AddReplayToCombobox(QString replayName);

    /**
     * @brief notify View to display game field
     * @param gameField 2D array - representation of game field
     */
    void DisplayMap(std::vector<std::vector<char>> &gameField);

    /**
     * @brief notify Game View to change page
     * @param page to change to
     */
    void ChangePage(RVPageCode page);

    void ChangePacmanPosition(direction d, int speed);


public slots:
    /**
     * @brief open File Dialog to choose replay file and notify view to display it
     */
    void SelectReplayFile();

    void BuildMap(QString map);

    void MoveGhosts();

};

#endif // REPLAYMODEL_H


/* END OF FILE */
