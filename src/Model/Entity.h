/**
 * @file Entity.h
 * @author
 * @brief header file for Entity.cpp
 *
 */

#ifndef ENTITY_H
#define ENTITY_H

#include <utility>
#include "../consts.h"

using namespace std;


class Entity
{
public:
    Entity(int x, int y);
    ~Entity();
    int x();
    int y();
    int next_x();
    int next_y();
    void setCurrPos(int x, int y);
    pair<int, int> getCurrPos();
    void setNextPos(int x, int y);
    pair<int, int> getNextPos();
    direction getCurrDirection();
    direction getNextDirection();
    void setCurrDirection(direction dr);
    void setNextDirection(direction dr);
    bool isMoving();
    void setMoving(bool state);
    bool isMovable();
    void setMovable(bool state);
    void assignNumber(int n);
    int getNumber();

private:
    int x_pos;                  //< current pacman x-position
    int y_pos;                  //< current pacman y-position
    int x_next_pos;             //< next pacman x-position
    int y_next_pos;             //< next pacman y-position
    direction _currDirection;   //< current pacman movement direction
    direction _nextDirection;   //< next pacman movement direction - allows save the next change of direction
    bool _moving;               //< true if pacman is currently moving false if it is not moving
    bool movable;               //< if pacman dies, it cannot be moved until next round starts
    int number;                 //< used to distinguish ghosts for logging purposes
};

#endif // ENTITY_H


/* END OF FILE */
