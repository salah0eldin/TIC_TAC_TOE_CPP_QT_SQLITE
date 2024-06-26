QT += testlib
QT += gui sql
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=     tst_aitest.cpp\
    ../aiAlgorithm.cpp

HEADERS += \
    ../aiAlgorithm.h


TARGET = Myaitest
