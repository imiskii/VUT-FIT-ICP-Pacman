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
#include <QPoint>

using namespace std;


class GameMap
{
public:
    GameMap();
    ~GameMap();
    /**
     * @brief loadMap load and process game map
     * @param fileLines reference to vector with loaded lines from map file
     * @return True if map was successfuly loaded or False if map file is corrupted
     */
    bool loadMap(vector<string> &fileLines);
    /**
     * @brief getCols getter for count of map field columns
     * @return number of map columns
     */
    int getCols() const;
    /**
     * @brief getRows getter for count of map field rows
     * @return number of map rows
     */
    int getRows() const;
    /**
     * @brief getMapField getter for map field
     * @return reference to map field
     */
    vector<vector<char>> &getMapField();


private:
    QPointF _StartPos;
    vector<QPointF> _gostPos;
    int _rows;
    int _cols;
    vector<vector<char>> _field;

};

#endif // GAMEMAP_H
