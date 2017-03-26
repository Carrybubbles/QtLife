//
// Created by artem on 19.02.17.
//

#ifndef LIFE_LIFEMODEL_H
#define LIFE_LIFEMODEL_H

#include "Cell.h"

#include <QVector>
#include <QPoint>
#include <QTimer>
#include <QPointer>
#include <memory>

#include "Constants.h"
#include "paramsstorage.h"
#include "FileParser.h"

using namespace data;

class LifeModel final {
public:
    LifeModel();
    ~LifeModel();
    void clear();

    bool isAlive(const QPoint& current);
    void step();

    void setParams();


    QPointer<QTimer> timer() const;
    void setTimer(const QPointer<QTimer> &timer);
    void setImpact();

    void initField();

    infoLife info() const;
    void setInfo(const infoLife &info);

    void setMode(int mode);

     Storage *getModelData();
     void setModelData(const Storage& storage);

\
     QVector<Cell>& board();
     void setBoard(const QVector<Cell> &board);

     QVector<Cell> getPrevBoard();
     void setPrevBoard(const QVector<Cell> &prevBoard);
     bool isModified(Storage* fileStorage);

     bool isEmpty();
private:
     infoLife _info;
     QVector<Cell> _board;
     QVector<Cell> _prevBoard;
     QPointer<QTimer> _timer;


    QVector<QPoint> *createNeighboursFirst(const QPoint &current);
    QVector<QPoint> *createNeighboursSecond(const QPoint &current);
    int powerFirst(const QPoint& first);
    int powerSecond(const QPoint& second);

};


#endif //LIFE_LIFEMODEL_H
