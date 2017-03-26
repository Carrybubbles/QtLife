#ifndef PARAMSSTORAGE_H
#define PARAMSSTORAGE_H

#include <QPointer>
namespace data {


struct infoLife{
    infoLife(){}
    int cellSize = 30;
    int width = 30;
    int height = 30;
    double fstImpact = 1;
    double sndImpact = 0.3;
    double lBegin = 2;
    double lEnd = 3.3;
    double bBegin = 2.3;
    double bEnd = 2.9;
    int mode = 0;
};


struct Storage {
    Storage(){}
    int height;
    int width;
    int cellSize;
    QVector<QPoint> aliveCells;
};

} // Data

#endif // PARAMSSTORAGE_H
