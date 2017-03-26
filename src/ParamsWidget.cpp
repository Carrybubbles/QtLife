#include "ParamsWidget.h"
#include "ui_ParamsWidget.h"

ParamsWidget::ParamsWidget(QWidget *parent, LifeModel *model, MainWindow *mainWind):
    QDialog(parent),
    ui(new Ui::ParamsWidget),
    _model(model),
    _main(mainWind)
{
    ui->setupUi(this);

    connect(ui->cellSB, SIGNAL(valueChanged(int)),ui->cellVS,SLOT(setValue(int)) );
    connect(ui->cellVS,SIGNAL(valueChanged(int)),ui->cellSB,SLOT(setValue(int)) );
    connect(ui->buttonsBox, SIGNAL(accepted()), this, SLOT(reconstruct()));
    ui->cellVS->setMinimum(10);
    ui->cellVS->setMaximum(50);
    initFields();

}

ParamsWidget::~ParamsWidget()
{
    delete ui;
    delete _info;
}

void ParamsWidget::initFields() {
    ui->bBeingB->setValue(_info->bBegin);
    ui->bEndB->setValue(_info->bEnd);

    ui->cellSB->setValue(_info->cellSize);
    ui->fstB->setValue(_info->fstImpact);
    ui->heightSP->setValue(_info->height);
    ui->widthSB->setValue(_info->width);
    ui->lBeginB->setValue(_info->lBegin);
    ui->lEndB->setValue(_info->lEnd);
    ui->scdB->setValue(_info->sndImpact);
    ui->xorRB->setChecked(false);
    ui->replaceRB->setChecked(true);

}

void ParamsWidget::setParams() {
    _info->bBegin = ui->bBeingB->value();
    _info->bEnd = ui->bEndB->value();
    _info->cellSize = ui->cellSB->value();
    _info->fstImpact = ui->fstB->value();
    _info->height = ui->heightSP->value();
    _info->width = ui->widthSB->value();
    _info->lBegin = ui->lBeginB->value();
    _info->lEnd = ui->lEndB->value();
    _info->lEnd = ui->lEndB->value();
    _info->sndImpact = ui->scdB->value();

    _info->mode = ui->replaceRB->isChecked() ? Utils::REPLACE : Utils::XOR;
}


QRadioButton *ParamsWidget::getXorRB() const
{
    return ui->xorRB;
}

QRadioButton *ParamsWidget::getRepRB() const
{
    return ui->replaceRB;
}

void ParamsWidget::reconstruct()
{
    setParams();
    LifeArea *area = static_cast<LifeArea*>(parentWidget());

    if(!((_info->lBegin > _info->bBegin) || (_info->bEnd > _info->lEnd))){
        _model->setInfo(*_info);
        int h = _info->cellSize * 2 * _info->height;
        int w = _info->cellSize * 2 * _info->width;
        area->resizeImage(w,h);
        area->drawField();
        area->update();
    }else{
        QMessageBox box;
        box.setText("Must be LIVE_BEGIN ≤ BIRTH_BEGIN ≤ BIRTH_END ≤ LIVE_END.");
        box.exec();
    }
    if(area->created()){
        _model->clear();
        _main->getParser()->setPathToFile("");
    }
}


infoLife *ParamsWidget::getInfo() const
{
    return _info;
}

void ParamsWidget::setInfo(infoLife *info)
{
    _info = info;
}
