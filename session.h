#ifndef SESSION_H
#define SESSION_H

#include <QVector>
#include <QPair>
#include <QDateTime>

#include "game.h"

#define HUMAN   0
#define AI_EASY    1
#define AI_MED    2
#define AI_HARD    3

struct SessionScore {
    int wins = 0;
    int ties = 0;
    int losses = 0;
};

class Session
{
private:
    int id;
    int specificId;
    int gamesCount;
    int userId;

    QString opponentName;

    SessionScore score;

    QDateTime timestamp;
    QVector<Game> games;


public:
    Session():id(-1),gamesCount(0){};
    Session(const int id, const QVector<Game> &games);
    void setId(const int &id);
    void setSpecificId(const int &id);
    void setUserId(const int &id);
    void setScore(const int &wins,const int &ties, const int &loss);
    void setOpponentName(const QString &name);
    void setTimestamp(const QDateTime &time);
    void setGames(const QVector<Game> &games);
    void setGamesCount(const int &count);
    void setType(int type);
    int getType() const;
    int getSpecificId() const;
    int getGamesCout() const;
    int getId() const;
    int getUserId() const;
    QVector<Game> getGames() const;
    QVector<Game> *getGamesPointer();

    QString getOpponentName() const;
    SessionScore getScore() const;
    QDateTime getTimestamp() const;
    void addGame(Game game);
    int type;
};

#endif // SESSION_H
