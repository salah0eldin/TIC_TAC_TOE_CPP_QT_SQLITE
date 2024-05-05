#include "session.h"

Session::Session() {
    id = -1;
}

Session::Session(const int id, const QVector<Game> & games) {
    this->id = id;
    this->games = games;
}

void Session::setId(const int &id) {
    this->id = id;
}

void Session::setSpecificId(const int &id) {
    this->specificId = id;
}

void Session::setUserId(const int &id) {
    this->userId = id;
}

void Session::setScore(const int &wins,const int &ties, const int &loss){
    this->score.wins = wins;
    this->score.ties = ties;
    this->score.losses = loss;
}

void Session::setOpponentName(const QString &name) {
    opponentName = name;
}

void Session::setTimestamp(const QDateTime &time) {
    timestamp = time;
}

void Session::setGames(const QVector<Game> &games) {
    this->games = games;
}

int Session::getId() const {
    return id;
}

QVector<Game> Session::getGames() const {
    return games;
}

QString Session::getOpponentName() const {
    return opponentName;
}

Session::SessionScore Session::getScore() const {
    return score;
}

QDateTime Session::getTimestamp() const {
    return timestamp;
}

void Session::addGame(Game game) {
    games.push_back(game);
    switch(game.getState().toLatin1()) {
    case 'w':
        score.wins++;
        break;
    case 't':
        score.ties++;
        break;
    case 'l':
        score.losses++;
        break;
    }
}
