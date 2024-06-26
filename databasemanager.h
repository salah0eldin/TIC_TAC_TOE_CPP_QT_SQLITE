#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QImage>
#include <QtSql>            // Include Qt SQL module
#include <QDebug>           // Include qDebug for debugging output
#include <QVector>
#include "session.h"
#include "game.h"           // Include Game class header

#define DATABASE_ERROR   0     ///< Error code indicating a database operation failure.
#define DATABASE_SUCCESS 1     ///< Success code indicating a successful database operation.
#define USERNAME_TAKEN   2     ///< Error code indicating that the username is already taken.
#define SIGNED_UP        3     ///< Success code indicating successful user registration.
#define WRONG_USERNAME   4     ///< Error code indicating that the username provided is incorrect.
#define WRONG_PASSWORD   5     ///< Error code indicating that the password provided is incorrect.
#define SIGNED_IN        6     ///< Success code indicating successful user authentication.

class DatabaseManager
{
private:
    QSqlDatabase db; ///< The QSqlDatabase object for managing the database connection.

public:

    /**
     * @brief Initializes the database by creating the necessary tables if they don't exist.
     * @details This constructor opens the SQLite database and creates the necessary tables (if they don't exist):
     *          - users
     *          - sessions
     *          - games
     *        If any error occurs during database initialization, appropriate error messages are printed.
     */
    DatabaseManager();

    /**
     * @brief Registers a new user by inserting their username and password into the database.
     * @param username The username of the new user.
     * @param password The password of the new user.
     * @return SIGNED_UP if registration succeeds, USERNAME_TAKEN if the username is already taken,
     *         DATABASE_ERROR if there is an error in database operation.
     */
    int signUp(const QString &username, const QString &password);

    /**
     * @brief Authenticates a user by checking if their username and password match records in the database.
     * @param username The username of the user to authenticate.
     * @param password The password of the user to authenticate.
     * @param id Output parameter to store the ID of the authenticated user.
     * @param image Output parameter to store the user's profile image.
     * @return SIGNED_IN if authentication succeeds, WRONG_USERNAME if the username is not found,
     *         WRONG_PASSWORD if the provided password is incorrect, DATABASE_ERROR if there is an error
     *         in database operation.
     */
    int signIn(const QString &username, const QString &password, int &id, QImage &image);

    /**
     * @brief Changes the username of a user in the database.
     * @param id The ID of the user whose username is to be changed.
     * @param newUsername The new username to be set.
     * @param password The password of the user to authenticate the change.
     * @return DATABASE_SUCCESS if the username is successfully changed,
     *         WRONG_PASSWORD if the provided password is incorrect,
     *         DATABASE_ERROR if there is an error in the database operation.
     */
    int changeUsername(const int &id, const QString &newUsername, const QString &password);

    /**
     * @brief Changes the password of a user in the database.
     * @param id The ID of the user whose password is to be changed.
     * @param oldPassword The current password of the user to authenticate the change.
     * @param newPassword The new password to be set.
     * @return DATABASE_SUCCESS if the password is successfully changed,
     *         WRONG_PASSWORD if the provided old password is incorrect,
     *         DATABASE_ERROR if there is an error in the database operation.
     */
    int changePassword(const int &id, const QString &oldPassword, const QString &newPassword);

    /**
     * @brief Changes the profile image of a user in the database.
     * @param id The ID of the user whose profile image is to be changed.
     * @param imageData The byte array containing the new image data.
     * @return DATABASE_SUCCESS if the image is successfully changed,
     *         DATABASE_ERROR if there is an error in the database operation.
     */
    int changeImage(const int &id, const QByteArray &imageData);

    /**
     * @brief Saves a session record into the database.
     * @param session The Session object containing session details to be saved.
     * @return True if insertion succeeds, false if there is an error in database operation.
     */
    bool saveSession(Session &session);

    /**
     * @brief Saves a game record into the database.
     * @param game The Game object containing game details to be saved.
     * @return True if insertion succeeds, false if there is an error in database operation.
     */
    bool saveGame(Game &game);

    /**
     * @brief Loads all games associated with a session from the database.
     * @param session_id The ID of the session for which games are to be loaded.
     * @return A QVector containing all Game objects loaded from the database.
     */
    QVector<Game> loadGames(const int &session_id);

    /**
     * @brief Loads all historical sessions of a user from the database.
     * @param id The ID of the user for which session history is to be loaded.
     * @return A QVector containing all Session objects loaded from the database.
     */
    QVector<Session> loadHistory(const int &id);
};

#endif // DATABASEMANAGER_H
