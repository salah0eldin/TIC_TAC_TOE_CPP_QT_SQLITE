#ifndef PLAYER_H
#define PLAYER_H


#include "qobject.h"
#include "session.h"

#include <QImage>

class Player {

private:
    const int id;
    QString username;
    QString hashedPassword;
    QImage image;

    QVector<Session> sessions;


public:
    Player(const int id, QString username, QString hashedPassword, QImage imagee);
    QString getUsername() const;
    QString getHashedPassword() const;
    int getId() const;
    void addSession(Session session);
    void removeSessionAt(int &index);
    QImage getImage();
    void setImage(QImage & image);
    void setUsername(QString &username);
    void setHashedPassword(QString &password);
};
#endif // PLAYER_H


