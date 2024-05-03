#include "game.h"

Game::Game() :playerturn(false) {
    id = -1;
    resetGame();
}

void Game::makeMove(int row, int col) {
    if (board[row][col] == ' ') {
        if (playerturn) {
            board[row][col] = playerChar;
        } else {
            board[row][col] = oppoChar;
        }
        playerturn = !playerturn;

        state = checkWinDraw();
    }
}

char Game::checkWinDraw() {
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
}

void Game::loadGame(const int id, const std::string& gameMoves){
    this->id = id;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = gameMoves[(i * 3) + j];
        }
    }
}

char Game::getState(){
    return state;
}


