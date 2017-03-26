//
// Created by artem on 19.02.17.
//

#include "LifeArea.h"

LifeArea::LifeArea(QWidget *parent, LifeModel *field) :QWidget(parent), _field(field)
                                                       {
    const int amountW = _field->info().width;
    const int amountH = _field->info().height;
    const int hexSize = _field->info().cellSize;
    QRect rec = QApplication::desktop()->screenGeometry();
    const int height = rec.height();
    const int width = rec.width();
    if(amountW *hexSize*2 < width && amountH*hexSize*2 < height){
        resize(width,height);
    }else{
        resize(amountW *hexSize*2,amountH*hexSize*2);
    }
    _image = new QImage(this->size(), QImage::Format_RGB32);
    _graphics = new MyGraphics(_image);
    drawField();
    update();
}

LifeArea::~LifeArea()
{
    delete _image;
    delete _graphics;
}

void LifeArea::resizeImage(int width, int height){
    resize(width,height);
    delete _image;
    _image = new QImage(this->size(),QImage::Format_RGB32);
    _graphics->setImage(_image);
}

void LifeArea::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    const int height = _field->info().height;
    const int width = _field->info().width;
    const int hexSize = _field->info().cellSize;
    for(int i = 0; i < height; i++){
        for(int j = 0; j< width; j++){
            std::unique_ptr<Hex> hex(new Hex(hexSize, QPoint(j,i)));
            int cx = hex->getCenterCoords()->x();
            int cy = hex->getCenterCoords()->y();
            if(_field->board()[width * i + j].alive()){
                _graphics->spanFill(QPoint(cx, cy), qRgba(255, 255, 255, 0), qRgba(0, 255, 0, 0));
            }else if(!_field->board()[width * i + j].alive()){
                _graphics->spanFill(QPoint(cx, cy), qRgba(0, 255, 0, 0), qRgba(255, 255, 255, 0));
            }
        }
    }
    painter.drawImage(0,0,*_image);
    if(_impact){
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial",hexSize/2));

        for(int i = 0; i < height; i++){
            for(int j = 0; j< width; j++){
                std::unique_ptr<Hex> hex(new Hex(hexSize, QPoint(j,i)));
                int cx = hex->getCenterCoords()->x();
                int cy = hex->getCenterCoords()->y();
                int startX = cx - hex->getR() ;
                int startY = cy - hex->getH();
                int h = hex->getSize();
                int w = hex->getWidth();
                QString text = QString::number(_field->board()[width * i + j].impact());
                painter.drawText(startX,startY,w,h,Qt::AlignHCenter,text);
            }
        }
    }
}

void LifeArea::drawField() {
    const int width = _field->info().width;
    const int height = _field->info().height;
    const int hexSize = _field->info().cellSize;

    _graphics->makeWhiteImage();
    _graphics->setColor(qRgba(0,0,0,0));
     for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            _graphics->drawHex(QPoint(j,i), hexSize,QPoint(width-1,height-1));
        }
    }

}

void LifeArea::mousePressEvent(QMouseEvent *event) {
    const int height = _field->info().height;
    const int width = _field->info().width;
    const int hexSize = _field->info().cellSize;

    if(event->button() == Qt::LeftButton) {
        const int x = event->pos().x();
        const int y = event->pos().y();

        std::unique_ptr<Hex> hex(new Hex(hexSize, x,y));
        const int cx = hex->getCenterCoords()->x();
        const int cy = hex->getCenterCoords()->y();
        const int ax = hex->getAxisCoords()->x();
        const int ay = hex->getAxisCoords()->y();
        if(_field->info().mode == Utils::REPLACE){
            if (ax >= 0 && ay >= 0 && ax < width && ay < height){
                _field->board()[width*ay +ax].setAlive(true);
                _graphics->spanFill(QPoint(cx, cy), qRgba(255, 255, 255, 0), qRgba(0, 255, 0, 0));
            }
        }else if(_field->info().mode == Utils::XOR){
            if (ax >= 0 && ay >= 0 && ax < width && ay < height){
                bool status = _field->board()[width*ay +ax].alive();
                _field->board()[width*ay +ax].setAlive(!status);
                _graphics->spanFill(QPoint(cx, cy), qRgba(0, 255, 0, 0), qRgba(255, 255, 255, 0));
            }
        }
        _field->setImpact();
        update();

    }
}

void LifeArea::mouseMoveEvent(QMouseEvent *event) {
    const int height = _field->info().height;
    const int width = _field->info().width;
    const int hexSize = _field->info().cellSize;
    if(event->buttons() == Qt::LeftButton) {
        const int x = event->pos().x();
        const int y = event->pos().y();
        std::unique_ptr<Hex> hex(new Hex(hexSize, x,y));
        const int cx = hex->getCenterCoords()->x();
        const int cy = hex->getCenterCoords()->y();
        const int ax = hex->getAxisCoords()->x();
        const int ay = hex->getAxisCoords()->y();
        if(_field->info().mode == Utils::REPLACE){
            if (ax >= 0 && ay >= 0 && ax < width && ay < height){
                _field->board()[width*ay +ax].setAlive(true);
                _graphics->spanFill(QPoint(cx, cy), qRgba(255, 255, 255, 0), qRgba(0, 255, 0, 0));
            }
        }else if(_field->info().mode == Utils::XOR){
            if(_prevCoords.x() != ax || _prevCoords.y() != ay){
                if (ax >= 0 && ay >= 0 && ax < width && ay < height){
                    bool status = _field->board()[width*ay +ax].alive();
                    _field->board()[width*ay +ax].setAlive(!status);
                    _graphics->spanFill(QPoint(cx, cy), qRgba(0, 255, 0, 0), qRgba(255, 255, 255, 0));
                }
                _prevCoords.setX(ax);
                _prevCoords.setY(ay);
            }
        }
        _field->setImpact();
        update();
    }
}

bool LifeArea::created() const
{
    return _created;
}

void LifeArea::setCreated(bool created)
{
    _created = created;
}

bool LifeArea::impact() const
{
    return _impact;
}

void LifeArea::setImpact(bool impact)
{
    _impact = impact;
}

QImage *LifeArea::image() const
{
    return _image;
}

void LifeArea::setImage(QImage *image)
{
    _image = image;
}


