#include "session.h"

Session::Session() {
    id = -1;
}

Session::Session(const int id, const QVector<Game> & games) {
    this->id = id;
    this->games = games;
}

void Session::addGame(Game game) {
    games.push_back(game);
    switch(game.getState()){
    case 'w':
        score.wins++;
        break;
    case 't':
        score.ties++;
        break;
    case 'l':
        score.loss++;
        break;
    }
}
