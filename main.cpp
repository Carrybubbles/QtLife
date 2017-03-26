#include <iostream>
#include "src/MainWindow.h"
#include <QApplication>
#include <src/LifeController.h>
#include "src/FileParser.h"
#include <memory>
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    LifeModel model;
    MainWindow window(&model);
    LifeController controller(&model,&window);
    window.show();
    return app.exec();

}
