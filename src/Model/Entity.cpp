/**
 * @file Entity.cpp
 * @author Michal Ľaš (xlasmi00), Adam Lazík (xlazik00)
 * @brief Class representing Pac-Man and ghosts in model
 *
 */

#include "Entity.h"

Entity::Entity(int x, int y)
{
    this->x_pos = x;
    this->y_pos = y;
    // if pacman is not moving it has current position equal to next position
    this->x_next_pos = x;
    this->y_next_pos = y;
    this->_currDirection = direction::NONE;
    this->_nextDirection = direction::NONE;
    this->_moving = false;
    movable = true;
}


Entity::~Entity()
{

}


int Entity::x()
{
    return this->x_pos;
}


int Entity::y()
{
    return this->y_pos;
}


int Entity::next_x()
{
    return this->x_next_pos;
}


int Entity::next_y()
{
    return this->y_next_pos;
}


void Entity::setCurrPos(int x, int y)
{
    this->x_pos = x;
    this->y_pos = y;
}

pair<int, int> Entity::getCurrPos()
{
    return pair<int, int>(x_pos, y_pos);
}

void Entity::setNextPos(int x, int y)
{
    this->x_next_pos = x;
    this->y_next_pos = y;
}

pair<int, int> Entity::getNextPos()
{
    return pair<int, int>(x_next_pos, y_next_pos);
}


direction Entity::getCurrDirection()
{
    return this->_currDirection;
}


direction Entity::getNextDirection()
{
    return this->_nextDirection;
}


void Entity::setCurrDirection(direction dr)
{
    this->_currDirection = dr;
}


void Entity::setNextDirection(direction dr)
{
    this->_nextDirection = dr;
}


bool Entity::isMoving()
{
    return this->_moving;
}


void Entity::setMoving(bool state)
{
    this->_moving = state;
}

bool Entity::isMovable()
{
    return movable;
}

void Entity::setMovable(bool state)
{
    movable = state;
}

void Entity::assignNumber(int n)
{
    number = n;
}

int Entity::getNumber()
{
    return number;
}

/* END OF FILE */
