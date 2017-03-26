//
// Created by artem on 26.02.17.
//

#include <QToolButton>
#include "LifeController.h"

LifeController::LifeController(LifeModel *model,
                               MainWindow *mainWindow) : _model(model),
                                                          _mainWindow(mainWindow){
    createActions();

    _area = _mainWindow->getArea();

    _mainWindow->connect(_model->timer(),SIGNAL(timeout()), this, SLOT(step()));

    _mainWindow->connect(_mainWindow->getParamsWidget()->getXorRB(),
                         SIGNAL(clicked(bool)),this,SLOT(checkedXor(bool)));
    _mainWindow->connect(_xorAct,
                         SIGNAL(triggered(bool)),_mainWindow->getParamsWidget()->getXorRB(),SLOT(setChecked(bool)));

    _mainWindow->connect(_mainWindow->getParamsWidget()->getRepRB(),
                         SIGNAL(clicked(bool)),this,SLOT(checkedRep(bool)));
    _mainWindow->connect(_replaceAct,
                         SIGNAL(triggered(bool)),_mainWindow->getParamsWidget()->getRepRB(),SLOT(setChecked(bool)));


}

LifeController::~LifeController()
{
    delete _newAct;
    delete _openAct;
    delete _saveAct;
    delete _saveAsAct;
    delete _exitAct;
    delete _replaceAct;
    delete _xorAct;
    delete _clearAct;
    delete _parametrsAct;
    delete _toolBarAct;
    delete _statusBarAct;
    delete _impactAct;
    delete _aboutAct;
    delete _runAct;
    delete _stopAct;
    delete _stepAct;

}

