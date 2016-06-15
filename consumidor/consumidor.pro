#-------------------------------------------------
#
# Project created by QtCreator 2016-05-23T07:47:49
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = consumidor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    grafico.cpp

HEADERS  += mainwindow.h \
    grafico.h

FORMS    += mainwindow.ui
