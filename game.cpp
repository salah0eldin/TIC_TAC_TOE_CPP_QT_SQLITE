#include "game.h"

Game::Game() : playerx(nullptr), playero(nullptr), playerturn(false) {
    id = -1;
    resetGame();
}

void Game::makeMove(int row, int col) {
    if (board[row][col] == ' ') {
        if (playerturn) {
            board[row][col] = 'X';
        } else {
            board[row][col] = 'O';
        }
        playerturn = !playerturn;
        emit gameStateChanged(checkWinDraw());
        switchPlayers();
    }
}

char Game::checkWinDraw() {
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return (board[i][0] == 'X') ? PLAYERX_WON : PLAYERO_WON; // Player X or O won
        }
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return (board[0][i] == 'X') ? PLAYERX_WON : PLAYERO_WON; // Player X or O won
            finished = true;
        }
    }


    if ((board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) ||
        (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])) {
        return (board[1][1] == 'X') ? PLAYERX_WON : PLAYERO_WON; // Player X or O won
        finished = true;
    }


    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') {
                return DRAW;
                finished = true;
            }
        }
    }
    return DRAW;
    finished = true;
}

void Game::switchPlayers() {
    currentplayer = (currentplayer == playerx) ? playero : playerx;
    emit currentPlayerChanged(currentplayer->getUsername());
}

void Game::resetGame() {
    // Clear the board
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = ' ';
        }
    }
    finished = false;
}

void Game::loadGame(const int id, const std::string& gameMoves){
    this->id = id;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = gameMoves[(i * 3) + j];
        }
    }
}

QPair<int, std::string> Game::saveGame(){
    std::string gameMoves;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            gameMoves.push_back(board[i][j]);
        }
    }
    return {id, gameMoves};
}


bool Game::isFinished() {
    return finished;
}