void LifeController::openFile()
{
    if(!_mainWindow->mbSave()){
        QDir dir = QDir::currentPath();
        dir.cdUp();
        dir.cd("Life/Data");
        QString fileName = QFileDialog::getOpenFileName(_mainWindow,
                                          tr("Open File"), dir.absolutePath());
        if(_mainWindow->getParser()->open(fileName)){
            _area->update();
        }else{
            QMessageBox box;
            box.setText("cant open File");
            box.exec();
        }
    }
}
void LifeController::createActions() {
    const QIcon newIcon = QIcon::fromTheme("document-new");
    _newAct = new QAction(newIcon,tr("&New File"), this);
    _newAct->setStatusTip(tr("Create new file"));
    _mainWindow->connect(_newAct, SIGNAL(triggered()), this, SLOT(create()));
    _mainWindow->getFileMenu()->addAction(_newAct);
    _mainWindow->getFileBar()->addAction(_newAct);


    const QIcon openIcon = QIcon::fromTheme("document-open");
    _openAct = new QAction(openIcon,tr("&Open File"), this);
    _openAct->setStatusTip(tr("Open File"));
    _mainWindow->connect(_openAct, SIGNAL(triggered()), this, SLOT(openFile()));
    _mainWindow->getFileMenu()->addAction(_openAct);
    _mainWindow->getFileBar()->addAction(_openAct);

    const QIcon saveIcon = QIcon::fromTheme("document-save");
    _saveAct = new QAction(saveIcon,tr("&Save File"), this);
    _saveAsAct = new QAction(saveIcon,tr("&Save as"), this);
    _saveAsAct->setStatusTip(tr("Save as "));
    _saveAct->setStatusTip(tr("Save file"));
    _mainWindow->connect(_saveAct, SIGNAL(triggered()), this, SLOT(save()));
    _mainWindow->connect(_saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));
    _mainWindow->getFileMenu()->addAction(_saveAct);
    _mainWindow->getFileMenu()->addAction(_saveAsAct);
    _mainWindow->getFileBar()->addAction(_saveAct);
    _mainWindow->getFileBar()->addAction(_saveAsAct);
    _mainWindow->getFileMenu()->addSeparator();

    const QIcon exitIcon = QIcon::fromTheme("exit-application");
    _exitAct = new QAction(exitIcon,tr("&Exit"), this);
    _exitAct->setStatusTip(tr("Exit from programm"));
    _mainWindow->connect(_exitAct, SIGNAL(triggered()), this, SLOT(exit()));
    _mainWindow->getFileMenu()->addAction(_exitAct);
    _mainWindow->getFileBar()->addAction(_exitAct);



    const QIcon replaceIcon = QIcon::fromTheme("");
    _replaceAct = new QAction(replaceIcon,tr("&Replace mode"), this);
    _replaceAct->setStatusTip(tr("Replace mode"));
    _replaceAct->setCheckable(true);
    _mainWindow->connect(_replaceAct, SIGNAL(triggered()), this, SLOT(replace()));
    _mainWindow->getEditMenu()->addAction(_replaceAct);
    _mainWindow->getEditBar()->addAction(_replaceAct);

    const QIcon xorIcon = QIcon::fromTheme("Xor mode");
    _xorAct = new QAction(xorIcon,tr("&Xor mode"), this);
    _xorAct->setStatusTip(tr("Xor mode"));
    _xorAct->setCheckable(true);
    _mainWindow->connect(_xorAct, SIGNAL(triggered()), this, SLOT(xorf()));
    _mainWindow->getEditMenu()->addAction(_xorAct);
    _mainWindow->getEditBar()->addAction(_xorAct);
    _mainWindow->getEditMenu()->addSeparator();



    const QIcon clearIcon = QIcon::fromTheme("window-close");
    _clearAct = new QAction(clearIcon,tr("&Clear field"), this);
    _clearAct->setStatusTip(tr("Clear"));
    _mainWindow->connect(_clearAct, SIGNAL(triggered()), this, SLOT(clear()));
    _mainWindow->getEditMenu()->addAction(_clearAct);
    _mainWindow->getEditBar()->addAction(_clearAct);
    _mainWindow->getEditMenu()->addSeparator();

    const QIcon paramIcon = QIcon::fromTheme("document-properties");
    _parametrsAct = new QAction(paramIcon,tr("&Parametrs"), this);
    _parametrsAct->setStatusTip(tr("Set Parametrs"));
    _mainWindow->connect(_parametrsAct, SIGNAL(triggered()), this, SLOT(params()));
    _mainWindow->getEditMenu()->addAction(_parametrsAct);
    _mainWindow->getEditBar()->addAction(_parametrsAct);


    _toolBarAct = new QAction(tr("&ToolBar"), this);
    _toolBarAct->setStatusTip(tr("En/Dis ToolBar"));
    _toolBarAct->setCheckable(true);
    _toolBarAct->setChecked(true);
    _mainWindow->connect(_toolBarAct, SIGNAL(triggered()), this, SLOT(showToolBar()));
    _mainWindow->getViewMenu()->addAction(_toolBarAct);

    _statusBarAct = new QAction(tr("&StatusBar"), this);
    _statusBarAct->setStatusTip(tr("En/Dis StatusBar"));
    _statusBarAct->setCheckable(true);
    _statusBarAct->setChecked(true);
    _mainWindow->connect(_statusBarAct, SIGNAL(triggered()), this, SLOT(showStatusBar()));
    _mainWindow->getViewMenu()->addAction(_statusBarAct);
    _mainWindow->getViewMenu()->addSeparator();

    const QIcon impactIcon = QIcon::fromTheme("format-text-strikethrough");
    _impactAct = new QAction(impactIcon,tr("&Display Impact"), this);
    _impactAct->setStatusTip(tr("Display Impact"));
    _impactAct->setCheckable(true);
    _mainWindow->connect(_impactAct, SIGNAL(triggered()), this, SLOT(displayImpact()));
    _mainWindow->getViewMenu()->addAction(_impactAct);
    _mainWindow->getEditBar()->addAction(_impactAct);


    const QIcon runIcon = QIcon::fromTheme("media-playback-pause");
    _runAct = new QAction(runIcon,tr("&Run life"), this);
    _runAct->setStatusTip(tr("Run life"));
    _runAct->setCheckable(true);
    _mainWindow->connect(_runAct, SIGNAL(triggered()), this, SLOT(run()));
    _mainWindow->getSimulateMenu()->addAction(_runAct);
    _mainWindow->getSimulateBar()->addAction(_runAct);

    const QIcon stepIcon = QIcon::fromTheme("media-playback-start");
    _stepAct = new QAction(stepIcon,tr("&Step"), this);
    _stepAct->setStatusTip(tr("Step"));
    _mainWindow->connect(_stepAct, SIGNAL(triggered()), this, SLOT(step()));
    _mainWindow->getSimulateMenu()->addAction(_stepAct);
    _mainWindow->getSimulateBar()->addAction(_stepAct);


    const QIcon helpIcon = QIcon::fromTheme("help-about");
    _aboutAct = new QAction(helpIcon,tr("&Help"), this);
    _aboutAct->setStatusTip(tr("Help"));
    _mainWindow->connect(_aboutAct, SIGNAL(triggered()), this, SLOT(about()));
    _mainWindow->getHelpMenu()->addAction(_aboutAct);
    _mainWindow->getHelpBar()->addAction(_aboutAct);

    QAction *act =_model->info().mode == Utils::REPLACE ? _replaceAct : _xorAct;
    act->setChecked(true);

}

