#-------------------------------------------------
#
# Project created by QtCreator 2016-06-04T00:00:22
#
#-------------------------------------------------

QT       += core gui
QT       += sql xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = grade_management
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    login.cpp \
    delete.cpp \
    insert.cpp \
    compute.cpp

HEADERS  += mainwindow.h \
    delete.h \
    login.h \
    insert.h \
    connection.h \
    compute.h

FORMS    += mainwindow.ui \
    login.ui \
    delete.ui \
    insert.ui

RESOURCES += \
    picture.qrc
