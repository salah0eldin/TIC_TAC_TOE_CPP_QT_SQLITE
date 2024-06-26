#include <QtTest/QtTest>
#include "../player.h"
#include "../session.h"
#include "../game.h"
 QImage testImage(100, 100, QImage::Format_RGB32);

class TestPlayer : public QObject {
    Q_OBJECT

private slots:
    void testGetUsername();
    void testGetHashedPassword();
    void testGetId();
    void testGetImage();
    void testAddSession();
    void testRemoveSessionAt();
    void testGetSessions();
    void testSetSessions();
    void testSetId();
    void testSetImage();
    void testSetUsername();
    void testSetHashedPassword();
};

void TestPlayer::testGetUsername() {
    Player player;
    QString testUsername = "test_user";
    player.setUsername(testUsername);

    QCOMPARE(player.getUsername(), testUsername);
}
void TestPlayer::testGetHashedPassword() {
    Player player;
    QString testHashedPassword = "hashed_pass";
    player.setHashedPassword(testHashedPassword);
    QCOMPARE(player.getHashedPassword(), testHashedPassword);
}
void TestPlayer::testGetId() {
    Player player(1, "test_user", "hashed_pass", QImage());
    QCOMPARE(player.getId(), 1);
}
void TestPlayer::testGetImage() {

    // Create a Player instance with the test image
    Player player(1, "test_user", "hashed_pass", testImage);

    // Check if the retrieved image is equal to the test image
    QCOMPARE(player.getImage(), testImage);
}
void TestPlayer::testAddSession() {
    // Create a Player object
    Player player(1, "JohnDoe", "hashedpassword", QImage());

    // Create some Session objects
    QVector<Game> games;
    Session session1(1, games);
    Session session2(2, games);

    // Add sessions to the player
    player.addSession(session1);
    player.addSession(session2);

    // Verify the number of sessions added
    QCOMPARE(player.getSessionsCount(), 2);

    // Optionally, you can verify session details or perform additional checks
    // For example:
    QVector<Session> sessions = player.getSessions();
    QCOMPARE(sessions.size(), 2);
    QCOMPARE(sessions[0].getId(), 1);
    QCOMPARE(sessions[1].getId(), 2);
}
void TestPlayer::testRemoveSessionAt() {
    // Create a Player instance
    QImage testImage(100, 100, QImage::Format_RGB32);
    Player player(1, "test_user", "hashed_pass", testImage);

    // Create and add multiple Session instances
    QVector<Game> games;
    Session session1(1, games);
    Session session2(2, games);
    Session session3(3, games);
    player.addSession(session1);
    player.addSession(session2);
    player.addSession(session3);

    // Remove the session at index 1 (session2)
    player.removeSessionAt(1);

    // Check if the session was removed
    QVector<Session> sessions = player.getSessions();
    QCOMPARE(sessions.size(), 2); // Verify the vector contains two sessions
    QCOMPARE(sessions[0].getId(), session1.getId()); // Verify the first session is still session1
    QCOMPARE(sessions[1].getId(), session3.getId()); // Verify the second session is now session3
}
void TestPlayer::testGetSessions() {
    // Create a Player instance
    QImage testImage(100, 100, QImage::Format_RGB32);
    Player player(1, "test_user", "hashed_pass", testImage);

    // Create and add multiple Session instances
    QVector<Game> games;
    Session session1(1, games);
    Session session2(2, games);
    Session session3(3, games);
    player.addSession(session1);
    player.addSession(session2);
    player.addSession(session3);

    // Retrieve sessions from the player
    QVector<Session> sessions = player.getSessions();

    // Check if the sessions vector contains the correct sessions
    QCOMPARE(sessions.size(), 3); // Verify the vector contains three sessions
    QCOMPARE(sessions[0].getId(), session1.getId()); // Verify the first session's ID
    QCOMPARE(sessions[1].getId(), session2.getId()); // Verify the second session's ID
    QCOMPARE(sessions[2].getId(), session3.getId()); // Verify the third session's ID
}
void TestPlayer::testSetSessions() {
    // Create a Player instance
    QImage testImage(100, 100, QImage::Format_RGB32);
    Player player(1, "test_user", "hashed_pass", testImage);

    // Create sessions for testing
    Session session1(1, QVector<Game>());
    Session session2(2, QVector<Game>());
    QVector<Session> newSessions = {session1, session2};

    // Set the new sessions
    player.setSessions(newSessions);

    // Verify the sessions were updated
    QVector<Session> retrievedSessions = player.getSessions();
    QCOMPARE(retrievedSessions.size(), newSessions.size());
    QCOMPARE(retrievedSessions[0].getId(), newSessions[0].getId());
    QCOMPARE(retrievedSessions[1].getId(), newSessions[1].getId());
}
void TestPlayer::testSetId() {
    // Create a Player instance
    QImage testImage(100, 100, QImage::Format_RGB32);
    Player player(1, "test_user", "hashed_pass", testImage);

    // Set a new ID
    int newId = 42;
    player.setId(newId);

    // Verify the ID was updated
    QCOMPARE(player.getId(), newId);
}

void TestPlayer::testSetImage() {
    // Create a Player instance
    QImage testImage(100, 100, QImage::Format_RGB32);
    Player player(1, "test_user", "hashed_pass", testImage);

    // Set a new image
    QImage newImage(200, 200, QImage::Format_RGB32);
    player.setImage(newImage);

    // Verify the image was updated
    QCOMPARE(player.getImage(), newImage);
}

void TestPlayer::testSetUsername() {
    // Create a Player instance
    QImage testImage(100, 100, QImage::Format_RGB32);
    Player player(1, "initial_user", "hashed_pass", testImage);

    // Set a new username
    QString newUsername = "new_user";
    player.setUsername(newUsername);

    // Verify the username was updated
    QCOMPARE(player.getUsername(), newUsername);
}

void TestPlayer::testSetHashedPassword() {
    // Create a Player instance
    QImage testImage(100, 100, QImage::Format_RGB32);
    Player player(1, "test_user", "initial_pass", testImage);

    // Set a new hashed password
    QString newHashedPassword = "new_hashed_pass";
    player.setHashedPassword(newHashedPassword);

    // Verify the hashed password was updated
    QCOMPARE(player.getHashedPassword(), newHashedPassword);
}
QTEST_APPLESS_MAIN(TestPlayer)
#include "tst_testcase.moc"
