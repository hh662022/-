#-------------------------------------------------
#
# Project created by QtCreator 2022-05-06T13:39:50
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = uso
TEMPLATE = app


SOURCES += main.cpp \
    accuracy.cpp \
    game.cpp \
    judge.cpp \
    note.cpp \
    playfield.cpp \
    score.cpp

HEADERS  += \
    accuracy.h \
    game.h \
    judge.h \
    note.h \
    playfield.h \
    score.h

FORMS    += \
    form.ui

RESOURCES += \
    res.qrc
