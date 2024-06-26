/**
 * @file main.cpp
 * @brief Tic-Tac-Toe Game Application
 *
 * This application implements a Tic-Tac-Toe game where users can play against each other
 * or against various levels of AI. It allows users to view their game history, replay
 * past games, and manage their profile settings.
 */

#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include <QCursor>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
