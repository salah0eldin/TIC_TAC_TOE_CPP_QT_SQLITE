#include "player.h"

// Constructor
Player::Player(const int id, QString username, QString hashedPassword, QImage imagee)
    : id(id), username(username), hashedPassword(hashedPassword), image(imagee)
{
    sessionsCount = 0;
}

// Getter for username
QString Player::getUsername() const {
    return username;
}

// Getter for hashed password
QString Player::getHashedPassword() const {
    return hashedPassword;
}

// Getter for player ID
int Player::getId() const {
    return id;
}

// Method to add a session to the player's sessions list
void Player::addSession(Session session) {
    sessions.push_back(session);
    sessionsCount++;
}

// Method to remove a session from the player's sessions list at a specific index
void Player::removeSessionAt(int index) {
    sessions.removeAt(index);
}

// Method to update a session in the player's sessions list at a specific index
void Player::updateSessionAt(int index, Session session) {
    sessions[index] = session;
}

// Getter for player's image
QImage Player::getImage() {
    return image;
}

// Getter for player's sessions
QVector<Session> Player::getSessions() {
    return sessions;
}

// Setter for sessions count
void Player::setSessionsCount(int count) {
    sessionsCount = count;
}

// Getter for sessions count
int Player::getSessionsCount() const {
    return sessionsCount;
}

// Setter for player ID
void Player::setId(int &id) {
    this->id = id;
}

// Setter for player's image
void Player::setImage(QImage &image) {
    this->image = image;
}

// Setter for player's username
void Player::setUsername(QString &username) {
    this->username = username;
}

// Setter for player's hashed password
void Player::setHashedPassword(QString &password) {
    this->hashedPassword = password;
}

// Setter for player's sessions
void Player::setSessions(QVector<Session> &sessions) {
    this->sessions = sessions;
}
QString Player::getName() const {
    return username;  // Assuming 'username' is where the player's name is stored
}

void Player::setName(const QString &name) {
    username = name;  // Update the player's name
}

