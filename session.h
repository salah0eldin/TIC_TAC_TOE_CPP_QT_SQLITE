#ifndef SESSION_H
#define SESSION_H
#include <QVector>
#include <QPair>
#include "player.h"
#include "game.h"
class Session
{
    int id;
    QVector<QPair<int, std::string>> sessionHistory;
    QPair<int, int> score;
    Player *playerX, *playerO, *currentPlayer;
    bool playerTurn;
    int currentGameIndex;
    Game* currentGame;
public:

    Session();
    Session(const int id, const QVector<QPair<int, std::string>>& sessionHistory);
    void updateScore();
    void saveSession();
};

#endif // SESSION_H
