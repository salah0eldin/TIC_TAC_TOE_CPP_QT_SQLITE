#include "game.h"

/**
 * Constructor for the Game class.
 * Initializes the Game object with default values.
 * Sets the players to nullptr, player turn to false, and id to -1.
 * Calls the resetGame() method to reset the game state.
 *
 * @returns None
 */
Game::Game() : playerx(nullptr), playero(nullptr), playerturn(false) {
    id = -1;
    resetGame();
}

/**
 * Makes a move in the game at the specified row and column.
 *
 * @param row The row index of the move.
 * @param col The column index of the move.
 *
 * @returns None
 */
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

/**
 * Checks the current state of the game board to determine if there is a winner or a draw.
 *
 * @return The result of the game: PLAYERX_WON, PLAYERO_WON, or DRAW.
 */
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

/**
 * Switches the current player in the game.
 *
 * This function toggles the current player between 'playerx' and 'playero'.
 * It emits a signal 'currentPlayerChanged' with the username of the new current player.
 *
 * @returns None
 */
void Game::switchPlayers() {
    currentplayer = (currentplayer == playerx) ? playero : playerx;
    emit currentPlayerChanged(currentplayer->getUsername());
}

/**
 * Resets the game board and sets the game state to unfinished.
 *
 * @param None
 *
 * @returns None
 */
void Game::resetGame() {
    // Clear the board
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = ' ';
        }
    }
    finished = false;
}

/**
 * Loads a game state from a string of game moves into the board.
 *
 * @param id The identifier of the game.
 * @param gameMoves A string representing the game moves.
 *
 * @returns None
 */
void Game::loadGame(const int id, const std::string& gameMoves){
    this->id = id;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = gameMoves[(i * 3) + j];
        }
    }
}

/**
 * Saves the current game state by serializing the game moves.
 *
 * @return A QPair containing the game ID and serialized game moves.
 */
QPair<int, std::string> Game::saveGame(){
    std::string gameMoves;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            gameMoves.push_back(board[i][j]);
        }
    }
    return {id, gameMoves};
}


/**
 * Check if the game is finished.
 *
 * @return true if the game is finished, false otherwise.
 */
bool Game::isFinished() {
    return finished;
}
