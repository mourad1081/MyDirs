#-------------------------------------------------
#
# Project created by QtCreator 2015-03-20T19:35:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QMAKE_CXXFLAGS += -std=c++11 -pedantic-errors
TARGET = ElPersonalisator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fichier.cpp

HEADERS  += mainwindow.h \
    fichier.h

FORMS    += mainwindow.ui

RESOURCES += \
    ressources.qrc
