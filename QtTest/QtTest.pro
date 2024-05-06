QT += testlib
QT += gui sql
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_testcase.cpp \
    ../game.cpp \
    ../player.cpp \
    ../session.cpp

FORMS += \
    ../mainwindow.ui

HEADERS += \
    ../game.h \
    ../player.h \
    ../session.h

TARGET = MyQtTest

