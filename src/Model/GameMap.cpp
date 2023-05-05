/**
 * @file GameMap.cpp
 * @author Michal Ľaš (xlasmi00)
 * @brief Class representing Game Map
 *
 */

#include "GameMap.h"


using namespace std;


GameMap::GameMap()
{
    this->_cols = 0;
    this->_rows = 0;
    this->_mapName = "";
    this->_itemsInMap.targetPos = pair<int, int>(-1,-1);
}


GameMap::~GameMap()
{

}


bool GameMap::loadMap(vector<string> &fileLines, string mapName)
{
    // set map name
    this->_mapName = mapName;
    // check empty file
    if (fileLines.size() == 0) // file has 0 lines, so file is empty
    {
        return false;
    }
    // get map size
    istringstream iss(fileLines.at(0));
    iss >> this->_rows >> this->_cols;
    // check values
    if (this->_rows == 0 || this->_cols == 0) // missing map size declaration of first line of the file
    {
        return false;
    }
    // check map rows
    if ((fileLines.size()-1) < this->_rows) // file has not enough lines for declared map size row count
    {
        return false;
    }
    // process map
    this->_field.reserve(this->_rows+2); // set size to avoid resizeing (+2 bcs. borders)
    // add top border
    vector<char> border(this->_cols+2, 'X');
    this->_field.push_back(border);
    // add map lines
    for (int i = 0; i < this->_rows; i++)
    {
        // check map columns
        if (fileLines.at(i+1).size() != this->_cols) // declared size of map column and size of line does not match
        {
            return false;
        }
        vector<char> line; // create temporary vector
        line.reserve(this->_cols+2); // set it size to avoid resizeing (+2 bcs. borders)
        // process one line of map
        istringstream iss(fileLines.at(i+1));
        for (int j = 0; j < this->_cols; j++)
        {
            // add left border
            if (j == 0)
                line.push_back('X');

            char c;
            iss >> c;

            switch (c)
            {
                case 'S':
                    this->_itemsInMap.startPos = pair<int, int>(j+1, i+1);
                    break;
                case 'G':
                    this->_itemsInMap.ghostsPos.push_back(pair<int, int>(j+1, i+1));
                    break;
                case 'K':
                    this->_itemsInMap.keysPos.push_back(pair<int, int>(j+1, i+1));
                    break;
                case 'T':
                    this->_itemsInMap.targetPos = pair<int, int>(j+1, i+1);
                    break;
                case '.':
                case 'X':
                    break;
                default:
                    return false; // Unknown symbol
            }

            line.push_back(c);

            // add right border
            if (j == (this->_cols-1))
                line.push_back('X');
        }
        this->_field.push_back(line); // put new line to 2D array - _field
    }
    // check if target point was given
    if (this->_itemsInMap.targetPos == pair<int, int>(-1,-1))
    {
        return false;
    }

    // add botton border
    this->_field.push_back(border);
    // count added borders
    this->_rows += 2;
    this->_cols += 2;

    return true;
}


int GameMap::getCols() const
{
    return this->_cols;
}


int GameMap::getRows() const
{
    return this->_rows;
}


vector<vector<char> > &GameMap::getMapField()
{
    return this->_field;
}


MapItems GameMap::getMapItems()
{
    return this->_itemsInMap;
}


string GameMap::getMapName()
{
    return this->_mapName;
}


bool GameMap::isWall(int x, int y)
{
    try
    {
        if (this->_field.at(y).at(x) == 'X')
            return true;
        else
            return false;
    }
    catch (out_of_range)
    {
        return false;
    }
}


char GameMap::isOnPosition(int x, int y)
{
    try
    {
        return this->_field.at(y).at(x);
    }
    catch (out_of_range)
    {
        return ' ';
    }
}

/* END OF FILE */
