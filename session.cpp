#include "session.h"

// Constructor with initialization of id and games
Session::Session(const int id, const QVector<Game> &games) {
    this->id = id;
    this->games = games;
}

// Sets the id of the session
void Session::setId(const int &id) {
    this->id = id;
}

// Sets the specific id of the session
void Session::setSpecificId(const int &id) {
    this->specificId = id;
}

// Sets the user id associated with the session
void Session::setUserId(const int &id) {
    this->userId = id;
}

// Sets the score (wins, ties, losses) of the session
void Session::setScore(const int &wins, const int &ties, const int &loss) {
    this->score.wins = wins;
    this->score.ties = ties;
    this->score.losses = loss;
}

// Sets the opponent name for the session
void Session::setOpponentName(const QString &name) {
    opponentName = name;
}

// Sets the timestamp of the session
void Session::setTimestamp(const QDateTime &time) {
    timestamp = time;
}

// Sets the list of games for the session
void Session::setGames(const QVector<Game> &games) {
    this->games = games;
}

// Sets the count of games in the session
void Session::setGamesCount(const int &count) {
    gamesCount = count;
}

// Gets the specific id of the session
int Session::getSpecificId() const {
    return specificId;
}

// Gets the count of games in the session
int Session::getGamesCount() const {
    return gamesCount;
}

// Gets the id of the session
int Session::getId() const {
    return id;
}

// Gets the user id associated with the session
int Session::getUserId() const {
    return userId;
}

// Gets the list of games in the session
QVector<Game> Session::getGames() const {
    return games;
}

// Gets a pointer to the list of games in the session
QVector<Game> *Session::getGamesPointer() {
    return &games;
}

// Gets the opponent name for the session
QString Session::getOpponentName() const {
    return opponentName;
}

// Gets the score (wins, ties, losses) of the session
SessionScore Session::getScore() const {
    return score;
}

// Gets the timestamp of the session
QDateTime Session::getTimestamp() const {
    return timestamp;
}

// Adds a game to the session
void Session::addGame(Game game) {
    games.push_back(game); // Add game to the session
    gamesCount++; // Increment games count

    // Update score based on game state
    switch (game.getState().toLatin1()) {
    case 'w':
        score.wins++;
        break;
    case 'n':
    case 't':
        score.ties++;
        break;
    case 'l':
        score.losses++;
        break;
    }
}
