#include "database.h"

/**
 * @brief Opens a connection to the SQLite database.
 *
 * This function attempts to open the SQLite database named "database.db" and
 * returns a pointer to the opened database connection.
 *
 * @return Pointer to the opened database connection, or nullptr on failure.
 */
sqlite3 *Open_db() {
    sqlite3 *db;
    // Attempt to open the SQLite database
    int result = sqlite3_open("database.db", &db);
    if (result != SQLITE_OK) {
        // Print error message if database opening fails
        qDebug() << "Error opening SQLite database: " << sqlite3_errmsg(db);
        // Close the database connection
        sqlite3_close(db);
        return nullptr; // Return nullptr to indicate failure
    }
    return db; // Return pointer to the opened database connection
}

/**
 * @brief Closes the connection to the SQLite database.
 *
 * This function closes the connection to the SQLite database.
 *
 * @param db Pointer to the database connection to close.
 */
void Close_db(sqlite3 *db) {
    // Check if the database connection pointer is valid
    if (db)
        // Close the database connection
        sqlite3_close(db);
}

/**
 * @brief Executes an SQL query on the specified SQLite database.
 *
 * This function executes the given SQL query on the specified SQLite database
 * connection. It returns `DATABASE_SUCCESS` if the query execution is
 * successful, and `DATABASE_ERROR` otherwise.
 *
 * @param db Pointer to the SQLite database connection.
 * @param query SQL query to execute.
 * @return `DATABASE_SUCCESS` on success, `DATABASE_ERROR` on failure.
 */
bool ExecuteQuery(sqlite3 *db, const QString &query) {
    char *error_message = nullptr;

    // Execute the SQL query
    int result = sqlite3_exec(db, query.toUtf8().constData(), nullptr, nullptr,
                              &error_message);

    // Check for errors
    if (result != SQLITE_OK) {
        // Print error message if query execution fails
        qDebug() << "Error executing query: " << error_message;
        // Free error message memory
        sqlite3_free(error_message);
        return DATABASE_ERROR; // Return failure
    }

    return DATABASE_SUCCESS; // Return success
}

/**
 * @brief Initializes the database by creating necessary tables if they don't
 * exist.
 *
 * This function initializes the SQLite database by creating the necessary
 * tables if they do not already exist. It returns `DATABASE_SUCCESS` if the
 * initialization is successful, and `DATABASE_ERROR` otherwise.
 *
 * @return `DATABASE_SUCCESS` on successful initialization, `DATABASE_ERROR` on failure.
 */
bool Init_db() {
    // Open the SQLite database
    sqlite3 *db = Open_db();

    // Check if the database connection is valid
    if (db == nullptr)
        return DATABASE_ERROR; // Return false if database opening fails

    // SQL query to create the necessary tables if they don't exist
    QString query = R"(
        CREATE TABLE IF NOT EXISTS users (
            id       INTEGER      PRIMARY KEY AUTOINCREMENT,
            username VARCHAR(255) UNIQUE NOT NULL,
            password VARCHAR(255) NOT NULL
        );
        CREATE TABLE IF NOT EXISTS sessions (
            id            INTEGER      PRIMARY KEY AUTOINCREMENT,
            userid        INTEGER      NOT NULL,
            against       VARCHAR(255) NOT NULL,
            wins          INTEGER      NOT NULL,
            losses        INTEGER      NOT NULL,
            ties          INTEGER      NOT NULL,
            numberofgames INTEGER      NOT NULL,
            timestamp     DATETIME     DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (userid) REFERENCES users (id)
        );
        CREATE TABLE IF NOT EXISTS games (
            id              INTEGER      PRIMARY KEY AUTOINCREMENT,
            session_id      INTEGER      NOT NULL,
            playerCharacter CHAR(1)      NOT NULL,
            moves           VARCHAR(500) NULL,
            state           VARCHAR(500) NOT NULL,
            FOREIGN KEY (session_id) REFERENCES sessions (id)
        );
    )";

    // Execute the SQL query to create the necessary tables
    ExecuteQuery(db, query);

    // Close the database connection
    Close_db(db);

    return DATABASE_SUCCESS; // Return true to indicate successful initialization
}

/**
 * @brief Registers a new user by inserting their username and password into the
 * database.
 *
 * This function registers a new user by inserting their username and password
 * into the "users" table of the SQLite database. It returns `SIGNED_UP` if the
 * registration is successful, `DATABASE_ERROR` if there is an error in database
 * operation, and `USERNAME_TAKEN` if the username is already in use.
 *
 * @param username The username of the new user.
 * @param password The password of the new user.
 * @return `SIGNED_UP` on successful registration, `DATABASE_ERROR` on database
 * operation error, `USERNAME_TAKEN` if the username is already in use.
 */
