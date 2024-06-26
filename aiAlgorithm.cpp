#include "aiAlgorithm.h"

// TreeNode constructor
TreeNode::TreeNode(QChar b[3][3], QPair<int, int> m, char p) : move(m), player(p) {
    // Initialize board state
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = b[i][j];
        }
    }
}

// TreeNode destructor
TreeNode::~TreeNode() {
    // Delete all child nodes
    qDeleteAll(children);
}

// Minimax algorithm with alpha-beta pruning
QPair<int, QPair<int, int>> minimax(TreeNode* node, int depth, int alpha, int beta, bool maximizingPlayer, int diff) {
    // Check terminal states
    if (is_winner(node->board, 'X')) return QPair<int, QPair<int, int>>(-diff + depth, node->move);
    if (is_winner(node->board, 'O')) return QPair<int, QPair<int, int>>(diff - depth, node->move);
    if (is_draw(node->board)) return QPair<int, QPair<int, int>>(0, node->move);

    // Maximize or minimize based on player turn
    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();
        QPair<int, int> bestMove;
        for (TreeNode* child : node->children) {
            auto eval = minimax(child, depth + 1, alpha, beta, false, diff);
            if (eval.first > maxEval) {
                maxEval = eval.first;
                bestMove = child->move;
            }
            alpha = std::max(alpha, eval.first);
            if (beta <= alpha) break;
        }
        return QPair<int, QPair<int, int>>(maxEval, bestMove);
    } else {
        int minEval = std::numeric_limits<int>::max();
        QPair<int, int> bestMove;
        for (TreeNode* child : node->children) {
            auto eval = minimax(child, depth + 1, alpha, beta, true, diff);
            if (eval.first < minEval) {
                minEval = eval.first;
                bestMove = child->move;
            }
            beta = std::min(beta, eval.first);
            if (beta <= alpha) break;
        }
        return QPair<int, QPair<int, int>>(minEval, bestMove);
    }
}

// Generate child nodes for the current board state
void generate_children(TreeNode* node, char player) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (node->board[i][j] == ' ') {
                // Create a new board configuration
                QChar newBoard[3][3];
                for (int x = 0; x < 3; ++x) {
                    for (int y = 0; y < 3; ++y) {
                        newBoard[x][y] = node->board[x][y];
                    }
                }
                newBoard[i][j] = player;

                // Create a child node and add to parent
                TreeNode* child = new TreeNode(newBoard, QPair<int, int>(i, j), player);
                node->children.push_back(child);

                // Recursively generate children nodes
                generate_children(child, (player == 'X') ? 'O' : 'X');
            }
        }
    }
}

// Determine the best move using minimax algorithm
QPair<int, int> best_move(QChar board[3][3], char player, int diff) {
    // Create root node
    TreeNode* root = new TreeNode(board);

    // Generate child nodes for possible moves
    generate_children(root, player);

    // Apply minimax algorithm with alpha-beta pruning
    auto result = minimax(root, 0, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), player == 'O', diff);

    // Clean up memory
    delete root;

    // Return best move coordinates
    return result.second;
}

// Check if there is a winner
bool is_winner(const QChar board[3][3], char player) {
    // Check rows and columns for three in a row
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }
    // Check diagonals for three in a row
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
    return false;
}

// Check if the game is a draw
bool is_draw(const QChar board[3][3]) {
    // Check if any cell is empty
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') return false;
        }
    }
    return true; // All cells are filled, game is a draw
}
