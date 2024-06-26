
QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aiAlgorithm.cpp \
    aiPage.cpp \
    boardPage.cpp \
    changepasswordPage.cpp \
    changeusernamePage.cpp \
    databasemanager.cpp \
    game.cpp \
    gamesPage.cpp \
    main.cpp \
    mainwindow.cpp \
    player.cpp \
    profilePage.cpp \
    session.cpp \
    sessionsPage.cpp \
    signinPage.cpp \
    signupPage.cpp

HEADERS += \
    aiAlgorithm.h \
    databasemanager.h \
    game.h \
    mainwindow.h \
    player.h \
    session.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    BUILD.bazel \
    WORKSPACE \
    pictures/aaa.jpg \
    pictures/bg.png \
    pictures/password.png \
    pictures/user.jpg
