#ifndef GAME_H
#define GAME_H

#include <QString>

class Game {

private:
    int id;
    int sessionId;
    int specifiedId;
    QChar playerChar;
    QChar oppoChar;
    QChar state = 'n';
    bool playerIsFirst;
    QString moves;

public:
    // Constructors and initialization
    QChar board[3][3];
    Game(): id(-1), playerChar('X'), oppoChar('O') {
        resetGame();
        specifiedId = 0;
        playerIsFirst = true;
        playerturn = true;
    };

    // Methods for gameplay
    void makeMove(int row, int col);
    QChar getState();
    QChar checkWinDraw();
    void resetGame();
    void loadGame(const int id, const std::string& gameMoves);

    // Setters
    void setSessionId(const int &id);
    void setId(int gameId);
    void setPlayerIsFirst(bool Turn);
    void setMoves(const QString &gameMoves);
    void setState(QChar gameState);
    void setSpecifiedId(const int &id);
    void setPlayerCharacter(const QChar &c);

    // Getters
    int getSpeceifiedId() const;
    int getSessionId() const;
    int getId() const;
    QString getPlayerIsFirst() const;
    QString getMoves();

    // Public member variable
    bool playerturn = true;
};

#endif // GAME_H
