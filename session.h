#ifndef SESSION_H
#define SESSION_H

#include <QVector>
#include <QPair>
#include <QDateTime>

#include "game.h"

class Session
{
private:
    int id;
    int specificId;
    int userId;
    QString opponentName;
    struct SessionScore {
        int wins = 0;
        int ties = 0;
        int losses = 0;
    } score;

    QDateTime timestamp;
    QVector<Game> games;


public:
    Session();
    Session(const int id, const QVector<Game> &games);
    void setId(const int &id);
    void setSpecificId(const int &id);
    void setUserId(const int &id);
    void setScore(const int &wins,const int &ties, const int &loss);
    void setOpponentName(const QString &name);
    void setTimestamp(const QDateTime &time);
    void setGames(const QVector<Game> &games);

    int getId() const;
    QVector<Game> getGames() const;
    QString getOpponentName() const;
    SessionScore getScore() const;
    QDateTime getTimestamp() const;
    void addGame(Game game);
};

#endif // SESSION_H
