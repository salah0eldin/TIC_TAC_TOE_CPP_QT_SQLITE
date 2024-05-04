#include "databasemanager.h"

DatabaseManager::DatabaseManager() {
    // Open the SQLite database
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");

    // Attempt to open the database
    if (!db.open()) {
        // Print error message if database opening fails
        qDebug() << "Error opening SQLite database: " << db.lastError().text();
        return;
    }

    // SQL query to create the users table if it doesn't exist
    QString query = R"(
        CREATE TABLE IF NOT EXISTS users (
            id       INTEGER      PRIMARY KEY AUTOINCREMENT,
            username VARCHAR(255) UNIQUE NOT NULL,
            password VARCHAR(255) NOT NULL
        );
    )";

    // Execute the SQL query to create the users table
    QSqlQuery sqlQuery(query);
    if (!sqlQuery.exec()) {
        // Print error message if query execution fails
        qDebug() << "Error creating users table: " << sqlQuery.lastError().text();
    }

    // SQL query to create the sessions table if it doesn't exist
    query = R"(
        CREATE TABLE IF NOT EXISTS sessions (
            id            INTEGER      PRIMARY KEY AUTOINCREMENT,
            specificId    INTEGER      NOT NULL,
            userid        INTEGER      NOT NULL,
            against       VARCHAR(255) NOT NULL,
            wins          INTEGER      NOT NULL,
            losses        INTEGER      NOT NULL,
            ties          INTEGER      NOT NULL,
            timestamp     DATETIME     DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (userid) REFERENCES users (id)
        );
    )";

    // Execute the SQL query to create the sessions table
    sqlQuery.prepare(query);
    if (!sqlQuery.exec()) {
        // Print error message if query execution fails
        qDebug() << "Error creating sessions table: "
                 << sqlQuery.lastError().text();
    }

    // SQL query to create the games table if it doesn't exist
    query = R"(
        CREATE TABLE IF NOT EXISTS games (
            id              INTEGER      PRIMARY KEY AUTOINCREMENT,
            session_id      INTEGER      NOT NULL,
            playerCharacter CHAR(1)      NOT NULL,
            moves           VARCHAR(500) NULL,
            state           CHAR(1)      NOT NULL,
            FOREIGN KEY (session_id) REFERENCES sessions (id)
        );
    )";

    // Execute the SQL query to create the games table
    sqlQuery.prepare(query);
    if (!sqlQuery.exec()) {
        // Print error message if query execution fails
        qDebug() << "Error creating games table: " << sqlQuery.lastError().text();
    }
}

int DatabaseManager::signUp(const QString &username, const QString &password) {
    // Prepare SQL query to check if username already exists
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM users WHERE username = ? ");
    selectQuery.addBindValue(username);

    // Execute the query
    if (!selectQuery.exec()) {
        // Print error message if query execution fails
        qDebug() << "Error executing select user up query:"
                 << selectQuery.lastError().text();
        return DATABASE_ERROR; // Return error code
    }

    // Check if the query returned a row (username already exists)
    if (selectQuery.next()) {
        qDebug() << "Username already exists";
        return USERNAME_TAKEN; // Return username taken code
    }

    // Prepare SQL query to insert new user
    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO users (username, password) VALUES (?, ?)");
    insertQuery.addBindValue(username);
    insertQuery.addBindValue(password);

    // Execute the query
    if (!insertQuery.exec()) {
        // Print error message if query execution fails
        qDebug() << "Error executing insert user query:"
                 << insertQuery.lastError().text();
        return DATABASE_ERROR; // Return error code
    }

    qDebug() << "Signed Up";
    return SIGNED_UP; // Return success code
}

int DatabaseManager::signIn(const QString &username, const QString &password,int &id) {
    // Prepare SQL query to retrieve user record based on username
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM users WHERE username = ?");
    selectQuery.addBindValue(username);

    // Execute the query
    if (!selectQuery.exec()) {
        // Print error message if query execution fails
        qDebug() << "Error executing select user in query:"
                 << selectQuery.lastError().text();
        return DATABASE_ERROR; // Return error code
    }

    // Check if the query returned a row (username found)
    if (!selectQuery.next()) {
        qDebug() << "User not found"; // Print user not found message
        return WRONG_USERNAME;        // Return wrong username code
    }

    // Retrieve the stored password from the result set
    QString storedPassword = selectQuery.value("password").toString();

    // Compare the provided password with the stored password
    if (password == storedPassword) {
        qDebug() << "Signed in"; // Print sign-in success message
        id = selectQuery.value("id").toInt();
        return SIGNED_IN;        // Return success code
    } else {
        qDebug() << "Wrong password"; // Print incorrect password message
        return WRONG_PASSWORD;        // Return wrong password code
    }
}

