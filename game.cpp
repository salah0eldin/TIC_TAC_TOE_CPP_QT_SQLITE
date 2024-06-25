#include "game.h"

void Game:: makeMove(int row, int col) {
    if (board[row][col] != 'X' && board[row][col] != 'O') {
        if (playerturn) {
            board[row][col] = playerChar;
        } else {
            board[row][col] = oppoChar;
        }
        playerturn = !playerturn;
        int index = row*3+col;
        moves += QString::number(index);
        state = checkWinDraw();
    }
}

QChar Game::checkWinDraw() {
    // Check rows
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            if (board[i][0] == playerChar)
                return 'w'; // Player wins
            else if (board[i][0] == oppoChar)
                return 'l'; // Player loses
        }
    }

    // Check columns
    for (int j = 0; j < 3; ++j) {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j]) {
            if (board[0][j] == playerChar)
                return 'w'; // Player wins
            else if (board[0][j] == oppoChar)
                return 'l'; // Player loses
        }
    }

    // Check diagonals
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0])) {
        if (board[1][1] == playerChar)
            return 'w'; // Player wins
        else if (board[1][1] == oppoChar)
            return 'l'; // Player loses
    }

    // Check for draw
    bool draw = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                draw = false;
                break;
            }
        }
        if (!draw)
            break;
    }
    if (draw)
        return 't'; // Tie

    // Game not finished
    return 'n';
}


void Game::resetGame() {
    // Clear the board
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = ' ';
        }
    }
    state = 'n';
    specifiedId++;
    playerIsFirst = !playerIsFirst;
    playerturn = playerIsFirst;
    moves = "";
}

void Game::loadGame(const int id, const std::string& gameMoves){
    this->id = id;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = gameMoves[(i * 3) + j];
        }
    }
}

QChar Game::getState(){
    return state;
}
void Game::setSessionId(const int&id){
    sessionId = id;
}
void Game::setId(int gameId) {
    id = gameId;
}

void Game::setPlayerIsFirst(bool Turn){
    playerIsFirst = Turn;
}

void Game::setMoves(const QString &gameMoves) {
    moves = gameMoves;
}

void Game::setState(QChar gameState) {
    state = gameState;
}

void Game::setSpecifiedId(const int &id){
    specifiedId = id;
}

int Game::getSpeceifiedId() const{
    return specifiedId;
}

int Game::getSessionId() const{
    return sessionId;
}

QString Game::getPlayerIsFirst() const{
    return (playerIsFirst?"T":"F");
}

QString Game::getMoves(){
    return moves;
}
