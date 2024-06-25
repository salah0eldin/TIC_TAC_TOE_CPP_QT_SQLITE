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
            password VARCHAR(255) NOT NULL,
            image    BLOB
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
            type          INTEGER      NOT NULL,
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
            specific_id     INTEGER      NOT NULL,
            playerCharacter CHAR(1)      NOT NULL,
            playerIsFirst   CHAR(1)      NOT NULL,
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
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT * FROM users WHERE username = ?");
    checkQuery.addBindValue(username);

    if (!checkQuery.exec()) {
        qDebug() << "Error executing checkQuery:" << checkQuery.lastError().text();
        return DATABASE_ERROR;
    }

    if (checkQuery.next()) {
        qDebug() << "Username already exists";
        return USERNAME_TAKEN;
    }

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO users (username, password) VALUES (?, ?)");
    insertQuery.addBindValue(username);
    insertQuery.addBindValue(password);

    if (!insertQuery.exec()) {
        qDebug() << "Error executing insertQuery:"
                 << insertQuery.lastError().text();
        return DATABASE_ERROR;
    }

    qDebug() << "User signed up successfully";
    return SIGNED_UP;
}

int DatabaseManager::signIn(const QString &username, const QString &password,
                            int &id, QImage &image) {
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
        QByteArray imageData = selectQuery.value("image").toByteArray();

        image.loadFromData(imageData);

        return SIGNED_IN; // Return success code
    } else {
        qDebug() << "Wrong password"; // Print incorrect password message
        return WRONG_PASSWORD;        // Return wrong password code
    }
}

int DatabaseManager::changeUsername(const int &id, const QString &newUsername,
                                    const QString &password) {
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM users WHERE id = ?");
    selectQuery.addBindValue(id);

    if (!selectQuery.exec() || !selectQuery.next()) {
        qDebug() << "User not found";
        return DATABASE_ERROR;
    }

    QString storedPassword = selectQuery.value("password").toString();
    if (password != storedPassword) {
        qDebug() << "Wrong password";
        return WRONG_PASSWORD;
    }

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT * FROM users WHERE username = ?");
    checkQuery.addBindValue(newUsername);

    if (!checkQuery.exec() || checkQuery.next()) {
        qDebug() << "Username already taken";
        return USERNAME_TAKEN;
    }

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE users SET username = ? WHERE id = ?");
    updateQuery.addBindValue(newUsername);
    updateQuery.addBindValue(id);

    if (!updateQuery.exec()) {
        qDebug() << "Error executing updateQuery:"
                 << updateQuery.lastError().text();
        return DATABASE_ERROR;
    }

    qDebug() << "Username changed successfully";
    return DATABASE_SUCCESS;
}

int DatabaseManager::changePassword(const int &id, const QString &oldPassword,
                                    const QString &newPassword) {
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM users WHERE id = ?");
    selectQuery.addBindValue(id);

    if (!selectQuery.exec() || !selectQuery.next()) {
        qDebug() << "User not found";
        return DATABASE_ERROR;
    }

    QString storedPassword = selectQuery.value("password").toString();
    if (oldPassword != storedPassword) {
        qDebug() << "Wrong password";
        return WRONG_PASSWORD;
    }

    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE users SET password = ? WHERE id = ?");
    updateQuery.addBindValue(newPassword);
    updateQuery.addBindValue(id);

    if (!updateQuery.exec()) {
        qDebug() << "Error executing updateQuery:"
                 << updateQuery.lastError().text();
        return DATABASE_ERROR;
    }

    qDebug() << "Password changed successfully";
    return DATABASE_SUCCESS;
}

int DatabaseManager::changeImage(const int &id, const QByteArray &imageData) {

    // Update the image data in the database
    QSqlQuery query;
    query.prepare("UPDATE users SET image = :imageData WHERE id = :id");
    query.bindValue(":imageData", imageData);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Failed to update image in database:"
                 << query.lastError().text();
        return DATABASE_ERROR;
    }

    qDebug() << "Image updated in database successfully!";
    return DATABASE_SUCCESS;
}

