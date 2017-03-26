#-------------------------------------------------
#
# Project created by QtCreator 2017-02-28T20:23:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Life
TEMPLATE = app
CONFIG += c++11 rtti


SOURCES += \
   src/Cell.cpp \
   src/FileParser.cpp \
   src/Hex.cpp \
   src/LifeArea.cpp \
   src/LifeController.cpp \
   src/LifeModel.cpp \
   src/MainWindow.cpp \
   src/MyGraphics.cpp \
   src/ParamsWidget.cpp \
   main.cpp

HEADERS  +=  src/Cell.h \
   src/Constants.h \
   src/FileParser.h \
   src/Hex.h \
   src/LifeArea.h \
   src/LifeController.h \
   src/LifeModel.h \
   src/MainWindow.h \
   src/MyGraphics.h \
   src/ParamsWidget.h \
    src/paramsstorage.h

INCLUDEPATH = \
    src \

FORMS += src/ParamsWidget.ui

DISTFILES += \
    Data/life.lf
