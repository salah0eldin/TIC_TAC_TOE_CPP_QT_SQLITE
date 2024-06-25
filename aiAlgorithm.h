#ifndef AIALGORITHM_H
#define AIALGORITHM_H

#include <QChar>
#include <QPair>
#include <QVector>
#include <limits>
#include <algorithm> // for std::max and std::min

class TreeNode {
public:
    QChar board[3][3];
    QPair<int, int> move;
    char player;
    QVector<TreeNode*> children;

    TreeNode(QChar b[3][3], QPair<int, int> m = QPair<int, int>(-1, -1), char p = ' ');
    ~TreeNode();
};

// Function declarations
QPair<int, QPair<int, int>> minimax(TreeNode* node, int depth, int alpha, int beta, bool maximizingPlayer, int diff);
void generate_children(TreeNode* node, char player);
QPair<int, int> best_move(QChar board[3][3], char player,int diff);
bool is_winner(const QChar board[3][3], char player);
bool is_draw(const QChar board[3][3]);

#endif // AIALGORITHM_H
