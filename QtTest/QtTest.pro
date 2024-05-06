QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_testcase.cpp \
    ../databasemanager.cpp \
    ../game.cpp \
    ../main.cpp \
    ../mainwindow.cpp \
    ../mainwindowFunctions.cpp \
    ../player.cpp \
    ../session.cpp

FORMS += \
    ../mainwindow.ui

HEADERS += \
    ../databasemanager.h \
    ../game.h \
    ../mainwindow.h \
    ../player.h \
    ../session.h
