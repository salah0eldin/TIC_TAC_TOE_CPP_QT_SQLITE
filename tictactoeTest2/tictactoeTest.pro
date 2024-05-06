QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_testcase.cpp \
    game.cpp \
    player.cpp \
    session.cpp

HEADERS += \
    game.h \
    player.h \
    session.h
