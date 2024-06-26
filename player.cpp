
#include "player.h"


Player::Player(const int id, QString username, QString hashedPassword,QImage imagee)
    : id(id), username(username), hashedPassword(hashedPassword) ,image(imagee) { sessionsCount = 0;}

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
    sessionsCount++;
}

void Player::removeSessionAt(int index){
    sessions.removeAt(index);
}

void Player::updateSessionAt(int index,Session session){
    sessions[index] = session;
}

QImage Player::getImage(){
    return image;
}

QVector<Session> Player::getSessions(){
    return sessions;
}
void Player::setSessoinsCount(int count){
    sessionsCount = count;
}
int Player::getSessionsCount() const {
    return sessionsCount;
}
void Player::setId(int &id){
    this->id = id;
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

void Player::setSessions(QVector<Session> &sessions){
    this->sessions = sessions;
}
