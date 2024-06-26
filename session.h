#ifndef SESSION_H
#define SESSION_H

#include <QVector>
#include <QDateTime>

#include "game.h"

// Constants defining session types
#define HUMAN   0
#define AI_EASY 1
#define AI_MED  2
#define AI_HARD 3

// Structure to hold session scores
struct SessionScore {
    int wins = 0;
    int ties = 0;
    int losses = 0;
};

class  Session
{
private:
    // Session attributes
    int id;
    int specificId;
    int gamesCount;
    int userId;
    QString opponentName;
    SessionScore score;
    QDateTime timestamp;
    QVector<Game> games;

public:
    int type;

    // Default constructor
    Session():id(-1),gamesCount(0){};

    // Constructor with initialization
    Session(int id, const QVector<Game> &games);

    // Method to add a game to the session
    void addGame(Game game);

    // Setter methods
    void setId(const int &id);
    void setSpecificId(const int &id);
    void setUserId(const int &id);
    void setScore(const int &wins, const int &ties, const int &loss);
    void setOpponentName(const QString &name);
    void setTimestamp(const QDateTime &time);
    void setGames(const QVector<Game> &games);
    void setGamesCount(const int &count);

    // Getter methods
    int getId() const;
    int getSpecificId() const;
    int getGamesCount() const;
    int getUserId() const;
    QString getOpponentName() const;
    SessionScore getScore() const;
    QDateTime getTimestamp() const;
    QVector<Game> getGames() const;
    QVector<Game> *getGamesPointer();
};

#endif // SESSION_H
