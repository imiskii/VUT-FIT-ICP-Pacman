/**
 * @file GameModel.h
 * @author Michal Ľaš (xlasmi00)
 * @brief header file for GameModel.cpp
 * 
 */

#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QObject>
#include <QFileDialog>
#include <vector>
#include <utility>
#include "../consts.h"
#include "../View/gamepage.h"
#include "FileLoader.h"
#include "GameMap.h"
#include "Pacman.h"


using namespace std;


class GameModel : public QObject
{
    Q_OBJECT

public:
    explicit GameModel(QObject *parent = nullptr, gamepage *GameView = nullptr);
    ~GameModel();


private:
    unsigned short _gameLevel;      ///< Current level of the game
    gamepage *_GameView;            ///< Game View
    GameMap *_Map;                  ///< Game map/field
    Pacman *_Pacman;                ///< object representing pacman
    int _PacmanSpeed;               ///< pacman transition time to a new field in milliseconds
    int _GhostsSpeed;               ///< ghosts transition time to a new field in milliseconds
    vector<pair<int, int>> _keysPos;///< positions of keys in map


    /**
     * @brief _setNewPosition update given position (x,y) based on given direction
     * @param dr direction
     * @param x reference to x position
     * @param y reference to y position
     */
    void _setNewPosition(direction dr, int &x, int &y);
    /**
     * @brief _checkPosition check if on given position is key or target point. If there is key or target point it call next actions
     * @param x position
     * @param y position
     */
    void _checkPosition(int x, int y);


signals:
    /**
     * @brief AddMapNameToCombobox notify View to update combobox with available maps
     * @param mapFile name of map
     */
    void AddMapNameToCombobox(QString mapFile);
    /**
     * @brief DisplayMap notify View to display game field
     * @param gameField 2D array - representation of game field
     */
    void DisplayMap(std::vector<std::vector<char>> &gameField);
    /**
     * @brief DisplayMessage notify view to display message
     * @param msg Message to be displayed
     */
    void DisplayMessage(QString msg);
    /**
     * @brief DisplayPage notify Game View to change page
     * @param page to change to
     */
    void ChangePage(GVPageCode page);
    /**
     * @brief ChangePacmanPosition notify Game View to change pacman position on map
     * @param dr direction where should pacman move
     */
    void ChangePacmanPosition(direction dr, int speed);
    /**
     * @brief NextMove continue in next/currnet pacman movement
     * @param dr direction where should pacman move
     */
    void NextMove(direction dr);
    /**
     * @brief KeyCollected notify Game View that KeyItem with given index was collected
     * @param index index of collected item
     */
    void KeyCollected(int index);
    /**
     * @brief DeleteMap notify Game View to delete current scene
     */
    void DeleteMap();


public slots:
    /**
     * @brief SelectMapFile open File Dialog to choose map file and notify view to display it
     */
    void SelectMapFile();
    /**
     * @brief BuildMap Load given map and notify View to display it
     * @param map map to be loaded
     */
    void BuildMap(QString map);
    /**
     * @brief MovePacman move pacman object to given direction
     * @param dr direction where should pacman move
     */
    void MovePacman(direction dr);
    /**
     * @brief KeepPacmanMoving call another move signal for pacman if last pacman movement was finished
     */
    void KeepPacmanMoving();
    void LeaveGame();
    void GoOnNextLevel();

};

#endif // GAMEMODEL_H


/* END OF FILE */