bool DatabaseManager::saveSession(Session &session) {

    QSqlQuery insertQuery;
    qDebug()<<session.getId();
    if (session.getId() == -1) {
        // Prepare SQL query to insert new session
        insertQuery.prepare("INSERT INTO sessions (specificId, userid, type, against, "
                            "wins, losses, ties, timestamp) "
                            "VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
        insertQuery.addBindValue(session.getSpecificId());
        insertQuery.addBindValue(session.getUserId());
        insertQuery.addBindValue(session.getType());
        insertQuery.addBindValue(session.getOpponentName());
        insertQuery.addBindValue(session.getScore().wins);
        insertQuery.addBindValue(session.getScore().losses);
        insertQuery.addBindValue(session.getScore().ties);
        insertQuery.addBindValue(QDateTime::currentDateTime());
    } else {
        insertQuery.prepare("UPDATE sessions SET wins = ?, losses = ?, ties = ?, "
                            "timestamp = ? WHERE id = ?");
        insertQuery.addBindValue(session.getScore().wins);
        insertQuery.addBindValue(session.getScore().losses);
        insertQuery.addBindValue(session.getScore().ties);
        insertQuery.addBindValue(QDateTime::currentDateTime());
        insertQuery.addBindValue(session.getId());
    }

    // Execute the query
    if (!insertQuery.exec()) {
        // Print error message if query execution fails
        qDebug() << "Error executing insert session query:"
                 << insertQuery.lastError().text();
        return DATABASE_ERROR; // Return false to indicate failure
    }
    // If a new session was inserted, update the session ID

    int sessionId = insertQuery.lastInsertId().toLongLong();

    if (session.getId() == -1) {
        session.setId(sessionId);
    }

    for (Game game : session.getGames()) {
        qDebug()<<"game"<<game.getId();
        if (game.getId() == -1) {
            game.setSessionId(sessionId);
            saveGame(game);
        }
    }

    return DATABASE_SUCCESS; // Return true to indicate successful insertion
}

bool DatabaseManager::saveGame(Game &game) {
    // Prepare SQL query to insert a new game
    QSqlQuery insertQuery;

    insertQuery.prepare("INSERT INTO games (session_id, specific_id, "
                        "playerCharacter, playerIsFirst, moves, state) "
                        "VALUES (?, ?, ?, ?, ?, ?)");
    insertQuery.addBindValue(game.getSessionId());
    insertQuery.addBindValue(game.getSpeceifiedId());
    insertQuery.addBindValue("X");
    insertQuery.addBindValue(game.getPlayerIsFirst());
    insertQuery.addBindValue(game.getMoves());
    insertQuery.addBindValue(game.getState());

    // Execute the query
    if (!insertQuery.exec()) {
        // Print error message if query execution fails
        qDebug() << "Error executing insert game query:"
                 << insertQuery.lastError().text();
        return DATABASE_ERROR; // Return false to indicate failure
    }

    int gameId = insertQuery.lastInsertId().toLongLong();
    game.setId(gameId);

    return DATABASE_SUCCESS; // Return true to indicate successful insertion
}

QVector<Game> DatabaseManager::loadGames(const int &session_id) {
    QVector<Game> games;

    // Prepare SQL query to select games for a specific session
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM games WHERE session_id = ?");
    selectQuery.addBindValue(session_id);

    // Execute the query
    if (!selectQuery.exec()) {
        // Print error message if query execution fails
        qDebug() << "Error executing select games query:"
                 << selectQuery.lastError().text();
        return games; // Return an empty vector to indicate failure
    }

    // Iterate over the results and create Game objects
    while (selectQuery.next()) {
        Game game;
        game.setId(selectQuery.value("id").toInt());
        game.setSpecifiedId(selectQuery.value("specific_id").toInt());
        game.setPlayerCharacter(selectQuery.value("playerCharacter").toChar());
        game.setPlayerIsFirst(selectQuery.value("playerIsFirst").toChar() == 'T');
        game.setMoves(selectQuery.value("moves").toString());
        game.setState(selectQuery.value("state").toChar());

        games.push_back(game);
    }

    return games; // Return the vector of games
}

QVector<Session> DatabaseManager::loadHistory(const int &id) {
    QVector<Session> sessions;

    // Prepare SQL query to select sessions for a specific user
    QSqlQuery selectQuery;
    selectQuery.prepare("SELECT * FROM sessions WHERE userid = ?");
    selectQuery.addBindValue(id);

    // Execute the query
    if (!selectQuery.exec()) {
        // Print error message if query execution fails
        qDebug() << "Error executing select sessions query:"
                 << selectQuery.lastError().text();
        return sessions; // Return an empty vector to indicate failure
    }

    // Iterate over the results and create Session objects
    while (selectQuery.next()) {
        Session session;
        session.setId(selectQuery.value("id").toInt());
        session.setSpecificId(selectQuery.value("specificId").toInt());
        session.setType(selectQuery.value("type").toInt());
        session.setUserId(selectQuery.value("userid").toInt());
        session.setOpponentName(selectQuery.value("against").toString());
        session.setScore(selectQuery.value("wins").toInt(),
                         selectQuery.value("ties").toInt(),
                         selectQuery.value("losses").toInt());
        session.setTimestamp(selectQuery.value("timestamp").toDateTime());
        session.setGames(loadGames(session.getId()));

        sessions.push_back(session);
    }

    return sessions; // Return the vector of sessions
}
