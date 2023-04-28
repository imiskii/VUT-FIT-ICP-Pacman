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
}


GameMap::~GameMap()
{

}


bool GameMap::loadMap(vector<string> &fileLines)
{
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
    this->_field.reserve(this->_rows); // set size to avoid resizeing
    for (int i = 0; i < this->_rows; i++)
    {
        // check map columns
        if (fileLines.at(i+1).size() != this->_cols) // declared size of map column and size of line does not match
        {
            return false;
        }
        vector<char> line; // create temporary vector
        line.reserve(this->_cols); // set it size to avoid resizeing
        // process one line of map
        istringstream iss(fileLines.at(i+1));
        for (int j = 0; j < this->_cols; j++)
        {
            char c;
            iss >> c;
            if (!(c == '.' || c == 'T' || c == 'X' || c == 'G' || c == 'K' || c == 'S')) // Ak sa symbol nerovná ./T/S/X/K/G
            {
                return false;
            }
            line.push_back(c);
        }
        this->_field.push_back(line); // put new line to 2D array - _field
    }
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
