#include <QtTest/QtTest>
#include "../aiAlgorithm.h"

// Define the test class
class aitest : public QObject
{
    Q_OBJECT

public:
    aitest();
    ~aitest();

private slots:
    void testMinimaxAlgorithm();
    void testGenerateChildren();
    void testBestMove();
    void testIsWinner();
    void testIsDraw();
};

// Constructor
aitest::aitest() {}

// Destructor
aitest::~aitest() {}

// Test case for minimax algorithm
void aitest::testMinimaxAlgorithm()
{
    QChar board[3][3] = {
        {'X', ' ', 'O'},
        {'O', 'X', ' '},
        {' ', ' ', ' '}
    };

    auto result = minimax(new TreeNode(board), 0, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), true, HARD);
    QCOMPARE(result.second, QPair<int, int>(2, 1)); // Assuming expected move coordinates
}

// Test case for generating children nodes
void aitest::testGenerateChildren()
{
    QChar board[3][3] = {
        {'X', ' ', 'O'},
        {'O', 'X', ' '},
        {' ', ' ', ' '}
    };

    TreeNode* root = new TreeNode(board);
    generate_children(root, 'X');

    QCOMPARE(root->children.size(), 4); // Assuming expected number of children nodes

    delete root;
}

// Test case for determining the best move
void aitest::testBestMove()
{
    QChar board[3][3] = {
        {'X', ' ', 'O'},
        {'O', 'X', ' '},
        {' ', ' ', ' '}
    };

    auto result = best_move(board, 'X', HARD);
    QCOMPARE(result, QPair<int, int>(2, 1)); // Assuming expected move coordinates
}

// Test case for checking winner condition
void aitest::testIsWinner()
{
    QChar board[3][3] = {
        {'X', ' ', 'O'},
        {'O', 'X', ' '},
        {' ', ' ', ' '}
    };

    QVERIFY(is_winner(board, 'X'));
}

// Test case for checking draw condition
void aitest::testIsDraw()
{
    QChar board[3][3] = {
        {'X', 'O', 'X'},
        {'X', 'O', 'X'},
        {'O', 'X', 'O'}
    };

    QVERIFY(is_draw(board));
}

// Main function to run tests
QTEST_APPLESS_MAIN(aitest)
#include "tst_aitest.moc"
