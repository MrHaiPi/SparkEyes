#-------------------------------------------------
#
# Project created by QtCreator 2018-05-28T19:31:43
#
#-------------------------------------------------

QT       += core gui
QT += multimedia
RC_ICONS = sparkeyes.ico

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    gamearea.cpp \
    main.cpp \
    myitem.cpp \
    widget.cpp \
    gamewidget.cpp

HEADERS  += \
    myitem.h \
    widget.h \
    gamearea.h \
    gamewidget.h

FORMS    += \
    widget.ui \
    gamewidget.ui

