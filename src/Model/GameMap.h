/**
 * @file GameMap.h
 * @author Michal Ľaš (xlasmi00)
 * @brief header file for GameMap.cpp
 *
 */

#ifndef GAMEMAP_H
#define GAMEMAP_H


#include <vector>
#include <string>
#include <sstream>
#include <utility>

using namespace std;


/**
 * @brief The MapItems structure for positions of important map items
 */
struct MapItems
{
    pair<int, int> startPos;
    pair<int, int> targetPos;
    vector<pair<int, int>> keysPos;
    vector<pair<int, int>> ghostsPos;
};


/**
 * @brief The GameMap class representing map field
 */
class GameMap
{
public:
    GameMap();
    ~GameMap();

    /**
     * @brief load and process game map
     * @param fileLines reference to vector with loaded lines from map file
     * @return True if map was successfuly loaded or False if map file is corrupted
     */
    bool loadMap(vector<string> &fileLines, string mapName);

    /**
     * @brief getter for count of map field columns
     * @return number of map columns
     */
    int getCols() const;

    /**
     * @brief getter for count of map field rows
     * @return number of map rows
     */
    int getRows() const;

    /**
     * @brief getter for map field
     * @return 2D array - map field
     */
    vector<vector<char>> &getMapField();

    /**
     * @brief get positions of items in map
     * @return structure with positions of items in map
     */
    MapItems &getMapItems();

    /**
     * @brief get map name
     * @return name of map that was loaded
     */
    string getMapName();

    /**
     * @brief check if on given position of field is wall
     * @param x column
     * @param y row
     * @return True if there is wall or False if there is something else or given position is out of map field
     */
    bool isWall(int x, int y);

    /**
     * @brief check what is on given position
     * @param x column
     * @param y row
     * @return character that represents item on given position if given position is out of map field it returns space char (' ')
     */
    char isOnPosition(int x, int y);

private:
    string _mapName;                ///< name of map
    MapItems _itemsInMap;           ///< structure with positions of important map items
    int _rows;                      ///< number of map rows
    int _cols;                      ///< number of map columns
    vector<vector<char>> _field;    ///< 2D array representig map field

};

#endif // GAMEMAP_H


/* END OF FILE */