int Sign_Up(const QString &username, const QString &password) {
    // Open the SQLite database
    sqlite3 *db = Open_db();
    // Check if the database connection is valid
    if (db == nullptr)
        return DATABASE_ERROR; // Return false if database opening fails

    // Check if username already exists
    QString select_query = "SELECT * FROM users WHERE username = ?";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, select_query.toUtf8().constData(), -1, &stmt,
                                nullptr);
    if (rc != SQLITE_OK) {
        // Print error message if preparing statement fails
        qDebug() << "Error preparing statement: " << sqlite3_errmsg(db);
        // Close the database connection
        Close_db(db);
        return DATABASE_ERROR; // Return false to indicate failure
    }
    // Bind username parameter to the prepared statement
    sqlite3_bind_text(stmt, 1, username.toUtf8().constData(), -1,
                      SQLITE_TRANSIENT);
    // Execute the statement
    rc = sqlite3_step(stmt);
    // Check if the query returned a row (username already exists)
    if (rc == SQLITE_ROW) {
        qDebug() << "Username already exists";
        // Finalize the statement
        sqlite3_finalize(stmt);
        // Close the database connection
        Close_db(db);
        return USERNAME_TAKEN; // Return false to indicate failure
    }
    // Finalize the statement
    sqlite3_finalize(stmt);

    // Insert new user
    QString insert_query = "INSERT INTO users (username, password) VALUES (?, ?)";
    rc = sqlite3_prepare_v2(db, insert_query.toUtf8().constData(), -1, &stmt,
                            nullptr);
    if (rc != SQLITE_OK) {
        // Print error message if preparing statement fails
        qDebug() << "Error preparing statement: " << sqlite3_errmsg(db);
        // Close the database connection
        Close_db(db);
        return DATABASE_ERROR; // Return false to indicate failure
    }
    // Bind username and password parameters to the prepared statement
    sqlite3_bind_text(stmt, 1, username.toUtf8().constData(), -1,
                      SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, password.toUtf8().constData(), -1,
                      SQLITE_TRANSIENT);
    // Execute the statement
    rc = sqlite3_step(stmt);
    // Check if the execution was successful
    if (rc != SQLITE_DONE) {
        // Print error message if insertion fails
        qDebug() << "Error inserting user: " << sqlite3_errmsg(db);
        // Finalize the statement
        sqlite3_finalize(stmt);
        // Close the database connection
        Close_db(db);
        return DATABASE_ERROR; // Return false to indicate failure
    }
    // Finalize the statement
    sqlite3_finalize(stmt);

    // Close the database connection
    Close_db(db);

    return SIGNED_UP; // Return true to indicate successful registration
}

/**
 * @brief Authenticates a user by checking if their username and password match
 * records in the database.
 *
 * This function authenticates a user by checking if their username and password
 * match records in the "users" table of the SQLite database. It returns
 * `SIGNED_IN` if the authentication is successful, `DATABASE_ERROR` if there
 * is an error in database operation, `WRONG_PASSWORD` if the provided password
 * is incorrect, and `WRONG_USERNAME` if the username is not found.
 *
 * @param username The username of the user to authenticate.
 * @param password The password of the user to authenticate.
 * @return `SIGNED_IN` on successful authentication, `DATABASE_ERROR` on database
 * operation error, `WRONG_PASSWORD` if the provided password is incorrect, and
 * `WRONG_USERNAME` if the username is not found.
 */
int Sign_In(const QString &username, const QString &password) {
    // Open the SQLite database
    sqlite3 *db = Open_db();
    // Check if the database connection is valid
    if (db == nullptr)
        return DATABASE_ERROR; // Return false if database opening fails

    // SQL query to retrieve user record based on username
    QString select_query = "SELECT * FROM users WHERE username = ?";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(db, select_query.toUtf8().constData(), -1, &stmt,
                                nullptr);
    if (rc != SQLITE_OK) {
        // Print error message if preparing statement fails
        qDebug() << "Error preparing statement: " << sqlite3_errmsg(db);
        // Close the database connection
        Close_db(db);
        return DATABASE_ERROR; // Return false to indicate failure
    }
    // Bind username parameter to the prepared statement
    sqlite3_bind_text(stmt, 1, username.toUtf8().constData(), -1,
                      SQLITE_TRANSIENT);
    // Execute the statement
    rc = sqlite3_step(stmt);
    // Check if the query returned a row (username found)
    if (rc == SQLITE_ROW) {
        // Retrieve the stored password from the result set
        const unsigned char *stored_password = sqlite3_column_text(stmt, 2);
        // Compare the provided password with the stored password
        if (stored_password &&
            QString::compare(password, reinterpret_cast<const char *>(stored_password)) == 0) {
            qDebug() << "Signed in"; // Print sign-in success message
            // Finalize the statement
            sqlite3_finalize(stmt);
            // Close the database connection
            Close_db(db);
            return SIGNED_IN; // Return true to indicate successful authentication
        } else {
            qDebug() << "Wrong password"; // Print incorrect password message

            // Finalize the statement
            sqlite3_finalize(stmt);
            // Close the database connection
            Close_db(db);
            return WRONG_PASSWORD; // Return false to indicate authentication failure
        }
    } else {
        qDebug() << "User not found"; // Print user not found message
    }

    // Finalize the statement
    sqlite3_finalize(stmt);
    // Close the database connection
    Close_db(db);
    return WRONG_USERNAME; // Return false to indicate authentication failure
}

