
#include "player.h"

/**
 * Constructs a Player object with the given parameters.
 *
 * @param id The unique identifier of the player.
 * @param username The username of the player.
 * @param hashedPassword The hashed password of the player.
 * @param parent The parent object (optional).
 */
Player::Player(const int id, QString username, QString hashedPassword, QObject *parent)
    : QObject(parent), id(id), username(username), hashedPassword(hashedPassword) {}

/**
 * Returns the username of the player.
 *
 * @return The username of the player as a QString.
 */
QString Player::getUsername() const  {
    return username;
}

/**
 * Retrieve the hashed password of the player.
 *
 * @return The hashed password of the player as a QString.
 */
QString Player::getHashedPassword() const  {
    return hashedPassword;
}

/**
 * Get the ID of the player.
 *
 * @return The ID of the player.
 */
int Player::getId() const {
    return id;
}
