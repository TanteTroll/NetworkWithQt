#-------------------------------------------------
#
# Project created by QtCreator 2016-01-16T19:09:46
#
#-------------------------------------------------

QT       += core gui \
network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Network
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    network.cpp \
    server.cpp \
    client.cpp \
    message.cpp

HEADERS  += mainwindow.h \
    network.h \
    server.h \
    client.h \
    message.h

FORMS    += mainwindow.ui \
    server.ui \
    client.ui
