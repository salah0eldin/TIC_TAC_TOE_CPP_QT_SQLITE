#ifndef SESSION_H
#define SESSION_H

#include <QVector>
#include <QPair>

#include "game.h"

class Session
{
    int id;
    QVector<Game> games;

    struct sessionScore{
        int wins = 0;
        int ties = 0;
        int loss = 0;
    } score;

    QString oppoName;

public:

    Session();
    Session(const int id, const QVector<Game> & games);
    void addGame(Game game);
};

#endif // SESSION_H
