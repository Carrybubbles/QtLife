//
// Created by artem on 26.02.17.
//

#ifndef LIFE_LIFECONTROLLER_H
#define LIFE_LIFECONTROLLER_H


#include "LifeModel.h"
#include "MainWindow.h"
#include <QMessageBox>
#include <QFileDialog>

class LifeController final: public QObject {
    Q_OBJECT
public:
    LifeController(LifeModel *model, MainWindow *mainWindow);
    ~LifeController();


private slots:
    void openFile();
    void save();
    void saveAs();
    void about();
    void create();
    void exit();

    void replace();
    void xorf();
    void clear();
    void params();

    void showToolBar();
    void showStatusBar();
    void displayImpact();

    void run();
    void step();

    void checkedXor(bool param);
    void checkedRep(bool param);
private:
    void createActions();
    LifeModel *_model = nullptr;
    LifeArea *_area = nullptr;
    MainWindow *_mainWindow = nullptr;

    QAction *_newAct = nullptr;
    QAction *_openAct = nullptr;
    QAction *_saveAct = nullptr;
    QAction *_saveAsAct = nullptr;
    QAction *_exitAct = nullptr;

    QAction *_replaceAct = nullptr;
    QAction *_xorAct = nullptr;
    QAction *_clearAct = nullptr;
    QAction *_parametrsAct = nullptr;

    QAction *_toolBarAct = nullptr;
    QAction *_statusBarAct = nullptr;
    QAction *_impactAct = nullptr;

    QAction *_aboutAct = nullptr;

    QAction *_runAct = nullptr;
    QAction *_stopAct = nullptr;
    QAction *_stepAct = nullptr;

};


#endif //LIFE_LIFECONTROLLER_H
