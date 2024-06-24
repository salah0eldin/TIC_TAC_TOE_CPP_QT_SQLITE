#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_pushButton_back_from_signup_to_login_clicked()
{
    ui->stackedWidget->setCurrentIndex(LOGIN_WINDOW);
}

void MainWindow::on_pushButton_signup_to_main_clicked() {
    // Retrieve username, password, and confirm password from input fields
    QString username = ui->lineEdit_user_signup->text();
    QString password = ui->lineEdit_pass_signup->text();
    QString confirmPassword = ui->lineEdit_pass2_signup->text();

    // Check if username or password is empty
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Username or password can't be empty.");
        return; // Exit the function early
    } else {
        // Check if passwords match
        if (password != confirmPassword) {
            QMessageBox::warning(this, "Error", "Passwords don't match.");
            // Clear password fields
            ui->lineEdit_pass_signup->setText("");
            ui->lineEdit_pass2_signup->setText("");
            return;
        }

        // Hash the password before sending it for signup
        password = hashing(password);

        // Attempt to sign up with provided credentials
        int handl = db.signUp(username, password);

        // Handle different signup scenarios
        switch (handl) {
        case DATABASE_ERROR:
            // Display error message for database error
            QMessageBox::warning(this, "Error", "Error in database, try again later.");
            break;
        case USERNAME_TAKEN:
            // Display error message for username already taken
            QMessageBox::warning(this, "Error", "Username already taken.");
            // Clear input fields
            ui->lineEdit_user_signup->setText("");
            ui->lineEdit_pass_signup->setText("");
            ui->lineEdit_pass2_signup->setText("");
            break;
        case SIGNED_UP:
            // Display success message for successful signup
            QMessageBox::information(this, "Success", "You have successfully signed up! Please sign in.");
            // Clear input fields
            ui->lineEdit_user_signup->setText("");
            ui->lineEdit_pass_signup->setText("");
            ui->lineEdit_pass2_signup->setText("");
            // Navigate to login window
            ui->stackedWidget->setCurrentIndex(LOGIN_WINDOW);
            break;
        }
    }
}

void MainWindow::on_checkBox_pass_signup_stateChanged()
{
    if (ui->checkBox_pass_signup->isChecked()){
        ui->lineEdit_pass_signup->setEchoMode(QLineEdit::Normal);
    } else {
        ui->lineEdit_pass_signup->setEchoMode(QLineEdit::Password);
    }
}

void MainWindow::on_checkBox_confirm_pass_signup_stateChanged()
{
    if (ui->checkBox_confirm_pass_signup->isChecked()){
        ui->lineEdit_pass2_signup->setEchoMode(QLineEdit::Normal);
    } else {
        ui->lineEdit_pass2_signup->setEchoMode(QLineEdit::Password);
    }
}
