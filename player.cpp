
#include "player.h"


Player::Player(const int id, QString username, QString hashedPassword)
    : id(id), username(username), hashedPassword(hashedPassword) {}

QString Player::getUsername() const  {
    return username;
}


QString Player::getHashedPassword() const  {
    return hashedPassword;
}


int Player::getId() const {
    return id;
}

void Player::addSession(Session session){
    sessions.push_back(session);
}

void Player::removeSessionAt(int &index){
    sessions.removeAt(index);
}
