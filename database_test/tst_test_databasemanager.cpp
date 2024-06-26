#include <QtTest/QtTest>
#include "../databasemanager.h"
#include <QImage>
#include <QBuffer>
#include <QtTest/QtTest>
#include "../databasemanager.h"
#include <QImage>
#include <QBuffer>

class TestDatabaseManager : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void testSignUp();
    void testSignIn();
    void testChangeUsername();
    void testChangePassword();
    void testChangeImage();
    void testSaveSession();
    void testSaveGame();
    void testLoadGames();
    void testLoadHistory();
    void cleanupTestCase();

private:
    DatabaseManager dbManager;
};

void TestDatabaseManager::initTestCase() {
    // Ensure database is reset for testing
    QSqlQuery resetQuery;
    resetQuery.exec("DELETE FROM users");
    qDebug() << "Database reset for testing";
}

void TestDatabaseManager::testSignUp() {
    QString username = "testUser";
    QString password = "testPassword";

    int result = dbManager.signUp(username, password);
    QCOMPARE(result, SIGNED_UP);

    result = dbManager.signUp(username, password);
    QCOMPARE(result, USERNAME_TAKEN);
}

void TestDatabaseManager::testSignIn() {
    QString username = "testUser";
    QString password = "testPassword";
    int id=1;
    QImage image;

    int result = dbManager.signIn(username, password, id, image);
    QCOMPARE(result, SIGNED_IN);

    result = dbManager.signIn("wrongUser", password, id, image);
    QCOMPARE(result, WRONG_USERNAME);

    result = dbManager.signIn(username, "wrongPassword", id, image);
    QCOMPARE(result, WRONG_PASSWORD);
}

void TestDatabaseManager::testChangeUsername() {
    QString username = "testUser";
    QString newPassword = "newPassword";
    int id=1;
    QImage image;
    dbManager.signIn(username, "testPassword", id, image);

    int result = dbManager.changeUsername(id, "newUser", "testPassword");
    QCOMPARE(result, DATABASE_SUCCESS);

    dbManager.signUp("existingUser", "password");
    result = dbManager.changeUsername(id, "existingUser", "testPassword");
    QCOMPARE(result, USERNAME_TAKEN);
}

void TestDatabaseManager::testChangePassword() {
    QString username = "newUser";
    QString oldPassword = "testPassword";
    QString newPassword = "newPassword";
    int id=1;
    QImage image;
    dbManager.signIn(username, oldPassword, id, image);

    int result = dbManager.changePassword(id, oldPassword, newPassword);
    QCOMPARE(result, DATABASE_SUCCESS);

    result = dbManager.changePassword(id, "wrongPassword", "anotherPassword");
    QCOMPARE(result, WRONG_PASSWORD);
}

void TestDatabaseManager::testChangeImage() {
    QString username = "newUser";
    QString password = "newPassword";
    int id;
    QImage image(100, 100, QImage::Format_RGB32);
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    QByteArray imageData = buffer.data();

    int result = dbManager.signIn(username, password, id, image);
    QCOMPARE(result, SIGNED_IN);

    result = dbManager.changeImage(id, imageData);
    QCOMPARE(result, DATABASE_SUCCESS);
}

void TestDatabaseManager::testSaveSession() {
    QString username = "newUser";
    QString password = "newPassword";
    int id=1;
    QImage image;

    dbManager.signIn(username, password, id, image);

    Session session;
    session.setSpecificId(12345);
    session.setUserId(id);
    session.type = 1; // Assigning to 'type' directly if it's a member variable
    session.setOpponentName("opponent");
    session.setScore(1, 0, 0); // Wins, losses, ties
    session.setTimestamp(QDateTime::currentDateTime());

    bool result = dbManager.saveSession(session);
    QVERIFY(result); // Assuming saveSession returns true on success
}



void TestDatabaseManager::testSaveGame() {
    Game game;
    game.setSessionId(1); // Assuming session id exists
    game.setSpecifiedId(1); // Assuming specified id exists
    game.setPlayerCharacter('X');
    game.setPlayerIsFirst('Y');
    game.setMoves("XOXOXOXOX");
    game.setState(QChar('w')); // Use QChar constructor to set the state

    bool result = dbManager.saveGame(game);
    QVERIFY(result); // Assuming saveGame returns true on success
}


void TestDatabaseManager::testLoadGames() {
    int sessionId = 1;

    QVector<Game> games = dbManager.loadGames(sessionId);
    QVERIFY(!games.isEmpty());
}

void TestDatabaseManager::testLoadHistory() {
    QString username = "newUser";
    QString password = "newPassword";
    int id =1 ;
    QImage image ;

    dbManager.signIn(username, password, id, image);

    QVector<Session> sessions = dbManager.loadHistory(id);
    QVERIFY(!sessions.isEmpty());
}

void TestDatabaseManager::cleanupTestCase() {
    // Clean up if needed
}

QTEST_MAIN(TestDatabaseManager)
#include "tst_test_databasemanager.moc"
