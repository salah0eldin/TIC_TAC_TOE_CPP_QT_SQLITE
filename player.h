#ifndef PLAYER_H
#define PLAYER_H


#include "qobject.h"
#include "session.h"

class Player {

private:
    const int id;
    const QString username;
    const QString hashedPassword;

    QVector<Session> sessions;


public:
    Player(const int id, QString username, QString hashedPassword);
    QString getUsername() const;
    QString getHashedPassword() const;
    int getId() const;
    void addSession(Session session);
    void removeSessionAt(int &index);
};
#endif // PLAYER_H


