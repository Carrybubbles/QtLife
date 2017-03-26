//
// Created by artem on 19.02.17.
//

#ifndef LIFE_MYPAINTER_H
#define LIFE_MYPAINTER_H


#include <QPainter>
#include <QImage>
#include <QRgb>
#include <memory>
#include <QDebug>
#include <QStack>
#include <algorithm>
#include "Hex.h"

class MyGraphics final{
public:
    explicit MyGraphics(QImage *image);
public:
    void drawLine(const int x1, const int y1, const int x2, const int y2);
    void makeWhiteImage();
    void drawHex(const QPoint &axisCoords, const int size , const QPoint last);
    void spanFill(const QPoint &point, QRgb replace, QRgb newColor);

    QImage *getImage() const;

    void setImage(QImage *image);

    QRgb getColor() const;

    void setColor(QRgb color);

private:
    void setPixel(const QPoint &point, QRgb rgb);
    QRgb getPixel(const QPoint &point);
    QImage *_image = nullptr;
    QRgb  _color = qRgba(255,0,0,0);
    bool _xor;
};


#endif //LIFE_MYPAINTER_H
