#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_pushButton_14_clicked()
{

    ui->stackedWidget->setCurrentIndex(MAIN_WINDOW);
}

void MainWindow::on_pushButton_12_clicked()
{
    //easy
    diff = 1;
    ai_to_board("AI_Easy");
}

void MainWindow::on_pushButton_15_clicked()
{
    //medium
    diff = 3;
    ai_to_board("AI_Med");
}

void MainWindow::on_pushButton_13_clicked()
{
    //hard
    diff = 10;
    ai_to_board("AI_Hard");
}

void MainWindow::ai_to_board(QString opponame){

    Session s;

    ui->label->setText(opponame);

    s.setOpponentName(opponame);
    s.setSpecificId(player.getSessionsCount());
    s.setUserId(player.getId());

    CurrentSession = s;

    Game g;
    g.setSpecifiedId(0);
    g.playerturn = true;

    CurrentGame = g;

    ui->label_54->setText("0");
    ui->label_55->setText("0");
    ui->label_53->setText("0");

    ui->stackedWidget->setCurrentIndex(BOARD_WINDOW);
}

// TreeNode class constructor and destructor
TreeNode::TreeNode(QChar b[3][3], QPair<int, int> m, char p) : move(m), player(p) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = b[i][j];
        }
    }
}

TreeNode::~TreeNode() {
    qDeleteAll(children);
}

// Minimax algorithm with alpha-beta pruning
QPair<int, QPair<int, int>> minimax(TreeNode* node, int depth, int alpha, int beta, bool maximizingPlayer,int diff) {
    if (is_winner(node->board, 'X')) return QPair<int, QPair<int, int>>(-diff + depth, node->move);
    if (is_winner(node->board, 'O')) return QPair<int, QPair<int, int>>(diff - depth, node->move);
    if (is_draw(node->board)) return QPair<int, QPair<int, int>>(0, node->move);

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

// Generate children nodes
void generate_children(TreeNode* node, char player) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (node->board[i][j] == ' ') {
                QChar newBoard[3][3];
                for (int x = 0; x < 3; ++x) {
                    for (int y = 0; y < 3; ++y) {
                        newBoard[x][y] = node->board[x][y];
                    }
                }
                newBoard[i][j] = player;
                TreeNode* child = new TreeNode(newBoard, QPair<int, int>(i, j), player);
                node->children.push_back(child);
                generate_children(child, (player == 'X') ? 'O' : 'X');
            }
        }
    }
}

// Determine the best move
QPair<int, int> best_move(QChar board[3][3], char player,int diff) {
    TreeNode* root = new TreeNode(board);
    generate_children(root, player);
    auto result = minimax(root, 0, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), player == 'O',diff);
    delete root;
    return result.second;
}

// Check for winner
bool is_winner(const QChar board[3][3], char player) {
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
    return false;
}

// Check for draw
bool is_draw(const QChar board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') return false;
        }
    }
    return true;
}
