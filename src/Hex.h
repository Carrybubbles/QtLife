//
// Created by artem on 19.02.17.
//

#ifndef LIFE_HEX_H
#define LIFE_HEX_H

#include <QPoint>
#include <QImage>
#include <memory>

class Hex final
{
public:
    Hex(const int &_size, const QPoint &_axisCoords);
    Hex(const int &_size,const int x, const int y);
    ~Hex();

    int getSize() const{
        return size;
    }

    int getHeight() const{
        return (size*2) * 3 / 4;
    }

    int getWidth() const {
        return sqrt(3)/2*(size*2);
    }


    int getH() const;

    int getR() const;


    void setAxisCoords(QPoint *axisCoords);

    void setCenterCoords(QPoint *centerCoords);


    std::vector<QPoint> getHexPointsCoord();


    std::shared_ptr<QPoint> getAxisCoords() const;

    std::shared_ptr<QPoint> getCenterCoords() const;

private:
    int size;
    int h;
    int r;
    //position hex in map
    std::shared_ptr<QPoint> axisCoords;
    std::shared_ptr<QPoint> centerCoords;

    QPoint converPixelToHex(const int x, const int y);
    QPoint getHexAngle(const int &number);
};

#endif //LIFE_HEX_H