void LifeController::step() {
    _model->step();
    _model->setImpact();
    _area->update();
}

void LifeController::checkedXor(bool param)
{
    _xorAct->setChecked(param);
    _replaceAct->setChecked(!param);
}
void LifeController::checkedRep(bool param)
{
    _xorAct->setChecked(!param);
    _replaceAct->setChecked(param);
}


void LifeController::save() {
    QString pathToFile = _mainWindow->getParser()->pathToFile();
    if(!pathToFile.isEmpty()){
        _mainWindow->getParser()->save();
    }else{
        saveAs();
    }
}

void LifeController::saveAs()
{
    QDir dir = QDir::currentPath();
    dir.cdUp();
    dir.cd("Life/Data");
    QString fileName = QFileDialog::getSaveFileName(_mainWindow,
                                      tr("Save File"), dir.absolutePath());
    _mainWindow->getParser()->save(fileName);
}

void LifeController::about() {
    QMessageBox::about(_mainWindow, tr("About Life"),
                       tr("<p>Федин Артем ФИТ 14202</p>"
                                  "<p>--Описание программы--</p>"
                                  "<p>1. Replace Mode - переход в режим Replace</p>"
                                  "<p>2. XOR Mode - переход в режим XOR</p>"
                                  "<p>3. edit - задание режима и произвольного размера ячейки</p>"
                                  "<p>Работает сохранение и загрузка.</p>"));

}

void LifeController::create() {
    _area->setCreated(true);
    _mainWindow->mbSave();
    _mainWindow->getParamsWidget()->setVisible(true);
}

void LifeController::exit() {
   if(_mainWindow->mbClose()){
       QApplication::quit();
   }
}

void LifeController::replace() {
    _model->setMode(Utils::REPLACE);
    if(_replaceAct->isChecked()){
        _xorAct->setChecked(false);
    }
}

void LifeController::xorf() {
    _model->setMode(Utils::XOR);
    if(_xorAct->isChecked()){
        _replaceAct->setChecked(false);
    }
}

void LifeController::clear() {
    _model->clear();

    _area->update();
}


void LifeController::showToolBar() {
    if(!_toolBarAct->isChecked()){
        _mainWindow->getEditBar()->setVisible(false);
        _mainWindow->getFileBar()->setVisible(false);
        _mainWindow->getHelpBar()->setVisible(false);
        _mainWindow->getSimulateBar()->setVisible(false);
    }else{
        _mainWindow->getEditBar()->setVisible(true);
        _mainWindow->getFileBar()->setVisible(true);
        _mainWindow->getHelpBar()->setVisible(true);
        _mainWindow->getSimulateBar()->setVisible(true);

    }

}

void LifeController::showStatusBar() {
    if(_statusBarAct->isChecked()){
        _statusBarAct->setVisible(false);
    }else{
        _statusBarAct->setVisible(true);
    }
}

void LifeController::displayImpact() {
    if(_impactAct->isChecked()){
        _area->setImpact(true);
    }else{
        _area->setImpact(false);
    }
    _area->update();

}

void LifeController::run() {

    if(_runAct->isChecked()){
        _model->timer()->start();
        _stepAct->setDisabled(true);
    }else{
        _model->timer()->stop();
        _stepAct->setDisabled(false);
    }

}

void LifeController::params() {
    _area->setCreated(false);
    _mainWindow->getParamsWidget()->setVisible(true);
}


