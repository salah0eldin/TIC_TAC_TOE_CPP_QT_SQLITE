#ifndef GAME_H
#define GAME_H

#include <QString>

class Game{

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
    QChar board[3][3];
    Game():id(-1),playerChar('X'),oppoChar('O'){resetGame();specifiedId=0;playerIsFirst=true;playerturn=true;};
    void makeMove(int row, int col);
    QChar getState();
    QChar checkWinDraw();
    void resetGame();
    void loadGame(const int id, const std::string& gameMoves);
    void setSessionId(const int&id);
    void setId(int gameId);
    void setPlayerIsFirst(bool Turn);
    void setMoves(const QString &gameMoves);
    void setState(QChar gameState);
    void setSpecifiedId(const int &id);
    void setPlayerCharacter(const QChar&c);
    int getSpeceifiedId() const;
    int getSessionId() const;
    int getId() const;
    QString getPlayerIsFirst() const;
    QString getMoves();
    bool playerturn = true;

};

#endif // GAME_H
