#ifndef PLAYER_H
#define PLAYER_H

#include "qobject.h"
class Player : public QObject {
    Q_OBJECT

private:
    const int id;
    const QString username;
    const QString hashedPassword;

public:
    explicit Player(const int id, QString username, QString hashedPassword, QObject *parent = nullptr);
    QString getUsername() const;
    QString getHashedPassword() const;
    int getId() const;
signals:
};
#endif // PLAYER_H


