#include "mainwindow.h"
#include "ui_mainwindow.h"

// ----------------------------------------------------------------------------
// Button Click Handlers
// ----------------------------------------------------------------------------

/**
 * @brief Handles the back button from selecting player2 name to main window.
 */
void MainWindow::on_pushButton_back_from_player2_to_main_clicked()
{
    ui->stackedWidget->setCurrentIndex(MAIN_WINDOW);
}

/**
 * @brief Handles the confirm button click event for player2 input.
 *        Initializes a new session and game with player2.
 */
void MainWindow::on_pushButton_confirm_player2_clicked()
{
    Session s;
    QString oppoName = ui->lineEdit_player2->text();

    if (oppoName.isEmpty())
        oppoName = "Guest2";

    // Update UI with opponent and current player's names
    ui->label->setText(oppoName);
    ui->label_40->setText(player.getUsername());

    // Initialize session with opponent details
    s.setOpponentName(oppoName);
    s.setSpecificId(player.getSessionsCount());
    s.setUserId(player.getId());
    s.type = HUMAN;
    Ai = false;
    CurrentSession = s;

    // Initialize new game for current session
    Game g;
    g.setSpecifiedId(0);
    g.playerturn = true;
    CurrentGame = g;

    // Update UI elements
    ui->label_54->setText("0");
    ui->label_55->setText("0");
    ui->label_53->setText("0");

    // Navigate to board window
    ui->stackedWidget->setCurrentIndex(BOARD_WINDOW);
}

/**
 * @brief Handles the back button click event from board page to main window.
 *        Checks if there are unsaved changes and prompts the user to save.
 */
void MainWindow::on_pushButton_back_from_board_to_main_clicked()
{
    if (CurrentGame.getMoves() != "" || CurrentSession.getGamesCount() != 0) {
        QMessageBox msgBox;
        msgBox.setText("Do you want to save the session?");
        msgBox.setWindowTitle("Confirmation");

        // Add buttons with appropriate roles
        QPushButton *saveButton = msgBox.addButton(tr("Save"), QMessageBox::AcceptRole);
        QPushButton *discardButton = msgBox.addButton(tr("Discard"), QMessageBox::RejectRole);
        QPushButton *cancelButton = msgBox.addButton(tr("Cancel"), QMessageBox::RejectRole);

        // Set default button
        msgBox.setDefaultButton(cancelButton);

        // Disable save button if not logged in
        if (!loggedIN) {
            saveButton->setEnabled(false);
        }

        // Executing the message box to get user response
        msgBox.exec();

        // Check which button was clicked
        if (msgBox.clickedButton() == saveButton) {
            if (CurrentGame.getState() == 'n')
                CurrentSession.addGame(CurrentGame);

            // Clear board and reset game state
            for (int i = 0; i < 9; i++) {
                button[i]->setText("");
            }
            CurrentGame.resetGame();

            CurrentSession.setTimestamp(QDateTime::currentDateTime());

            // Check if session is new or existing and update accordingly
            bool isNew = CurrentSession.getId() == -1;

            // Save session to database
            db.saveSession(CurrentSession);

            // Update player's session list
            if (isNew) {
                populateSession(CurrentSession);
                player.addSession(CurrentSession);
            } else {
                player.updateSessionAt(CurrentSession.getSpecificId(), CurrentSession);
                updatePopulateSession(CurrentSession);
            }

            // Navigate back to main window
            ui->stackedWidget->setCurrentIndex(MAIN_WINDOW);
        } else if (msgBox.clickedButton() == discardButton) {
            // Clear board and reset game state
            for (int i = 0; i < 9; i++) {
                button[i]->setText("");
            }
            CurrentGame.resetGame();
            ui->stackedWidget->setCurrentIndex(MAIN_WINDOW);
        } else if (msgBox.clickedButton() == cancelButton) {
            // Do nothing, cancel operation
        }
    } else {
        // No unsaved changes, directly navigate back to main window
        ui->stackedWidget->setCurrentIndex(MAIN_WINDOW);
    }
}

// ----------------------------------------------------------------------------
// Board Button Click Handlers
// ----------------------------------------------------------------------------

/**
 * @brief Handles the click events for board buttons (0, 0) to (2, 2).
 *        Calls boardPlaceMarker() with corresponding indices.
 */
