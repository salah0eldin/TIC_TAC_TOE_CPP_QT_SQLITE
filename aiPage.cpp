#include "mainwindow.h"
#include "ui_mainwindow.h"

// Slot for back button to return to main menu
void MainWindow::on_pushButton_14_clicked()
{
    ui->stackedWidget->setCurrentIndex(MAIN_WINDOW);
}

// Slot for selecting easy AI difficulty
void MainWindow::on_pushButton_12_clicked()
{
    diff = EASY;
    ai_to_board("AI_Easy");
}

// Slot for selecting medium AI difficulty
void MainWindow::on_pushButton_15_clicked()
{
    diff = MED;
    ai_to_board("AI_Med");
}

// Slot for selecting hard AI difficulty
void MainWindow::on_pushButton_13_clicked()
{
    diff = HARD;
    ai_to_board("AI_Hard");
}

// Function to initialize AI opponent and start game session
void MainWindow::ai_to_board(QString opponame) {
    // Create a new session
    Session s;

    // Update UI with opponent's name and player's username
    ui->label->setText(opponame);
    ui->label_40->setText(player.getUsername());

    // Set session details
    s.setOpponentName(opponame);
    s.setSpecificId(player.getSessionsCount());
    s.setUserId(player.getId());

    // Assign current session
    CurrentSession = s;

    // Set AI type based on selected difficulty
    switch (diff) {
    case EASY:
        CurrentSession.type = AI_EASY;
        break;
    case MED:
        CurrentSession.type = AI_MED;
        break;
    case HARD:
        CurrentSession.type = AI_HARD;
        break;
    }

    // Initialize a new game
    Game g;
    g.setSpecifiedId(0);
    g.playerturn = true;

    // Assign current game
    CurrentGame = g;

    // Reset UI labels
    ui->label_54->setText("0");
    ui->label_55->setText("0");
    ui->label_53->setText("0");

    // Change styles
    change_playing_styles();

    // Switch to game board view
    ui->stackedWidget->setCurrentIndex(BOARD_WINDOW);
}

