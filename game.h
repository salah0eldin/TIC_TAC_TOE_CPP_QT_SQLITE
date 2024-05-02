#ifndef GAME_H
#define GAME_H
#include "player.h"
#include <QObject>
#include <QPair>

#define PLAYERX_WON 1
#define DRAW 0
#define PLAYERO_WON -1

class Game : public QObject {

private:
    int id;
    char board[3][3];
    Player* playerx;
    Player* playero;
    Player* currentplayer;
    bool finished;
    bool playerturn;

public:
    Game();
    void makeMove(int row, int col);
    char checkWinDraw();
    void switchPlayers();
    void resetGame();
    bool isFinished();
    void loadGame(const int id, const std::string& gameMoves);
    QPair<int, std::string> saveGame();

signals:
    void currentPlayerChanged(const QString& player);
    void gameStateChanged(const char& gameState);
};

#endif // GAME_H
