#include <QObject>
#include <QtTest/QtTest>
#include "../game.h"
#include "../session.h"
#include "../player.h"
#include <QImage>

class CombinedTests : public QObject {
    Q_OBJECT

private slots:
    // Game class tests
    void testMakeMove();
    void testCheckWinDraw();
    void testResetGame();
    void testLoadGame();
    void testGettersAndSetters();

    // Player class tests (example)
    void testPlayerConstructor();
    void testPlayerSetName();
    void testPlayerGetName();
};

void CombinedTests::testMakeMove() {
    Game game;
    game.setPlayerCharacter('X'); // Set player character to X for testing

    // Test making moves
    game.makeMove(0, 0); // Player's turn
    QCOMPARE(game.board[0][0], 'X'); // Verify move is made

    game.makeMove(1, 1); // Opponent's turn
    QCOMPARE(game.board[1][1], 'O'); // Verify move is made
}

void CombinedTests::testCheckWinDraw() {
    Game game;

    // Test for a win scenario
    game.board[0][0] = 'X';
    game.board[0][1] = 'X';
    game.board[0][2] = 'X';
    QCOMPARE(game.checkWinDraw(), 'w'); // Verify player wins

    // Test for a draw scenario
    game.resetGame(); // Reset the game board
    game.board[0][0] = 'X';
    game.board[0][1] = 'O';
    game.board[0][2] = 'X';
    game.board[1][0] = 'O';
    game.board[1][1] = 'X';
    game.board[1][2] = 'O';
    game.board[2][0] = 'O';
    game.board[2][1] = 'X';
    game.board[2][2] = 'O';
    QCOMPARE(game.checkWinDraw(), 't'); // Verify it's a draw
}

void CombinedTests::testResetGame() {
    Game game;

    // Simulate a game state and reset
    game.makeMove(0, 0);
    game.resetGame();
    QCOMPARE(game.board[0][0], ' '); // Verify board is cleared
    QCOMPARE(game.getState(), 'n'); // Verify game state is reset
}

void CombinedTests::testLoadGame() {
    Game game;
    std::string gameMoves = "012345678"; // Example game moves data

    // Load a game state
    game.loadGame(1, gameMoves);
    QCOMPARE(game.getId(), 1); // Verify ID is set
    QCOMPARE(game.board[1][1], '4'); // Verify board state loaded correctly
}

void CombinedTests::testGettersAndSetters() {
    Game game;

    // Test setters and getters
    game.setSessionId(10);
    QCOMPARE(game.getSessionId(), 10); // Verify session ID set and retrieved

    game.setPlayerCharacter('X');
    QCOMPARE(game.getSpeceifiedId(), 0); // Verify specified ID default value

    game.setSpecifiedId(5);
    QCOMPARE(game.getSpeceifiedId(), 5); // Verify specified ID set and retrieved
}

// Example tests for Player class (similar structure)
void CombinedTests::testPlayerConstructor() {
    QString playerName = "Alice";
    Player player(1, playerName, "hashedpassword123", QImage("path/to/image.png")); // Assuming image path or QImage is correct
    QCOMPARE(player.getName(), QString("Alice")); // Verify player name set correctly
}

void CombinedTests::testPlayerSetName() {
    Player player(2, "Bob", "hashedpassword123", QImage("path/to/image.png")); // Assuming image path or QImage is correct
    player.setName("Charlie");
    QCOMPARE(player.getName(), QString("Charlie")); // Verify player name changed correctly
}

void CombinedTests::testPlayerGetName() {
    Player player(3, "David", "hashedpassword123", QImage("path/to/image.png")); // Assuming image path or QImage is correct
    QCOMPARE(player.getName(), QString("David")); // Verify initial player name
}

QTEST_APPLESS_MAIN(CombinedTests)

#include "tst_gametest.moc"
