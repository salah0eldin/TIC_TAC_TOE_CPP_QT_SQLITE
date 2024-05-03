#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QPair>

#define PLAYERX_WON 1
#define DRAW 0
#define PLAYERO_WON -1

class Game : public QObject {

private:
    int id;

    char board[3][3];
    char playerChar;
    char oppoChar;
    char state;

    bool playerIsFirst;
    bool playerturn;

    QString moves;

public:
    Game();
    void makeMove(int row, int col);
    char getState();
    char checkWinDraw();
    void resetGame();
    void loadGame(const int id, const std::string& gameMoves);
    QString getMoves();
};

#endif // GAME_H