int DatabaseManager::changeUsername(const int &id, const QString &newUsername,
                                    const QString &password) {
    // Prepare SQL query to retrieve user record based on id
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM users WHERE id = ?");
    selectQuery.addBindValue(id);

    // Execute the query
    if (!selectQuery.exec()) {
        // Print error message if query execution fails
        qDebug() << "Error executing select user query:"
                 << selectQuery.lastError().text();
        return DATABASE_ERROR; // Return error code to indicate failure
    }

    selectQuery.next();
    // Retrieve the stored password from the result set
    QString storedPassword = selectQuery.value("password").toString();

    // Compare the provided password with the stored password
    if (password != storedPassword) {
        qDebug() << "Wrong password"; // Print incorrect password message
        return WRONG_PASSWORD;        // Return error code to indicate failure
    }

    // Prepare SQL query to update username
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE users SET username = ? WHERE id = ?");
    updateQuery.addBindValue(newUsername);
    updateQuery.addBindValue(id);

    // Execute the query
    if (!updateQuery.exec()) {
        // Print error message if query execution fails
        qDebug() << "Error executing update username query:"
                 << updateQuery.lastError().text();
        return DATABASE_ERROR; // Return error code to indicate failure
    }

    qDebug() << "changed username";
    return DATABASE_SUCCESS; // Return success code to indicate successful update
}

int DatabaseManager::changePassword(const int &id, const QString &oldPassword,
                                    const QString &newPassword) {
    // Prepare SQL query to retrieve user record based on id
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM users WHERE id = ?");
    selectQuery.addBindValue(id);

    // Execute the query
    if (!selectQuery.exec()) {
        // Print error message if query execution fails
        qDebug() << "Error executing select user query:"
                 << selectQuery.lastError().text();
        return DATABASE_ERROR; // Return error code to indicate failure
    }

    selectQuery.next();
    // Retrieve the stored password from the result set
    QString storedPassword = selectQuery.value("password").toString();

    // Compare the provided password with the stored password
    if (oldPassword != storedPassword) {
        qDebug() << "Wrong password"; // Print incorrect password message
        return WRONG_PASSWORD;        // Return error code to indicate failure
    }

    // Prepare SQL query to update password
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE users SET password = ? WHERE id = ?");
    updateQuery.addBindValue(newPassword);
    updateQuery.addBindValue(id);

    // Execute the query
    if (!updateQuery.exec()) {
        // Print error message if query execution fails
        qDebug() << "Error executing update password query:"
                 << updateQuery.lastError().text();
        return DATABASE_ERROR; // Return error code to indicate failure
    }

    qDebug() << "changed password";
    return DATABASE_SUCCESS; // Return success code to indicate successful update
}


bool DatabaseManager::saveSession(const int &specificId,const int &userid, const QString &against, const int &wins,
                                  const int &losses, const int &ties)
{
    // Prepare SQL query to insert new session
    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO sessions (specificId, userid, against, wins, losses, ties) "
                        "VALUES (?, ?, ?, ?, ?, ?)");
    insertQuery.addBindValue(specificId);
    insertQuery.addBindValue(userid);
    insertQuery.addBindValue(against);
    insertQuery.addBindValue(wins);
    insertQuery.addBindValue(losses);
    insertQuery.addBindValue(ties);

    // Execute the query
    if (!insertQuery.exec()) {
        // Print error message if query execution fails
        qDebug() << "Error executing insert session query:"
                 << insertQuery.lastError().text();
        return DATABASE_ERROR; // Return false to indicate failure
    }

    return DATABASE_SUCCESS; // Return true to indicate successful insertion
}

bool DatabaseManager::saveGame(const int &session_id,
                               const char &playerCharacter,
                               const QString &moves, const QString &state) {
    // Prepare SQL query to insert a new game
    QSqlQuery insertQuery;
    insertQuery.prepare(
        "INSERT INTO games (session_id, playerCharacter, moves, state) "
        "VALUES (?, ?, ?, ?)");
    insertQuery.addBindValue(session_id);
    insertQuery.addBindValue(QString(playerCharacter));
    insertQuery.addBindValue(moves);
    insertQuery.addBindValue(state);

    // Execute the query
    if (!insertQuery.exec()) {
        // Print error message if query execution fails
        qDebug() << "Error executing insert game query:"
                 << insertQuery.lastError().text();
        return DATABASE_ERROR; // Return false to indicate failure
    }

    return DATABASE_SUCCESS; // Return true to indicate successful insertion
}
