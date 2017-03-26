//
// Created by artem on 20.02.17.
//

#ifndef LIFE_FILEPARSER_H
#define LIFE_FILEPARSER_H


#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDir>
#include <QFileDialog>

#include "LifeModel.h"
#include "LifeArea.h"
#include "paramsstorage.h"
#include "MainWindow.h"

using namespace data;
class LifeModel;
class LifeArea;
class MainWindow;

class FileParser final{
public:
    FileParser(LifeModel *model, MainWindow *mainWind);
    virtual ~FileParser();

    bool open();
    bool open(const QString& pathToFile);
    bool save();
    bool save(const QString& pathToFile);

    QString pathToFile() const;
    void setPathToFile(const QString &pathToFile);

    Storage storage();
    void setStorage(const Storage &storage);

    bool saved() const;
    void setSaved(bool saved);
    bool parseLifeFormat(Storage *storage);

private:
    QString _fileName = "";
    QString FORMAT = "lf";
    LifeModel *_model;
    MainWindow *_main;
    Storage _storage;
    QString _pathToFile;
    bool _saved;


};


#endif //LIFE_FILEPARSER_H
