/**
 * @file Pacman.cpp
 * @author
 * @brief Class representing Pac-Man
 * 
 */

#include "Pacman.h"

Pacman::Pacman(int x, int y)
{
    this->x_pos = x;
    this->y_pos = y;
    // if pacman is not moving it has current position equal to next position
    this->x_next_pos = x;
    this->y_next_pos = y;
    this->_currDirection = direction::NONE;
    this->_nextDirection = direction::NONE;
    this->_moving = false;
}


Pacman::~Pacman()
{

}


int Pacman::x()
{
    return this->x_pos;
}


int Pacman::y()
{
    return this->y_pos;
}


int Pacman::next_x()
{
    return this->x_next_pos;
}


int Pacman::next_y()
{
    return this->y_next_pos;
}


void Pacman::setCurrPos(int x, int y)
{
    this->x_pos = x;
    this->y_pos = y;
}


void Pacman::setNextPos(int x, int y)
{
    this->x_next_pos = x;
    this->y_next_pos = y;
}


direction Pacman::getCurrDirection()
{
    return this->_currDirection;
}


direction Pacman::getNextDirection()
{
    return this->_nextDirection;
}


void Pacman::setCurrDirection(direction dr)
{
    this->_currDirection = dr;
}


void Pacman::setNextDirection(direction dr)
{
    this->_nextDirection = dr;
}


bool Pacman::isMoving()
{
    return this->_moving;
}


void Pacman::setMoving(bool state)
{
    this->_moving = state;
}
