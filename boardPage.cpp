#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_pushButton_back_from_board_to_main_clicked()
{
    if(CurrentGame.getMoves() != "" || CurrentSession.getGamesCout() != 0){
        QMessageBox msgBox;
        msgBox.setText("Do you want to save the sessoin?");
        msgBox.setWindowTitle("Confirmation");

        // Add buttons with appropriate roles
        QPushButton *saveButton = msgBox.addButton(tr("Save"), QMessageBox::AcceptRole);
        QPushButton *discardButton = msgBox.addButton(tr("Discard"), QMessageBox::RejectRole);
        QPushButton *cancelButton = msgBox.addButton(tr("Cancel"), QMessageBox::RejectRole);

        // Set default button
        msgBox.setDefaultButton(cancelButton);

        if (!loggedIN) {
            saveButton->setEnabled(false);
        }
        // Executing the message box to get user response
        msgBox.exec();

        // Check which button was clicked
        if (msgBox.clickedButton() == saveButton) {
            if(CurrentGame.getState() == 'n')
                CurrentSession.addGame(CurrentGame);
            for(int i=0;i<9;i++){
                button[i]->setText("");
            }
            CurrentGame.resetGame();
            db.saveSession(CurrentSession);
            qDebug()<<"save"<<CurrentSession.getId();
            CurrentSession.setTimestamp(QDateTime::currentDateTime());
            player.addSession(CurrentSession);
            populateSession(CurrentSession);
            ui->stackedWidget->setCurrentIndex(MAIN_WINDOW);
        } else if (msgBox.clickedButton() == discardButton) {
            for(int i=0;i<9;i++){
                button[i]->setText("");
            }
            CurrentGame.resetGame();
            ui->stackedWidget->setCurrentIndex(MAIN_WINDOW);
        } else if (msgBox.clickedButton() == cancelButton) {

        }
    } else{
        ui->stackedWidget->setCurrentIndex(MAIN_WINDOW);
    }
}

void MainWindow::on_pushButton_back_from_player2_to_main_clicked()
{
    ui->stackedWidget->setCurrentIndex(MAIN_WINDOW);
}

void MainWindow::on_pushButton_confirm_player2_clicked()
{
    Session s;
    QString oppoName = ui->lineEdit_player2->text();

    if(oppoName=="")
        oppoName = "Guest2";

    ui->label->setText(oppoName);

    s.setOpponentName(oppoName);
    s.setSpecificId(player.getSessionsCount());
    s.setUserId(player.getId());
    s.setType(HUMAN);

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

void MainWindow::boardPlaceMarker(int index1,int index2){
    int index = index1 * 3 + index2;
    if(CurrentGame.getState() == 'n' && button[index]->text() == ""){
        QString symbol = (CurrentGame.playerturn?"X":"O");
        CurrentGame.makeMove(index1,index2);

        button[index]->setText(symbol);
        QChar state = CurrentGame.getState();
        if(state != 'n'){
            CurrentSession.addGame(CurrentGame);
            SessionScore score = CurrentSession.getScore();
            QString s;
            s = QString::number(score.wins);
            ui->label_55->setText(s);
            s = QString::number(score.losses);
            ui->label_54->setText(s);
            s = QString::number(score.ties);
            ui->label_53->setText(s);
        } else {

            if(Ai && !CurrentGame.playerturn)
            {
                QPair<int,int> p = best_move(CurrentGame.board,'O',diff);
                boardPlaceMarker(p.first,p.second);
            }
        }
    }
}


void MainWindow::resetBoard_checkAi(){
    for(int i=0;i<9;i++){
        button[i]->setText("");
    }
    CurrentGame.resetGame();

    if(Ai && CurrentGame.getPlayerIsFirst() == "F"){
        QPair<int,int> p = best_move(CurrentGame.board,'O',diff);
        boardPlaceMarker(p.first,p.second);
    }
}

void MainWindow::on_pushButton_16_clicked()
{
    if(CurrentGame.getState() != 'n'){
        resetBoard_checkAi();
    }else if(CurrentGame.getMoves()==""){

    }else{
        QMessageBox msgBox;
        msgBox.setText("Do you want to save your changes?");
        msgBox.setWindowTitle("Confirmation");

        // Add buttons with appropriate roles
        QPushButton *saveButton = msgBox.addButton(tr("Save"), QMessageBox::AcceptRole);
        QPushButton *discardButton = msgBox.addButton(tr("Discard"), QMessageBox::RejectRole);
        QPushButton *cancelButton = msgBox.addButton(tr("Cancel"), QMessageBox::RejectRole);

        // Set default button
        msgBox.setDefaultButton(cancelButton);

        if (!loggedIN) {
            saveButton->setEnabled(false);
        }

        // Executing the message box to get user response
        msgBox.exec();

        // Check which button was clicked
        if (msgBox.clickedButton() == saveButton) {
            CurrentSession.addGame(CurrentGame);
            resetBoard_checkAi();
        } else if (msgBox.clickedButton() == discardButton) {
            resetBoard_checkAi();
            CurrentGame.setSpecifiedId(CurrentGame.getSpeceifiedId()-1);
        } else if (msgBox.clickedButton() == cancelButton) {

        }
    }
}

void MainWindow::on_b0_clicked()
{
    boardPlaceMarker(0,0);
}

void MainWindow::on_b2_clicked()
{
    boardPlaceMarker(0,1);
}

void MainWindow::on_b7_clicked()
{
    boardPlaceMarker(0,2);
}

void MainWindow::on_b1_clicked()
{
    boardPlaceMarker(1,0);
}

void MainWindow::on_b6_clicked()
{
    boardPlaceMarker(1,1);
}

void MainWindow::on_b5_clicked()
{
    boardPlaceMarker(1,2);
}

void MainWindow::on_b4_clicked()
{
    boardPlaceMarker(2,0);
}

void MainWindow::on_b8_clicked()
{
    boardPlaceMarker(2,1);
}

void MainWindow::on_b3_clicked()
{
    boardPlaceMarker(2,2);
}
