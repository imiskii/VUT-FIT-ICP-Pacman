/**
 * @file Entity.h
 * @author Michal Las (xlasmi00), Adam Lazik (xlazik00)
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

    /**
     * @brief get current x coordinate
     * @return int current x coordinate
     */
    int x();

    /**
     * @brief get current y coordinate
     * @return int current y coordinate
     */
    int y();

    /**
     * @brief get next x coordinate
     * @return int next x coordinate
     */
    int next_x();

    /**
     * @brief get current y coordinate
     * @return int current y coordinate
     */
    int next_y();

    /**
     * @brief set new current position
     * @param x new x coordinate
     * @param y new y coordinate
     */
    void setCurrPos(int x, int y);

    /**
     * @brief get the current position
     * @return pair<int, int> current x and y coordinates
     */
    pair<int, int> getCurrPos();

    /**
     * @brief set new next position
     * @param x new next x coordinate
     * @param y new next y coordinate
     */
    void setNextPos(int x, int y);

    /**
     * @brief get the current position
     * @return pair<int, int> current x and y coordinates
     */
    pair<int, int> getNextPos();

    /**
     * @brief Get the current entity direction
     * @return direction current entity direction
     */
    direction getCurrDirection();

    /**
     * @brief Get the next entity direction
     * @return direction next entity direction
     */
    direction getNextDirection();

    /**
     * @brief set new current entity direction
     * @param dr new direction
     */
    void setCurrDirection(direction dr);

    /**
     * @brief set new next entity direction
     * @param dr new next direction
     */
    void setNextDirection(direction dr);

    /**
     * @brief find out if entity is currently moving
     * @return true if the entity is moving
     * @return false if the entity is not moving
     */
    bool isMoving();

    /**
     * @brief set entity moving state
     * @param state new entity moving state
     */
    void setMoving(bool state);

    /**
     * @brief find out if entity is currently movable
     * @return true if the entity can be moved
     * @return false if the entity cannot be moved
     */
    bool isMovable();

    /**
     * @brief set new movable state
     * @param state new novable state
     */
    void setMovable(bool state);

    /**
     * @brief assign entity number
     * @param n entity number
     */
    void assignNumber(int n);

    /**
     * @brief get entity number
     * @return int entity number
     */
    int getNumber();

private:
    int x_pos;                  //< current entity x coordinate
    int y_pos;                  //< current entity y coordinate
    int x_next_pos;             //< next entity x coordinate
    int y_next_pos;             //< next entity y coordinate
    direction _currDirection;   //< current entity movement direction
    direction _nextDirection;   //< next entity movement direction - allows  to save the next change of direction
    bool _moving;               //< true if entity is currently moving
    bool movable;               //< true if entity can move. if PacMan dies, it cannot be moved until next round starts
    int number;                 //< used to distinguish ghosts for logging purposes
};

#endif // ENTITY_H


/* END OF FILE */
