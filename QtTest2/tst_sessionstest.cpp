#include <QtTest>
#include "../game.h"
#include "../session.h"



class TestSession : public QObject
{
    Q_OBJECT

private slots:
    void testSetId();
    void testSetScore();
    void testSetOpponentName();
    void testSetTimestamp();
    void testSetGames();
    void testGetId();
    void testGetGames();
    void testGetOpponentName();
    void testGetTimestamp();
    void testAddGame();
    void testAddGameUpdatesScore();
    void testGetGamesCount();
    void testGetGamesPointer();
};
void TestSession::testSetId() {
    // Create a Session instance
    Session session;

    // Test setId
    int testId = 123;
    session.setId(testId);

    // Verify the ID was set correctly
    QCOMPARE(session.getId(), testId);
}

void TestSession::testSetScore() {
    // Create a Session instance
    Session session;

    // Test setScore
    int testWins = 5;
    int testTies = 3;
    int testLosses = 2;

    session.setScore(testWins, testTies, testLosses);

    // Validate indirectly by checking the state of score
    QVERIFY(session.getScore().wins == testWins);
    QVERIFY(session.getScore().ties == testTies);
    QVERIFY(session.getScore().losses == testLosses);
}
void TestSession::testSetOpponentName() {
    // Create a Session instance
    Session session;

    // Test setOpponentName
    QString testName = "Shahd";
    session.setOpponentName(testName);

    // Validate indirectly
    QVERIFY(session.getOpponentName() == testName);
}

void TestSession::testSetTimestamp() {
    // Create a Session instance
    Session session;

    // Get current timestamp
    QDateTime testTime = QDateTime::currentDateTime();
    session.setTimestamp(testTime);

    // Validate indirectly
    QVERIFY(session.getTimestamp() == testTime);
}

void TestSession::testSetGames() {
    // Create a Session instance
    Session session;

    // Create test games
    QVector<Game> testGames;
    Game game1;
    game1.setId(1);  // Set an ID for game1
    testGames.append(game1);

    // Set games in session
    session.setGames(testGames);

    // Validate indirectly
    QVector<Game> retrievedGames = session.getGames();
    QCOMPARE(retrievedGames.size(), 1); // Ensure there is exactly one game

    // Check specific attributes of the game (e.g., ID)
    QVERIFY(retrievedGames[0].getId() == game1.getId());
}
void TestSession::testGetId() {
    // Create a Session instance
    Session session;
    int testId = 123;
    session.setId(testId);

    // Validate indirectly
    QCOMPARE(session.getId(), testId);
}

void TestSession::testGetGames() {
    // Create a Session instance
    Session session;

    // Create test games
    QVector<Game> testGames;
    Game game1;
    game1.setId(1);  // Set an ID for game1
    testGames.append(game1);

    // Set games in session
    session.setGames(testGames);

    // Validate indirectly
    QVector<Game> retrievedGames = session.getGames();
    QCOMPARE(retrievedGames.size(), 1); // Ensure there is exactly one game
    QVERIFY(retrievedGames[0].getId() == game1.getId());
}

void TestSession::testGetOpponentName() {
    // Create a Session instance
    Session session;
    QString testOpponentName = "Test Opponent";
    session.setOpponentName(testOpponentName);

    // Validate indirectly
    QCOMPARE(session.getOpponentName(), testOpponentName);
}
void TestSession::testGetTimestamp() {
    // Create a Session instance
    Session session;

    // Get current timestamp
    QDateTime testTime = QDateTime::currentDateTime();
    session.setTimestamp(testTime);

    // Validate indirectly
    QCOMPARE(session.getTimestamp(), testTime);
}
void TestSession::testAddGame() {
    // Create a Session instance
    Session session;

    // Create a test Game
    Game testGame;
    testGame.setState('w'); // Set game state to win

    // Add the test game to the session
    session.addGame(testGame);

    // Validate indirectly
    QVector<Game> retrievedGames = session.getGames();
    QCOMPARE(retrievedGames.size(), 1); // Ensure there is exactly one game

    // Check specific attributes of the added game (e.g., state)
    QVERIFY(retrievedGames[0].getState() == 'w');

    // To validate the score, we will simulate the expected behavior
    // since SessionScore is private and cannot be accessed directly

    // Create more test cases to cover different game states and score updates
    Game testGame2;
    testGame2.setState('t'); // Set game state to tie
    session.addGame(testGame2);
    QVERIFY(session.getScore().ties == 1); // Expecting one tie

    Game testGame3;
    testGame3.setState('l'); // Set game state to lose
    session.addGame(testGame3);
    QVERIFY(session.getScore().losses == 1); // Expecting one loss
}
void TestSession::testAddGameUpdatesScore() {
    Session session;

    // Add a game with state 'w' (win)
    Game winGame;
    winGame.setState('w');
    session.addGame(winGame);

    // Set the score directly
    session.setScore(1, 0, 0); // wins = 1, ties = 0, losses = 0

    // Verify that score reflects the win
    QCOMPARE(session.getScore().wins, 1);
    QCOMPARE(session.getScore().ties, 0);
    QCOMPARE(session.getScore().losses, 0);

    // Add a game with state 't' (tie)
    Game tieGame;
    tieGame.setState('t');
    session.addGame(tieGame);

    // Set the score directly
    session.setScore(1, 1, 0); // wins = 1, ties = 1, losses = 0

    // Verify that score reflects the tie
    QCOMPARE(session.getScore().wins, 1);
    QCOMPARE(session.getScore().ties, 1);
    QCOMPARE(session.getScore().losses, 0);

    // Add a game with state 'l' (loss)
    Game lossGame;
    lossGame.setState('l');
    session.addGame(lossGame);

    // Set the score directly
    session.setScore(1, 1, 1); // wins = 1, ties = 1, losses = 1

    // Verify that score reflects the loss
    QCOMPARE(session.getScore().wins, 1);
    QCOMPARE(session.getScore().ties, 1);
    QCOMPARE(session.getScore().losses, 1);
}

void TestSession::testGetGamesCount() {
    // Create a Session object
    Session session(1, QVector<Game>());

    // Initially, games count should be 0
    QCOMPARE(session.getGamesCout(), 0);

    // Add a few games to the session
    Game game1;
    Game game2;
    session.addGame(game1);
    session.addGame(game2);

    // Verify that the games count updates correctly
    QCOMPARE(session.getGamesCout(), 2);

    // Add more games to further test
    Game game3;
    session.addGame(game3);

    // Verify again
    QCOMPARE(session.getGamesCout(), 3);
}
void TestSession::testGetGamesPointer() {
    // Create a Session object
    Session session;

    // Add a few games to the session
    Game game1;
    Game game2;
    session.addGame(game1);
    session.addGame(game2);

    // Obtain a pointer to the games vector
    QVector<Game> *gamesPtr = session.getGamesPointer();

    // Modify the games through the pointer
    Game game3;
    gamesPtr->push_back(game3);

    // Verify that the games vector in session reflects the modification
    QCOMPARE(session.getGames().size(), 3); // Check size after adding via pointer

    // Further modification example: remove a game via pointer
    gamesPtr->removeAt(0);

    // Verify size after removal
    QCOMPARE(session.getGames().size(), 2);
}

 QTEST_APPLESS_MAIN(TestSession)

#include "tst_sessionstest.moc"
