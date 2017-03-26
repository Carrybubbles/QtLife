//
// Created by artem on 19.02.17.
//

#include "MyGraphics.h"


MyGraphics::MyGraphics(QImage *image):_image(image) {}


void MyGraphics::drawLine(const int x1, const int y1, const int x2, const int y2) {
    int deltaX = abs(x2 - x1);
    int deltaY = abs(y2 - y1);
    int signX = x1 < x2 ? 1 : -1;
    int signY = y1 < y2 ? 1 : -1;
    int x = x1;
    int y = y1;
    bool change = false;
    if(deltaY > deltaX){
        int temp = deltaX;
        deltaX = deltaY;
        deltaY = temp;
        change = true;
    }
    int error = 2*deltaY - deltaX;
    for(int i = 0; i <= deltaX; i++){
        if(x < 0 || y < 0 || y >= _image->height() || x >= _image->width()){
            return;
        }
        setPixel(QPoint(x,y),_color);
        //up line
        while(error>=0){
            if(change){
                x +=signX;
            }else{
                y +=signY;
            }
            error = error -  2*deltaX;
        }
        //go through main line
        if(change){
            y += signY;
        }else{
            x += signX;
        }
        error = error +  2*deltaY;
    }

}

void MyGraphics::makeWhiteImage() {
    for(int i = 0; i < _image->height(); i++){
        for(int j = 0; j < _image->width(); j++){
            //white _color
            QRgb color = qRgba(255,255,255,0);
            setPixel(QPoint(j,i),color);
        }
    }

}



QImage *MyGraphics::getImage() const {
    return _image;
}

void MyGraphics::setImage(QImage *image) {
    MyGraphics::_image = image;
}

void MyGraphics::drawHex(const QPoint &axisCoords, const int size,const QPoint last) {
    std::unique_ptr<Hex> hex(new Hex(size, axisCoords));
    std::vector<QPoint> points = hex->getHexPointsCoord();
    if(!(axisCoords.y()%2)){
        for(int i = 0; i < 6; i++){
           QPoint point1(points[i]);
           QPoint point2(points[(i+1)%6]);
           if(i != 5 && i+1 != 0)
                drawLine(point1.x(), point1.y(), point2.x(), point2.y());
        }
        if(axisCoords.x() == last.x()){
            drawLine(points[5].x(), points[5].y(), points[0].x(), points[0].y());
        }
    }else{
        drawLine(points[2].x(), points[2].y(), points[3].x(), points[3].y());
        if(axisCoords.x() == last.x()){
            drawLine(points[0].x(), points[0].y(), points[1].x(), points[1].y());
            drawLine(points[5].x(), points[5].y(), points[0].x(), points[0].y());
            drawLine(points[4].x(), points[4].y(), points[5].x(), points[5].y());
        }
        if(axisCoords.y() == last.y()){
            drawLine(points[0].x(), points[0].y(), points[1].x(), points[1].y());
            drawLine(points[1].x(), points[1].y(), points[2].x(), points[2].y());
        }
    }


}

QRgb MyGraphics::getColor() const {
    return _color;
}

void MyGraphics::setColor(QRgb color) {
    MyGraphics::_color = color;
}

void MyGraphics::setPixel(const QPoint &point,QRgb rgb) {
    uchar* start = _image->bits();
    int y = point.y();
    int x = point.x();
    uchar* pos = &start[y*_image->width()*4 + x*4];
    pos[0] = (uchar) qBlue(rgb);
    pos[1] = (uchar) qGreen(rgb);
    pos[2] = (uchar) qRed(rgb);
    pos[3] = (uchar) qAlpha(rgb);

}

void MyGraphics::spanFill(const QPoint &point, QRgb replace, QRgb newColor) {
    QRgb current(getPixel(point));
    if(QColor(current) != QColor(replace)){
        return;
    }
    std::unique_ptr<QStack<QPoint>> stack(new QStack<QPoint>);
    stack->push(QPoint(point));
    while(!stack->isEmpty()){
        QPoint pop = stack->pop();
        setPixel(pop,newColor);
        for (int j = -1; j <= 1; j +=2) {
            int curx = j + pop.x();
            int cury = pop.y();
            if (cury >= 0 && cury < _image->height() && curx < _image->width() && curx >=0) {
                if( QColor(getPixel(QPoint(curx,cury))) == QColor(replace)){
                    stack->append(QPoint(curx,cury));
                }
            }
        }
        for (int j = -1; j <= 1; j +=2) {
            int curx =  pop.x();
            int cury = j+pop.y();
            if (cury >= 0 && cury < _image->height() && curx < _image->width() && curx >=0) {
                if( QColor(getPixel(QPoint(curx,cury))) == QColor(replace)){
                    stack->append(QPoint(curx,cury));
                }
            }
        }
    }
}

QRgb MyGraphics::getPixel(const QPoint &point) {
    uchar* start = _image->bits();
    int y = point.y();
    int x = point.x();
    uchar* pos = &start[y*_image->width()*4 + x*4];
    return qRgba(pos[0],pos[1],pos[2],pos[3]);
}

