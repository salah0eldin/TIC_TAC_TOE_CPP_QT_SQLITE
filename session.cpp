#include "session.h"


/**
 * Constructor for the Session class.
 * Initializes a new Session object with a new Game and sets the id to -1.
 *
 * @param None
 *
 * @returns None
 */
Session::Session() {
    currentGame = new Game;
    id = -1;
}

/**
 * Constructs a Session object with the given id and session history.
 *
 * @param id The unique identifier for the session.
 * @param sessionHistory A vector of pairs representing the game history in the session.
 *
 * @returns None
 */
Session::Session(const int id, const QVector<QPair<int, std::string>>& sessionHistory) {
    this->id = id;
    for (const QPair<int, std::string>& game : sessionHistory)
        this->sessionHistory.push_back(game);
}

/**
 * Updates the score based on the winner of the current game.
 *
 * This function checks the winner of the current game and updates the score accordingly.
 * If the winner is PLAYERX_WON, the score of player X is incremented.
 * If the winner is PLAYERO_WON, the score of player O is incremented.
 *
 * @returns None
 */
void Session::updateScore() {
    char winner = currentGame->checkWinDraw();
    if(winner == PLAYERX_WON)
    {
        score.first++;
    }
    else if(winner == PLAYERO_WON)
    {
        score.second++;
    }
}

/**
 * Saves the current session data.
 *
 * Checks if the session exists based on the session ID.
 * If the session exists, performs the necessary actions.
 * If the session does not exist, handles the case accordingly.
 *
 * Iterates through the session history and checks if each game exists.
 * If the game exists, performs the necessary actions.
 * If the game does not exist, handles the case accordingly.
 *
 * @returns None
 */
void Session::saveSession(){
    bool sessionExist = (id != -1);
    if (sessionExist) {
        // db.updateSession(id, playerX.getId(), score.first, score.second);
    } else {
        // db.insertSession(playerX.getId(), score.first, score.second);
    }
    // for (int i = 0; i < sessionHistory.size(); i++)
    for (const QPair<int, std::string>& game : sessionHistory) {
        bool gameExist = (game.first != -1);
        if (gameExist) {
            // db.updateGame(game.first, game.second);
        } else {
            // db.insertGame(playerX.getId(), score.first, score.second);
        }
    }

}
