//
// Created by artem on 19.02.17.
//

#ifndef LIFE_MAINWINDOW_H
#define LIFE_MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMessageBox>
#include <QScrollArea>
#include <QToolBar>
#include <QIcon>
#include <QStatusBar>
#include <QtWidgets/QToolButton>
#include <memory>

#include "LifeArea.h"
#include "ParamsWidget.h"
#include "Constants.h"
#include "FileParser.h"

class FileParser;
class LifeArea;
class ParamsWidget;
class LifeModel;

class MainWindow final : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(LifeModel *_model);
    ~MainWindow();

    LifeModel *getModel() const;
    void setModel(LifeModel *model);

    LifeArea *getArea() const;
    void setArea(LifeArea *area);


    QScrollArea *getScrollArea() const;

    QToolButton *getXorBtn() const;

    QToolButton *getRepBtn() const;

    ParamsWidget *getParamsWidget() const;

    QMenu *getFileMenu() const;

    void setFileMenu(QMenu *fileMenu);

    QMenu *getEditMenu() const;

    void setEditMenu(QMenu *editMenu);

    QMenu *getViewMenu() const;

    void setViewMenu(QMenu *viewMenu);

    QMenu *getSimulateMenu() const;

    void setSimulateMenu(QMenu *simulateMenu);

    QMenu *getHelpMenu() const;

    void setHelpMenu(QMenu *helpMenu);

    QToolBar *getFileBar() const;

    void setFileBar(QToolBar *fileBar);

    QToolBar *getEditBar() const;

    void setEditBar(QToolBar *editBar);

    QToolBar *getViewBar() const;

    void setViewBar(QToolBar *viewBar);

    QToolBar *getSimulateBar() const;

    void setSimulateBar(QToolBar *simulateBar);

    QToolBar *getHelpBar() const;

    void setHelpBar(QToolBar *helpBar);


    FileParser *getParser() const;
    void setParser(FileParser *value);
    bool mbSave();
    bool mbClose();


protected:
    void closeEvent(QCloseEvent *event) override;
private:       
    LifeArea *area = nullptr;
    LifeModel *model = nullptr;
    FileParser *parser = nullptr;
    ParamsWidget *paramsWidget = nullptr;

    QMenu *fileMenu = new QMenu(tr("File"));
    QMenu *editMenu = new QMenu(tr("Edit"));
    QMenu *viewMenu = new QMenu(tr("View"));
    QMenu *simulateMenu = new QMenu(tr("Simulate"));
    QMenu *helpMenu = new QMenu(tr("Help"));
    QToolButton *xorBtn = new QToolButton();
    QToolButton *repBtn = new QToolButton();

    QToolBar *fileBar = new QToolBar(tr("File"));
    QToolBar *editBar = new QToolBar(tr("Edit"));
    QToolBar *simulateBar = new QToolBar(tr("Simulate"));
    QToolBar *helpBar = new QToolBar(tr("Help"));
    QScrollArea *scrollArea = nullptr;

    void addMenus();
    void createMenus();

};


#endif //LIFE_MAINWINDOW_H
