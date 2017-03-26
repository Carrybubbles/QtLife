#include "FileParser.h"

FileParser::FileParser(LifeModel *model, MainWindow *mainWind){
    _model = model;
    _main = mainWind;

}

bool FileParser::parseLifeFormat( Storage *storage) {
    int width = 0;
    int height = 0;
    int cellSize = 0;
    std::unique_ptr<QFile> file(new QFile(_pathToFile));
    QVector<QPoint> aliveCells;
    QStringList temp;
    bool ok;
    if(file->open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&*file);

        QString fieldSize = in.readLine();

        if(!fieldSize.isEmpty()){
            temp = fieldSize.split(' ');
            if(temp.size() >= 3)
                if(!temp[2].startsWith("//"))  return false;
            width = temp[0].toInt(&ok,10);
            if(!ok) return false;
            height = temp[1].toInt(&ok,10);
            if(!ok) return false;
        }

        //parse filed
        QString hexSize = in.readLine();
        if(!hexSize.isEmpty()){
            temp = hexSize.split(' ');
            if(temp.size() >= 2)
                if(!temp[1].startsWith("//"))  return false;
            cellSize = temp[0].toInt(&ok,10);
            if(!ok) return false;
        }

        //parse hexsize
        while(!in.atEnd()){
            QString aliveCell = in.readLine();
            if(!aliveCell.isEmpty()){
                QStringList temp = aliveCell.split(' ');
                if(temp.size() >= 3)
                    if(!temp[2].startsWith("//")) return false;
                else if(temp.size() == 1)
                        return false;
                int x = temp[0].toInt(&ok,10);
                if(!ok) return false;
                int y = temp[1].toInt(&ok,10);
                if(!ok) return false;
                aliveCells.append(QPoint(x,y));
            }
        }
        storage->height = height;
        storage->width = width;
        storage->cellSize = cellSize;
        storage->aliveCells = aliveCells;
        file->close();
        return true;
    }
    return false;
}

FileParser::~FileParser() {}

bool FileParser::save() {

    std::unique_ptr<Storage> data(_model->getModelData());
    int height = data->height;
    int width = data->width;
    int cellSize = _main->getParamsWidget()->getInfo()->cellSize;
    QVector<QPoint> points = data->aliveCells;
    QPointer<QFile> file(new QFile(_pathToFile));
    if(file->open( QFile::WriteOnly| QFile::Text)){
        QTextStream stream(file);
        stream << width << " " << height << '\n';
        stream << cellSize << '\n';
        foreach (QPoint point, points) {
           stream << point.x() << " " << point.y() <<'\n';
        }
        _saved = true;
        return true;
    }
    return false;
}

bool FileParser::save(const QString &pathToFile)
{
    _pathToFile = pathToFile;
    std::unique_ptr<Storage> data(_model->getModelData());
    int height = data->height;
    int width = data->width;
    int cellSize = _main->getParamsWidget()->getInfo()->cellSize;
    QVector<QPoint> points = data->aliveCells;
    QPointer<QFile> file(new QFile(pathToFile));
    if(file->open(QFile::WriteOnly|QFile::Text)){
        QTextStream stream(file);
        stream << width << " " << height << '\n';
        stream << cellSize << '\n';
        foreach (QPoint point, points) {
           stream << point.x() << " " << point.y() <<'\n';
        }
        _saved = true;
        return true;
    }
    return false;
}

QString FileParser::pathToFile() const
{
    return _pathToFile;
}

void FileParser::setPathToFile(const QString &pathToFile)
{
    _pathToFile = pathToFile;
}

Storage FileParser::storage()
{
    return _storage;
}

void FileParser::setStorage(const Storage &storage)
{
    _storage = storage;
}

bool FileParser::saved() const
{
    return _saved;
}

void FileParser::setSaved(bool saved)
{
    _saved = saved;
}
bool FileParser::open() {
    std::unique_ptr<Storage> storage(new Storage());
    if(parseLifeFormat(storage.get())){
        _model->clear();
        _main->getParamsWidget()->getInfo()->height = storage->height;
        _main->getParamsWidget()->getInfo()->width = storage->width;
        _main->getParamsWidget()->getInfo()->cellSize = storage->cellSize;
        _main->getParamsWidget()->initFields();
        _main->getParamsWidget()->reconstruct();
        _model->setModelData(*storage);
        _saved = true;

        return true;
    }
    return false;

}

bool FileParser::open(const QString &pathToFile)
{
    _pathToFile = pathToFile;
    std::unique_ptr<Storage> storage(new Storage());
    if(parseLifeFormat(storage.get())){
        _model->clear();
        _main->getParamsWidget()->getInfo()->height = storage->height;
        _main->getParamsWidget()->getInfo()->width = storage->width;
        _main->getParamsWidget()->getInfo()->cellSize = storage->cellSize;
        _main->getParamsWidget()->initFields();
        _main->getParamsWidget()->reconstruct();
        _model->setModelData(*storage);
        _saved = true;
        return true;
    }
    return false;
}



