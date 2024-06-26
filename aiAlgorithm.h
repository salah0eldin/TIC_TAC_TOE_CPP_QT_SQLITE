#ifndef AIALGORITHM_H
#define AIALGORITHM_H

#include <QChar>
#include <QPair>
#include <QVector>
#include <limits>
#include <algorithm> // for std::max and std::min

#define EASY    1
#define MED     3
#define HARD    10

class TreeNode {
public:
    QChar board[3][3];
    QPair<int, int> move;
    char player;
    QVector<TreeNode*> children;

    TreeNode(QChar b[3][3], QPair<int, int> m = QPair<int, int>(-1, -1), char p = ' ');
    ~TreeNode();
};

/**
 * @brief Minimax algorithm function to determine the best move for the AI.
 * @param node The current node in the game tree.
 * @param depth The current depth of the tree (recursion depth).
 * @param alpha The alpha value for alpha-beta pruning.
 * @param beta The beta value for alpha-beta pruning.
 * @param maximizingPlayer Flag indicating if it's the maximizing player's turn.
 * @param diff The difficulty level of the AI (EASY, MED, HARD).
 * @return A pair containing the evaluated score and the best move coordinates.
 */
QPair<int, QPair<int, int>> minimax(TreeNode* node, int depth, int alpha, int beta, bool maximizingPlayer, int diff);

/**
 * @brief Generates child nodes for the given node in the game tree.
 * @param node The current node in the game tree.
 * @param player The player ('X' or 'O') making the move.
 */
void generate_children(TreeNode* node, char player);

/**
 * @brief Finds the best move on the current board for the given player using the minimax algorithm.
 * @param board The current state of the game board.
 * @param player The player ('X' or 'O') making the move.
 * @param diff The difficulty level of the AI (EASY, MED, HARD).
 * @return The coordinates of the best move as a pair (row, column).
 */
QPair<int, int> best_move(QChar board[3][3], char player, int diff);

/**
 * @brief Checks if the given player has won on the board.
 * @param board The current state of the game board.
 * @param player The player ('X' or 'O') to check for a win.
 * @return True if the player has won, false otherwise.
 */
bool is_winner(const QChar board[3][3], char player);

/**
 * @brief Checks if the game is a draw (no more possible moves).
 * @param board The current state of the game board.
 * @return True if the game is a draw, false otherwise.
 */
bool is_draw(const QChar board[3][3]);

#endif // AIALGORITHM_H
