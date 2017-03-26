//
// Created by artem on 19.02.17.
//

#include "Cell.h"

Cell::Cell(const int x, const int y) : _x(x), _y(y) {}

int Cell::x() const
{
    return _x;
}

void Cell::setX(int x)
{
    _x = x;
}

int Cell::y() const
{
    return _y;
}

void Cell::setY(int y)
{
    _y = y;
}

double Cell::impact() const
{
    return _impact;
}

void Cell::setImpact(double impact)
{
    _impact = impact;
}

bool Cell::alive() const
{
    return _alive;
}

void Cell::setAlive(bool alive)
{
    _alive = alive;
}

Cell::Cell(const Cell &other):_x(other._x), _y(other._y),_impact(other._impact), _alive(other._alive) {

}

Cell& Cell::operator=(const Cell& other){
    if(&other == this)
        return *this;
    _x = other._x;
    _y = other._y;
    _impact = other._impact;
    _alive = other._alive;
    return *this;
}

bool Cell::operator==(const Cell &another)
{
    return _x == another.x() && _y == another.y();
}

bool Cell::operator!=(const Cell &another)
{
    return !(*this == another);
}


