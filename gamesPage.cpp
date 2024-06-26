#include "mainwindow.h"
#include "ui_mainwindow.h"

int currentStep = 0;
int movesLength = 0;
QString moves = "";
bool playerTurn = false;

/**
 * @brief Loads a game session based on the provided game ID.
 * @param gameId The ID of the game to load.
 */
void MainWindow::loadGame(int gameId) {
    CurrentGame = CurrentSession.getGames()[gameId];
    moves = CurrentGame.getMoves();
    movesLength = moves.length();
    playerTurn = (CurrentGame.getPlayerIsFirst() == "T");

    for (int i = 0; i < 9; i++) {
        labelBoard[i]->setText("");
    }

    currentStep = 0;
}

/**
 * @brief Handles the action when the "Next Move" button is clicked.
 *        Advances to the next move in the game and updates the UI accordingly.
 */
void MainWindow::on_pushButton_31_clicked() {
    if (currentStep < movesLength) {
        QString symbol = (playerTurn ? "X" : "O");
        int index = moves[currentStep++].digitValue();
        labelBoard[index]->setText(symbol);
        playerTurn = !playerTurn;
    }
}

/**
 * @brief Handles the action when the "Previous Move" button is clicked.
 *        Reverts to the previous move in the game and updates the UI accordingly.
 */
void MainWindow::on_pushButton_30_clicked() {
    if (currentStep > 0) {
        int index = moves[--currentStep].digitValue();
        labelBoard[index]->setText("");
        playerTurn = !playerTurn;
    }
}

/**
 * @brief Handles the action when the "Replay" button is clicked.
 *        Prepares the UI for a new game replay session.
 */
void MainWindow::on_pushButton_replay_clicked() {
    ui->label->setText(CurrentSession.getOpponentName());

    Game g;
    g.setSpecifiedId(CurrentGame.getSpeceifiedId() + 1);
    g.setPlayerIsFirst(true); // Set player's turn to start
    CurrentGame = g;

    SessionScore score = CurrentSession.getScore();

    ui->label_55->setText(QString::number(score.wins));
    ui->label_53->setText(QString::number(score.ties));
    ui->label_54->setText(QString::number(score.losses));

    switch (CurrentSession.type) {
    case HUMAN:
        Ai = false;
        break;
    default:
        Ai = true;
        switch (CurrentSession.type) {
        case AI_EASY:
            diff = EASY;
            break;
        case AI_MED:
            diff = MED;
            break;
        case AI_HARD:
            diff = HARD;
            break;
        }
        break;
    }

    ui->stackedWidget->setCurrentIndex(BOARD_WINDOW);
}

/**
 * @brief Handles the action when the "Back" button is clicked from history view to session view.
 */
void MainWindow::on_pushButton_back_from_history_to_session_clicked() {
    ui->stackedWidget->setCurrentIndex(SESSIONS_WINDOW);
}
