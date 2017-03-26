//
// Created by artem on 19.02.17.
//

#ifndef LIFE_LIFEAREA_H
#define LIFE_LIFEAREA_H
#include <QDebug>
#include <QEvent>
#include <QPaintEvent>
#include <QtWidgets>
#include <memory>
#include "MyGraphics.h"
#include "LifeModel.h"
#include "Constants.h"
#include "ParamsWidget.h"

class ParamsWidget;
class LifeModel;

class LifeArea final: public QWidget {
    Q_OBJECT
public:
    LifeArea(QWidget *parent = nullptr, LifeModel *field = nullptr);
    ~LifeArea();
    void drawField();
    void resizeImage(int width, int height);

    QImage *image() const;
    void setImage(QImage *image);

    bool impact() const;
    void setImpact(bool impact);


    bool created() const;
    void setCreated(bool created);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent * event) override ;
private:
    QImage *_image = nullptr;
    MyGraphics *_graphics = nullptr;
    LifeModel *_field = nullptr;
    QPoint _prevCoords;
    bool _impact = false;
    bool _created = false;
};


#endif //LIFE_LIFEAREA_H
