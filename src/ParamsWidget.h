#ifndef RULES_H
#define RULES_H

#include <QDialog>
#include <QRadioButton>
#include "LifeModel.h"
#include "Constants.h"
#include "LifeArea.h"
#include "paramsstorage.h"
#include "LifeArea.h"
#include "MainWindow.h"

class LifeArea;
class LifeModel;
class MainWindow;
using namespace data;

namespace Ui {
class ParamsWidget;
}

class ParamsWidget : public QDialog
{
    Q_OBJECT

public:
    explicit ParamsWidget(QWidget *parent = 0,LifeModel *model = 0,MainWindow* mainWind = 0);
    ~ParamsWidget();

    QRadioButton* getXorRB() const;
    QRadioButton* getRepRB() const;

    infoLife *getInfo() const;
    void setInfo(infoLife *info);
    void initFields();
    void setParams();


public slots:
    void reconstruct();
private:
    Ui::ParamsWidget *ui;
    infoLife *_info = new infoLife();
    LifeModel *_model = nullptr;
    MainWindow *_main = nullptr;


};

#endif // RULES_H