/**
 * @brief Saves a session record into the database.
 *
 * This function saves a session record into the "sessions" table of the SQLite
 * database. It takes the user ID, opponent name, wins, losses, and ties as
 * input parameters. It calculates the total number of games played and inserts
 * all the information into the database. It returns `DATABASE_SUCCESS` on
 * successful insertion and `DATABASE_ERROR` if there is an error in database
 * operation.
 *
 * @param userid The ID of the user associated with the session.
 * @param against The name of the opponent.
 * @param wins The number of wins in the session.
 * @param losses The number of losses in the session.
 * @param ties The number of ties in the session.
 * @return `DATABASE_SUCCESS` on successful insertion, `DATABASE_ERROR` on failure.
 */
bool Save_Session(const int &userid, const QString &against, const int &wins,
                  const int &losses, const int &ties) {
    // Open the SQLite database
    sqlite3 *db = Open_db();
    // Check if the database connection is valid
    if (db == nullptr)
        return DATABASE_ERROR; // Return false if database opening fails

    sqlite3_stmt *stmt;
    // Calculate number of games by summing wins, losses, and ties
    int numberofgames = wins + losses + ties;
    QString insert_query = "INSERT INTO sessions (userid, against, wins, losses, ties, numberofgames) VALUES ("
                            "'" + QString::number(userid) + "', ? ,"
                            "'" + QString::number(wins) + "', "
                            "'" + QString::number(losses) + "', "
                            "'" + QString::number(ties) + "', "
                            "'" + QString::number(numberofgames) + "')";

    int rc = sqlite3_prepare_v2(db, insert_query.toUtf8().constData(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        // Print error message if preparing statement fails
        qDebug() << "Error preparing statement: " << sqlite3_errmsg(db);
        // Close the database connection
        Close_db(db);
        return DATABASE_ERROR; // Return false to indicate failure
    }

    sqlite3_bind_text(stmt, 1, against.toUtf8().constData(), -1, SQLITE_TRANSIENT);

    // Execute the statement
    rc = sqlite3_step(stmt);
    // Check if the execution was successful
    if (rc != SQLITE_DONE) {
        // Print error message if insertion fails
        qDebug() << "Error inserting session: " << sqlite3_errmsg(db);
        // Finalize the statement
        sqlite3_finalize(stmt);
        // Close the database connection
        Close_db(db);
        return DATABASE_ERROR; // Return false to indicate failure
    }

    // Finalize the statement
    sqlite3_finalize(stmt);

    // Close the database connection
    Close_db(db);

    return DATABASE_SUCCESS; // Return true to indicate successful registration
}

/**
 * @brief Saves a game record into the database.
 *
 * This function saves a game record into the "games" table of the SQLite
 * database. It takes the session ID, player character, and moves as input
 * parameters. It inserts all the information into the database. It returns
 * `DATABASE_SUCCESS` on successful insertion and `DATABASE_ERROR` if there is
 * an error in database operation.
 *
 * @param session_id The ID of the session associated with the game.
 * @param playerCharacter The character representing the player.
 * @param moves The sequence of moves made in the game.
 * @return `DATABASE_SUCCESS` on successful insertion, `DATABASE_ERROR` on failure.
 */
bool Save_Game(const int &session_id, const char &playerCharacter,
               const QString &moves) {
    // Open the SQLite database
    sqlite3 *db = Open_db();
    // Check if the database connection is valid
    if (db == nullptr)
        return DATABASE_ERROR; // Return false if database opening fails

    QString insert_query = "INSERT INTO games (session_id, playerCharacter, moves) VALUES ("
                            "'" + QString::number(session_id) + "',"
                            "'" + playerCharacter + "', "
                            "'" + moves.toUtf8().constData() + "')";

    // Execute the query
    if (ExecuteQuery(db, insert_query) != DATABASE_SUCCESS) {
        // Close the database connection
        Close_db(db);
        return DATABASE_ERROR; // Return failure
    }

    // Close the database connection
    Close_db(db);

    return DATABASE_SUCCESS; // Return true to indicate successful registration
}



