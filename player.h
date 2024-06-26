#ifndef PLAYER_H
#define PLAYER_H

#include "session.h"

#include <QImage>

class Player {

private:
    int id;
    int sessionsCount = 0;
    QString username;
    QString hashedPassword;
    QImage image;

    QVector<Session> sessions;

public:
    // Constructors
    Player(): sessionsCount(0) {}
    Player(const int id, QString username, QString hashedPassword, QImage image);

    // Getters
    QString getUsername() const;
    QString getHashedPassword() const;
    int getId() const;
    int getSessionsCount() const;
    QVector<Session> getSessions();
    QImage getImage();

    // Setters
    void setSessionsCount(int count);
    void setId(int &id);
    void setImage(QImage &image);
    void setUsername(QString &username);
    void setHashedPassword(QString &password);
    void setSessions(QVector<Session> &sessions);

    // Session management
    void addSession(Session session);
    void removeSessionAt(int index);
    void updateSessionAt(int index, Session session);
};

#endif // PLAYER_H
