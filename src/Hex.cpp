#include "Hex.h"

#include <QDebug>
#include <QPainter>
#include <Constants.h>

Hex::Hex(const int &size, const QPoint &_axisCoords):size(size), axisCoords(new QPoint(_axisCoords)){
    h = sin(30*M_PI / 180) * size;
    r = cos(30*M_PI / 180) * size;

    int xc = r + getWidth()*axisCoords->x() + (axisCoords->y() % 2)*r;
    int yc = size + axisCoords->y() * (getHeight());

    centerCoords = std::shared_ptr<QPoint>(new QPoint(xc,yc));
}

Hex::Hex(const int &size, int const x, int const y):size(size) {
    r = cos(30*M_PI / 180) * size;
    h = sin(30*M_PI / 180) * size;

    axisCoords = std::shared_ptr<QPoint>(new QPoint(converPixelToHex(x, y)));
    int xc = r + getWidth()*axisCoords->x() + (axisCoords->y() % 2)*r;
    int yc = size + axisCoords->y() * (getHeight());

    centerCoords = std::shared_ptr<QPoint>(new QPoint(xc,yc));
}

Hex::~Hex(){
}

std::vector<QPoint> Hex::getHexPointsCoord()
{
    std::vector<QPoint> points;
    for(int i = 0; i < 6; i++){
        points.push_back(getHexAngle(i));
    }

    return points;
}

std::shared_ptr<QPoint> Hex::getAxisCoords() const
{
    return axisCoords;
}


std::shared_ptr<QPoint> Hex::getCenterCoords() const
{
    return centerCoords;
}


QPoint Hex::getHexAngle(const int &number)
{

    const int angleDeg = 60 * number + 30;
    const double angleRad = (M_PI  * angleDeg) / 180;
    return QPoint((int) (centerCoords->x() + size * cos(angleRad)),
                      (int) (centerCoords->y() + size * sin(angleRad)));
}


QPoint Hex::converPixelToHex(const int x, const int y){

    const int xBlock = x / (2 * r + 1);
    const int yBlock = y / (size + h + 1);
    const int xPixel = x % (2 * r + 1);
    const int yPixel = y % (size + h +1);
    const double m = (double)h / r;
    int sx = xBlock;
    int sy = yBlock;
    if(yBlock % 2 == 0){
        //left
        if(yPixel < (h - xPixel * m)){
            --sx;
            --sy;
        }
        if(yPixel < (-h + xPixel*m)){
            --sy;
        }
    }else{
        //right side
        if(xPixel >= r){
            if(yPixel <  (2*h - xPixel*m)){
                --sy;
            }
        }
        if(xPixel < r){
            if(yPixel < (xPixel * m)){
               --sy;
            }else{
               --sx;
            }
        }
    }
    return QPoint(sx,sy);
}



int Hex::getH() const {
    return h;
}

int Hex::getR() const {
    return r;
}


