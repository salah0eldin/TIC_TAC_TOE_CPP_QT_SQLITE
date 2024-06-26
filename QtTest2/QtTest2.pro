
QT += testlib
QT += gui sql
CONFIG += qt warn_on depend_includepath testcase
CONFIG -= app_bundle
TEMPLATE = app

SOURCES +=  tst_sessionstest.cpp \
    ../databasemanager.cpp \
    ../game.cpp \
    ../player.cpp \
    ../session.cpp

FORMS += \
    ../mainwindow.ui

HEADERS += \
    ../databasemanager.h \
    ../game.h \
    ../player.h \
    ../session.h

TARGET = MyQtTest2

DISTFILES +=
