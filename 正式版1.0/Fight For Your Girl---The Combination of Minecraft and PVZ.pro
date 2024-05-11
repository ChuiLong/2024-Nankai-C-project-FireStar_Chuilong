QT       += multimedia
QT       += core gui sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Fight

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
    mainwindow.cpp \
    cheat.cpp \
    database.cpp \
    player.cpp \
    view.cpp

HEADERS += mainwindow.h \
    cheat.h \
    database.h \
    player.h \
    monster.h \
    tools.h \
    keys.h \
    view.h

RESOURCES += \
    application.qrc
