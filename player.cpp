
#include "player.h"

Player::Player(const int id, QString username, QString hashedPassword, QObject *parent)
    : QObject(parent), id(id), username(username), hashedPassword(hashedPassword) {}

QString Player::getUsername() const  {
    return username;
}

QString Player::getHashedPassword() const  {
    return hashedPassword;
}

int Player::getId() const {
    return id;
}
