
#include "player.h"


Player::Player(const int id, QString username, QString hashedPassword,QImage imagee)
    : id(id), username(username), hashedPassword(hashedPassword) ,image(imagee) {}

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

QImage Player::getImage(){
    return image;
}

void Player::setImage(QImage & image){
    this->image = image;
}

void Player::setUsername(QString &username){
    this->username = username;
}

void Player::setHashedPassword(QString &password){
    this->hashedPassword = password;
}
