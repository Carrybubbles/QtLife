//
// Created by artem on 19.02.17.
//

#include "LifeModel.h"

LifeModel::LifeModel():_timer(new QTimer)
{
    _timer->setInterval(Utils::INTERVAL);
    initField();
}

LifeModel::~LifeModel(){}

QVector<QPoint> *LifeModel::createNeighboursFirst(const QPoint &current) {
    QVector<QPoint> *neigh = new QVector<QPoint>();
    QPoint *points = new QPoint[6];
    const int height = _info.height;
    const int width = _info.width;
    int x = current.x();
    int y = current.y();
    //even
    if(!(y % 2)){
        points[0] = QPoint(1,0);
        points[1] = QPoint(0,-1);
        points[2] = QPoint(-1,-1);
        points[3] = QPoint(-1,0);
        points[4] = QPoint(-1,1);
        points[5] = QPoint(0,1);
    }else{
        points[0] = QPoint(1,0);
        points[1] = QPoint(1,-1);
        points[2] = QPoint(0,-1);
        points[3] = QPoint(1,1);
        points[4] = QPoint(0,1);
        points[5] = QPoint(-1,0);

    }
    for(int i = 0 ; i < 6; i++) {
        if ((points[i].x() + x) >= 0 && (points[i].x() + x) < width &&
            (points[i].y() + y) >= 0 && (points[i].y() + y) < height) {
            neigh->append(QPoint(points[i].x() + x, points[i].y() + y));
        }
    }
    delete[] points;
    return neigh;
}

QVector<QPoint> *LifeModel::createNeighboursSecond(const QPoint &current) {
    QVector<QPoint> *neigh = new QVector<QPoint>();
    QPoint *points = new QPoint[6];
    int x = current.x();
    int y = current.y();
    const int height = _info.height;
    const int width = _info.width;
    //even
    if(!(y % 2)){
        points[0] = QPoint(-2,-1);
        points[1] = QPoint(-2,1);
        points[2] = QPoint(0,-2);
        points[3] = QPoint(0,2);
        points[4] = QPoint(1,-1);
        points[5] = QPoint(1,1);
    }else{
        points[0] = QPoint(-1,-1);
        points[1] = QPoint(-1,1);
        points[2] = QPoint(0,-2);
        points[3] = QPoint(0,2);
        points[4] = QPoint(2,1);
        points[5] = QPoint(2,-1);

    }
    for(int i = 0 ; i < 6; i++) {
        if ((points[i].x() + x) >= 0 && (points[i].x() + x) < width &&
            (points[i].y() + y) >= 0 && (points[i].y() + y) < height) {
            neigh->append(QPoint(points[i].x() + x, points[i].y() + y));
        }
    }
    delete[] points;
    return neigh;
}




void LifeModel::clear() {
    const int height = _info.height;
    const int width = _info.width;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            _board[i*width + j].setAlive(false);
        }
    }
    setImpact();
    return;
}



int LifeModel::powerFirst(const QPoint &current) {
    QPoint point;
    std::unique_ptr<QVector<QPoint>> neigh(createNeighboursFirst(current));
    const int width = _info.width;
    int power = 0;

    foreach(point, *neigh){
        if(_board[width*point.y() + point.x()].alive()){
            power++;
        }
    }

    return power;
}

int LifeModel::powerSecond(const QPoint &current) {
    QPoint point;
    std::unique_ptr<QVector<QPoint>> neigh(createNeighboursSecond(current));
    const int width = _info.width;
    int power = 0;

    foreach(point, *neigh){
        if(_board[width*point.y() + point.x()].alive()){
            power++;
        }
    }
    return power;
}


void LifeModel::setImpact()
{
    const double fstImpact = _info.fstImpact;
    const double sndImpact = _info.sndImpact;
    const int width = _info.width;
    const int height = _info.height;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            const int powerF = powerFirst(QPoint(j,i));
            const int powerS = powerSecond(QPoint(j,i));
            double impact = fstImpact*powerF + sndImpact*powerS;
            _board[i * width + j].setImpact(impact);
        }
    }

}

void LifeModel::initField()
{
    const int height = _info.height;
    const int width = _info.width;
    _board = QVector<Cell>(height*width);
    for(int i = 0; i < height; i++){
        for(int j = 0 ; j < width; j++){
            _board[i*width + j] = Cell(j,i);
        }
    }
}

infoLife LifeModel::info() const
{
    return _info;
}

void LifeModel::setInfo(const infoLife &info)
{
    _info = info;
    _board.resize(_info.width * _info.height);
}

void LifeModel::setMode(int mode)
{
    _info.mode = mode;
}



Storage *LifeModel::getModelData()
{
    Storage *storage = new Storage();
    storage->width = _info.width;
    storage->height = _info.height;
    QVector<QPoint> points;
    for(int i = 0; i < _info.height; i++){
        for(int j = 0; j < _info.width; j++){
            if(_board[i*_info.width +j].alive()){
                points.append(QPoint(j,i));
            }
        }
    }
    storage->aliveCells = points;
    return storage;
}

void LifeModel::setModelData(const Storage &storage)
{
    QVector<QPoint> points = storage.aliveCells;
    foreach (QPoint curPoint, points) {
        _board[curPoint.y()*_info.width + curPoint.x()].setAlive(true);
    }

}

QVector<Cell>& LifeModel::board()
{
    return _board;
}

void LifeModel::setBoard(const QVector<Cell> &board)
{
    _board = board;
}

QVector<Cell> LifeModel::getPrevBoard()
{
    return _prevBoard;
}

void LifeModel::setPrevBoard(const QVector<Cell> &prevBoard)
{
    _prevBoard = prevBoard;
}

bool LifeModel::isModified(Storage *fileStorage)
{
    std::shared_ptr<Storage> str(getModelData());
    return _info.height == fileStorage->height &&
           _info.width == fileStorage->width &&
            str->aliveCells == fileStorage->aliveCells;
}

bool LifeModel::isEmpty()
{
    QVector<Cell>::iterator it = std::find_if(_board.begin(), _board.end(),[](const Cell &cur){
        return cur.alive() == true;
    });
    return it == _board.end();
}



bool LifeModel::isAlive(const QPoint &current) {
    const int width = _info.width;
    const double currentImpact = _board[width*current.y() + current.x()].impact();
    const double lBegin = _info.lBegin;
    const double lEnd = _info.lEnd;
    return currentImpact >= lBegin  && currentImpact <= lEnd;
}


void LifeModel::step() {
    setImpact();
    const int width = _info.width;
    const int height = _info.height;
    QVector<Cell> nextBoard(height*width);
    for(int i = 0; i < height; i++){
        for(int j = 0 ; j < width; j++){
            nextBoard[i*width + j] = Cell(j,i);
            if(isAlive(QPoint(j,i))){
                nextBoard[i*width + j].setAlive(true);
            }
        }
    }
    _prevBoard = _board;
    _board = nextBoard;
}

void LifeModel::setParams()
{
    const int width = _info.width;
    const int height = _info.height;
    _board.resize(width*height);

}



QPointer<QTimer> LifeModel::timer() const
{
    return _timer;
}

void LifeModel::setTimer(const QPointer<QTimer> &timer)
{
    _timer = timer;
}
