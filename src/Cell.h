//
// Created by artem on 19.02.17.
//

#ifndef LIFE_CELL_H
#define LIFE_CELL_H


class Cell final{
public:
    Cell(){}
    Cell(const Cell& other);
    Cell(const int x, const int y);
    Cell &operator= (const Cell &other);
    bool operator==(const Cell &another);
    bool operator!=(const Cell &another);

    int x() const;
    void setX(int x);

    int y() const;
    void setY(int y);

    double impact() const;
    void setImpact(double impact);

    bool alive() const;
    void setAlive(bool alive);


private:
    int _x = 0;
    int _y = 0;
    double _impact = 0;
    bool _alive = false;
};


#endif //LIFE_CELL_H
