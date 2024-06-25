#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_checkBox_changeuser_stateChanged()
{
    if (ui->checkBox_changeuser->isChecked()){
        ui->lineEdit_pass_to_change_user->setEchoMode(QLineEdit::Normal);
    } else {
        ui->lineEdit_pass_to_change_user->setEchoMode(QLineEdit::Password);
    }
}

void MainWindow::on_checkBox_changeuser_stateChanged(int state) {
    // Implementation code here
}

void MainWindow::on_pushButton_not_change_username_clicked()
{
    ui->stackedWidget->setCurrentIndex(PROFILE_WINDOW);
}


void MainWindow::on_pushButton_change_username_clicked() {
    // Retrieve new username and password from input fields
    QString newUsername = ui->lineEdit_change_username->text();
    QString password = ui->lineEdit_pass_to_change_user->text();

    // Check if username or password is empty
    if (newUsername.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Username or password can't be empty.");
        return; // Exit the function early
    }

    // Hash the password before sending for verification
    password = hashing(password);

    // Attempt to change username with provided credentials
    int handl = db.changeUsername(player.getId(), newUsername, password);

    // Handle different change username scenarios
    switch(handl){
    case DATABASE_ERROR:
        // Display error message for database error
        QMessageBox::warning(this, "Error", "Error in database, try again later.");
        break;
    case WRONG_PASSWORD:
        // Display error message for wrong password
        QMessageBox::warning(this, "Error", "Wrong Password.");
        // Clear password field
        ui->lineEdit_pass_to_change_user->setText("");
        break;
    case USERNAME_TAKEN:
        // Display error message for username already taken
        QMessageBox::warning(this, "Error", "Username already taken.");
        // Clear input fields
        ui->lineEdit_change_username->setText("");
        ui->lineEdit_pass_to_change_user->setText("");
        break;
    case DATABASE_SUCCESS:
        // Display success message for successful username change
        QMessageBox::information(this, "Success", "Username changed");
        // Clear input fields
        ui->lineEdit_change_username->setText("");
        ui->lineEdit_pass_to_change_user->setText("");

        // Update UI with new username
        ui->label_guest->setText(newUsername);
        ui->label_19->setText(newUsername);

        // Update player's username
        player.setUsername(newUsername);

        // Update username in local storage
        QSettings settings("MyApp", "MyApp");
        settings.setValue("username", newUsername);

        // Navigate to profile window
        ui->stackedWidget->setCurrentIndex(PROFILE_WINDOW);
        break;
    }
}
