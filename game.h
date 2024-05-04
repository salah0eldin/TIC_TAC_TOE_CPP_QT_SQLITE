#ifndef GAME_H
#define GAME_H

#include <QString>

class Game{

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
