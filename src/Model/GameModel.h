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
#include "../View/gamepage.h"
#include "FileLoader.h"
#include "GameMap.h"
#include "Pacman.h"

class GameModel : public QObject
{
    Q_OBJECT

public:
    explicit GameModel(QObject *parent = nullptr, gamepage *GameView = nullptr);
    ~GameModel();


private:
    gamepage *_GameView; //< Game View
    GameMap _Map;         //< Game map/field
    Pacman _Pacman;       //< object representing pacman


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
    void ChangePacmanPosition(direction dr);


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

};

#endif // GAMEMODEL_H
