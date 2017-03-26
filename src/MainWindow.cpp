//
// Created by artem on 19.02.17.
//

#include "MainWindow.h"

MainWindow::MainWindow(LifeModel *_model):model(_model) {
    scrollArea = new QScrollArea();
    area = new LifeArea(this,_model);
    scrollArea->setWidget(area);
    setCentralWidget(scrollArea);

    paramsWidget = new ParamsWidget(area,_model,this);
    model->setInfo(*paramsWidget->getInfo());
    paramsWidget->setVisible(false);

    parser = new FileParser(_model,this);
    addMenus();
    statusBar()->showMessage(tr("Ready"), 2000);
}



MainWindow::~MainWindow() {

    delete scrollArea;
    delete fileMenu;
    delete editMenu;
    delete viewMenu;
    delete helpMenu;
    delete simulateMenu;
    delete xorBtn;
    delete repBtn;
    delete fileBar;
    delete editBar;
    delete simulateBar;
    delete helpBar;
    delete parser;

}

LifeModel *MainWindow::getModel() const {
    return model;
}

void MainWindow::setModel(LifeModel *model) {
    MainWindow::model = model;
}


LifeArea *MainWindow::getArea() const {
    return area;
}

void MainWindow::setArea(LifeArea *area) {
    MainWindow::area = area;
}


QMenu *MainWindow::getFileMenu() const {
    return fileMenu;
}

void MainWindow::setFileMenu(QMenu *fileMenu) {
    MainWindow::fileMenu = fileMenu;
}

QMenu *MainWindow::getEditMenu() const {
    return editMenu;
}

void MainWindow::setEditMenu(QMenu *editMenu) {
    MainWindow::editMenu = editMenu;
}

QMenu *MainWindow::getViewMenu() const {
    return viewMenu;
}

void MainWindow::setViewMenu(QMenu *viewMenu) {
    MainWindow::viewMenu = viewMenu;
}

QMenu *MainWindow::getSimulateMenu() const {
    return simulateMenu;
}

void MainWindow::setSimulateMenu(QMenu *simulateMenu) {
    MainWindow::simulateMenu = simulateMenu;
}

QMenu *MainWindow::getHelpMenu() const {
    return helpMenu;
}

void MainWindow::setHelpMenu(QMenu *helpMenu) {
    MainWindow::helpMenu = helpMenu;
}

QToolBar *MainWindow::getFileBar() const {
    return fileBar;
}

void MainWindow::setFileBar(QToolBar *fileBar) {
    MainWindow::fileBar = fileBar;
}

QToolBar *MainWindow::getEditBar() const {
    return editBar;
}

void MainWindow::setEditBar(QToolBar *editBar) {
    MainWindow::editBar = editBar;
}


QToolBar *MainWindow::getSimulateBar() const {
    return simulateBar;
}

void MainWindow::setSimulateBar(QToolBar *simulateBar) {
    MainWindow::simulateBar = simulateBar;
}

QToolBar *MainWindow::getHelpBar() const {
    return helpBar;
}

void MainWindow::setHelpBar(QToolBar *helpBar) {
    MainWindow::helpBar = helpBar;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(mbClose()){
        event->accept();
    }else{
        event->ignore();
    }
}

FileParser *MainWindow::getParser() const
{
    return parser;
}

void MainWindow::setParser(FileParser *value)
{
    parser = value;
}

void MainWindow::addMenus() {
    addToolBar(fileBar);
    addToolBar(editBar);
    addToolBar(simulateBar);
    addToolBar(helpBar);
    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(editMenu);
    menuBar()->addMenu(viewMenu);
    menuBar()->addMenu(simulateMenu);
    menuBar()->addMenu(helpMenu);

}

bool MainWindow::mbSave()
{
    std::shared_ptr<Storage> str(new Storage());
    parser->parseLifeFormat(str.get());
    if(!model->isEmpty()){
        if(!model->isModified(str.get())){
            QMessageBox::StandardButton ret;
            ret = QMessageBox::warning(this, tr("Life"),
                              tr("The model was modified"
                                 "Do you want to save your changes?"),
                              QMessageBox::Save
                              | QMessageBox::Cancel);

            if (ret == QMessageBox::Save) {
                if(!parser->pathToFile().isEmpty()){
                   parser->save();
                }else{
                    QDir dir = QDir::currentPath();
                    dir.cdUp();
                    dir.cd("Life/Data");
                    QString fileName = QFileDialog::getSaveFileName(this,
                                                      tr("Save File"), dir.absolutePath());
                    parser->save(fileName);
                }
                return true;
            } else if(ret == QMessageBox::Cancel){
                return false;
            }
        }
    }
    return false;
}

bool MainWindow::mbClose()
{
    std::shared_ptr<Storage> str(new Storage());
    parser->parseLifeFormat(str.get());
    if(!model->isEmpty()){
        if(!model->isModified(str.get())){
            QMessageBox::StandardButton ret;
            ret = QMessageBox::warning(this, tr("Life"),
                              tr("The model was modified"
                                 "Do you want to save your changes?"),
                              QMessageBox::Save | QMessageBox::Discard
                              | QMessageBox::Cancel);

            if (ret == QMessageBox::Save) {
                if(!parser->pathToFile().isEmpty()){
                   parser->save();
                }else{
                    QDir dir = QDir::currentPath();
                    dir.cdUp();
                    dir.cd("Life/Data");
                    QString fileName = QFileDialog::getSaveFileName(this,
                                                      tr("Save File"), dir.absolutePath());
                    parser->save(fileName);
                }
                return true;

            } else if(ret == QMessageBox::Discard){
                return true;
            }else if(ret == QMessageBox::Cancel){
                return false;
            }
        }
    }
    return true;
}

ParamsWidget *MainWindow::getParamsWidget() const {
    return paramsWidget;
}

QToolButton *MainWindow::getXorBtn() const {
    return xorBtn;
}

QToolButton *MainWindow::getRepBtn() const {
    return repBtn;
}

QScrollArea *MainWindow::getScrollArea() const {
    return scrollArea;
}