void MainWindow::on_b0_clicked() { boardPlaceMarker(0, 0); }
void MainWindow::on_b2_clicked() { boardPlaceMarker(0, 1); }
void MainWindow::on_b7_clicked() { boardPlaceMarker(0, 2); }
void MainWindow::on_b1_clicked() { boardPlaceMarker(1, 0); }
void MainWindow::on_b6_clicked() { boardPlaceMarker(1, 1); }
void MainWindow::on_b5_clicked() { boardPlaceMarker(1, 2); }
void MainWindow::on_b4_clicked() { boardPlaceMarker(2, 0); }
void MainWindow::on_b8_clicked() { boardPlaceMarker(2, 1); }
void MainWindow::on_b3_clicked() { boardPlaceMarker(2, 2); }

// ----------------------------------------------------------------------------
// Helper Functions
// ----------------------------------------------------------------------------

/**
 * @brief Places marker on the board at specified position.
 *        Checks game state and updates UI accordingly.
 * @param index1 Row index of the board button clicked.
 * @param index2 Column index of the board button clicked.
 */
void MainWindow::boardPlaceMarker(int index1, int index2) {
    int index = index1 * 3 + index2;

    // Check if the game is ongoing and the button is empty
    if (CurrentGame.getState() == 'n' && button[index]->text() == "") {
        QString symbol = (CurrentGame.playerturn ? "X" : "O");
        CurrentGame.makeMove(index1, index2);

        // Update button text with player's symbol
        button[index]->setText(symbol);

        // Check game state after move
        QChar state = CurrentGame.getState();
        if (state != 'n') {
            // Update session score and UI elements
            CurrentSession.addGame(CurrentGame);
            SessionScore score = CurrentSession.getScore();
            ui->label_55->setText(QString::number(score.wins));
            ui->label_54->setText(QString::number(score.losses));
            ui->label_53->setText(QString::number(score.ties));
        } else {
            // If AI mode enabled and it's AI's turn, make AI move
            if (Ai && !CurrentGame.playerturn) {
                QPair<int, int> p = best_move(CurrentGame.board, 'O', diff);
                boardPlaceMarker(p.first, p.second);
            }
        }
    }
}

/**
 * @brief Resets the board and checks if AI should make the first move.
 */
void MainWindow::resetBoard_checkAi() {
    // Clear board buttons and reset game state
    for (int i = 0; i < 9; i++) {
        button[i]->setText("");
    }
    CurrentGame.resetGame();

    // If AI mode enabled and AI should start first, make AI move
    if (Ai && CurrentGame.getPlayerIsFirst() == "F") {
        QPair<int, int> p = best_move(CurrentGame.board, 'O', diff);
        boardPlaceMarker(p.first, p.second);
    }
}

/**
 * @brief Handles the click event for a specific button to reset the board or save changes.
 *        Prompts user to save changes if game in progress.
 */
void MainWindow::on_pushButton_16_clicked()
{
    if (CurrentGame.getState() != 'n') {
        resetBoard_checkAi();
    } else if (CurrentGame.getMoves() != "") {
        QMessageBox msgBox;
        msgBox.setText("Do you want to save your changes?");
        msgBox.setWindowTitle("Confirmation");

        // Add buttons with appropriate roles
        QPushButton *saveButton = msgBox.addButton(tr("Save"), QMessageBox::AcceptRole);
        QPushButton *discardButton = msgBox.addButton(tr("Discard"), QMessageBox::RejectRole);
        QPushButton *cancelButton = msgBox.addButton(tr("Cancel"), QMessageBox::RejectRole);

        // Set default button
        msgBox.setDefaultButton(cancelButton);

        // Disable save button if not logged in
        if (!loggedIN) {
            saveButton->setEnabled(false);
        }

        // Executing the message box to get user response
        msgBox.exec();

        // Check which button was clicked
        if (msgBox.clickedButton() == saveButton) {
            // Save current game and reset board
            CurrentSession.addGame(CurrentGame);
            resetBoard_checkAi();
        } else if (msgBox.clickedButton() == discardButton) {
            // Reset board without saving changes
            resetBoard_checkAi();
            CurrentGame.setSpecifiedId(CurrentGame.getSpeceifiedId() - 1);
        } else if (msgBox.clickedButton() == cancelButton) {
            // Do nothing, cancel operation
        }
    }
}
