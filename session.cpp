#include "session.h"


Session::Session() {
    currentGame = new Game;
    id = -1;
}

Session::Session(const int id, const QVector<QPair<int, std::string>>& sessionHistory) {
    this->id = id;
    for (const QPair<int, std::string>& game : sessionHistory)
        this->sessionHistory.push_back(game);
}

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
