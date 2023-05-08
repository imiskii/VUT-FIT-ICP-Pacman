/**
 * @file GameModel.h
 * @author Michal Ľaš (xlasmi00), Adam Lazík (xlazik00) [MoveGhosts, GetFreeNeighbors]
 * @brief header file for GameModel.cpp
 *
 */

#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QObject>
#include <QFileDialog>
#include <vector>
#include <utility>
#include <QTimer>
#include <QThread>
#include <ctime>
#include <string>
#include "../consts.h"
#include "../View/gamepage.h"
#include "FileLoader.h"
#include "GameMap.h"
#include "Entity.h"
#include "Logger.h"

using namespace std;


class GameModel : public QObject
{
    Q_OBJECT

public:
    explicit GameModel(QObject *parent = nullptr, gamepage *GameView = nullptr);
    ~GameModel();
    int getGhostSpeed();

private:
    unsigned short _gameLevel;      ///< Current level of the game
    gamepage *_GameView;            ///< Game View
    GameMap *_Map;                  ///< Game map/field
    Entity *_Pacman;                ///< object representing pacman
    vector<Entity> Ghosts;          ///< vector of ghost positions in model
    int _PacmanSpeed;               ///< pacman transition time to a new field in milliseconds
    int _GhostsSpeed;               ///< ghosts transition time to a new field in milliseconds
    vector<pair<int, int>> _keysPos;///< positions of keys in map
    QTimer GhostTimer;              ///< timer controlling ghost movement
    Logger logger;                  ///< for logging games
    int _score;                     ///< counting player score
    int _lives;                     ///< player lives

    /**
     * @brief update given position (x,y) based on given direction
     * @param dr direction
     * @param x reference to x position
     * @param y reference to y position
     */
    void _setNewPosition(direction dr, int &x, int &y);

    /**
     * @brief check if on given position is key or target point. If there is key or target point it call next actions
     * @param x position
     * @param y position
     */
    void _checkPosition(int x, int y);

    /**
     * @brief determine free positions next to specified
     * position. Free positions are considered those without a wall.
     * @param x x coordinate
     * @param y y coordinate
     * @return vector<pair<int, int>> vector of free neighboring positions
     */
    vector<pair<int, int>> GetFreeNeighbors(int x, int y);

signals:
    /**
     * @brief notify View to update combobox with available maps
     * @param mapFile name of map
     */
    void AddMapNameToCombobox(QString mapFile);

    /**
     * @brief notify View to display game field
     * @param gameField 2D array - representation of game field
     */
    void DisplayMap(std::vector<std::vector<char>> &gameField);

    /**
     * @brief notify view to display message
     * @param msg Message to be displayed
     */
    void DisplayMessage(QString msg);

    /**
     * @brief notify Game View to change page
     * @param page to change to
     */
    void ChangePage(GVPageCode page);

    /**
     * @brief notify Game View to change pacman position on map
     * @param dr direction where should pacman move
     */
    void ChangePacmanPosition(direction dr, int speed);

    /**
     * @brief continue in next/currnet pacman movement
     * @param dr direction where should pacman move
     */
    void ChangeGhostPositions(vector<pair<int, int>> &newpos, int speed);

    /**
     * @brief signal next pacman move
     * @param dr move direction
     */
    void NextMove(direction dr);

    /**
     * @brief notify Game View that KeyItem with given index was collected
     * @param index index of collected item
     */
    void KeyCollected(int index);

    /**
     * @brief notify Game View to delete current scene
     */
    void DeleteMap();

    /**
     * @brief signal PacMan encounter with a ghost
     */
    void Death();

    /**
     * @brief update currently achieved score
     * @param score new score
     */
    void updateScore(int score);

    void updateLives(int Lives);

public slots:

    /**
     * @brief open File Dialog to choose map file and notify view to display it
     */
    void SelectMapFile();

    /**
     * @brief Load given map and notify View to display it
     * @param map map to be loaded
     */
    void BuildMap(QString map);

    /**
     * @brief move pacman object to given direction
     * @param dr direction where should pacman move
     */
    void MovePacman(direction dr);

    /**
     * @brief call another move signal for pacman if last pacman movement was finished
     */
    void KeepPacmanMoving();

    /**
     * @brief leave the current game
     */
    void LeaveGame();

    /**
     * @brief proceed to the next level (same map, higher entity speed)
     */
    void GoOnNextLevel();

    /**
     * @brief Determine new positions for ghosts
     */
    void MoveGhosts();
};

#endif // GAMEMODEL_H


/* END OF FILE */
