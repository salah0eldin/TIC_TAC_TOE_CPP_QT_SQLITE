#ifndef DATABASE_H
#define DATABASE_H

#include "sqlite/sqlite3.h" // Include SQLite library header
#include <QDebug>           // Include qDebug for debugging output
#include <QString>          // Include the QString class for Qt string handling

#define DATABASE_ERROR  0       ///< Error code indicating a database operation failure.
#define DATABASE_SUCCESS 1     ///< Success code indicating a successful database operation.
#define USERNAME_TAKEN 2       ///< Error code indicating that the username is already taken.
#define SIGNED_UP 3            ///< Success code indicating successful user registration.
#define WRONG_USERNAME 4       ///< Error code indicating that the username provided is incorrect.
#define WRONG_PASSWORD 5       ///< Error code indicating that the password provided is incorrect.
#define SIGNED_IN 6            ///< Success code indicating successful user authentication.

/**
 * @brief Opens a connection to the SQLite database.
 *
 * This function opens a connection to the SQLite database file named "database.db".
 *
 * @return Pointer to the opened database connection, or nullptr on failure.
 */
sqlite3 *Open_db();

/**
 * @brief Closes the connection to the SQLite database.
 *
 * This function closes the connection to the SQLite database.
 *
 * @param db Pointer to the database connection to close.
 */
void Close_db(sqlite3 *db);

/**
 * @brief Executes an SQL query on the specified SQLite database.
 *
 * This function executes an SQL query on the specified SQLite database.
 *
 * @param db Pointer to the SQLite database connection.
 * @param query SQL query to execute.
 * @return True if execution succeeds, false otherwise.
 */
bool ExecuteQuery(sqlite3 *db, const QString &query);

/**
 * @brief Initializes the database by creating necessary tables if they don't exist.
 *
 * This function initializes the SQLite database by creating necessary tables if they
 * don't already exist. It creates tables for users, sessions, and games.
 *
 * @return True if initialization succeeds, false otherwise.
 */
bool Init_db();

/**
 * @brief Registers a new user by inserting their username and password into the database.
 *
 * This function registers a new user by inserting their username and password into
 * the "users" table of the SQLite database.
 *
 * @param username The username of the new user.
 * @param password The password of the new user.
 * @return SIGNED_UP if registration succeeds, USERNAME_TAKEN if the username is already taken,
 *         DATABASE_ERROR if there is an error in database operation.
 */
int Sign_Up(const QString &username, const QString &password);

/**
 * @brief Authenticates a user by checking if their username and password match records in the database.
 *
 * This function authenticates a user by checking if their username and password match records
 * in the "users" table of the SQLite database.
 *
 * @param username The username of the user to authenticate.
 * @param password The password of the user to authenticate.
 * @return SIGNED_IN if authentication succeeds, WRONG_USERNAME if the username is not found,
 *         WRONG_PASSWORD if the provided password is incorrect, DATABASE_ERROR if there is an error
 *         in database operation.
 */
int Sign_In(const QString &username, const QString &password);

/**
 * @brief Saves a session record into the database.
 *
 * This function saves a session record into the "sessions" table of the SQLite database.
 *
 * @param userid The ID of the user associated with the session.
 * @param against The name of the opponent.
 * @param wins The number of wins in the session.
 * @param loss The number of losses in the session.
 * @param ties The number of ties in the session.
 * @return DATABASE_SUCCESS if insertion succeeds, DATABASE_ERROR if there is an error in database operation.
 */
bool Save_Session(const int &userid, const QString &against, const int &wins,
                  const int &loss, const int &ties);

/**
 * @brief Saves a game record into the database.
 *
 * This function saves a game record into the "games" table of the SQLite database.
 *
 * @param session_id The ID of the session associated with the game.
 * @param playerCharacter The character representing the player.
 * @param moves The sequence of moves made in the game.
 * @return DATABASE_SUCCESS if insertion succeeds, DATABASE_ERROR if there is an error in database operation.
 */
bool Save_Game(const int &session_id, const char &playerCharacter,
               const QString &moves);

#endif // DATABASE_H
