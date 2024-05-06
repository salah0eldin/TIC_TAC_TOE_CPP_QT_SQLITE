#ifndef GAME_H
#define GAME_H

#include <QString>

class Game{

private:
    int id;

    QChar board[3][3];
    QChar playerChar;
    QChar oppoChar;
    QChar state;

    bool playerIsFirst;
    bool playerturn;

    QString moves;

public:
    Game();
    void makeMove(int row, int col);
    QChar getState();
    QChar checkWinDraw();
    void resetGame();
    void loadGame(const int id, const std::string& gameMoves);
    void setId(int gameId);
    void setPlayerCharacter(QChar character);
    void setPlayerIsFirst(bool Turn);
    void setMoves(const QString &gameMoves);
    void setState(QChar gameState);

    QString getMoves();
};

#endif // GAME_H
