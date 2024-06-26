#include "mainwindow.h"
#include "ui_mainwindow.h"

// ----------------------------------------------------------------------------
// Checkbox State Change Handlers
// ----------------------------------------------------------------------------

/**
 * @brief Handles the state change of the show password checkbox for changing password.
 */
void MainWindow::on_checkBox_oldpass_stateChanged()
{
    if (ui->checkBox_oldpass->isChecked()){
        ui->lineEdit_old_pass->setEchoMode(QLineEdit::Normal);
    } else {
        ui->lineEdit_old_pass->setEchoMode(QLineEdit::Password);
    }
}

/**
 * @brief Handles the state change of the show password checkbox for new password.
 */
void MainWindow::on_checkBox_newpass_stateChanged()
{
    if (ui->checkBox_newpass->isChecked()){
        ui->lineEdit_new_pass->setEchoMode(QLineEdit::Normal);
    } else {
        ui->lineEdit_new_pass->setEchoMode(QLineEdit::Password);
    }
}

/**
 * @brief Handles the state change of the show password checkbox for confirming new password.
 */
void MainWindow::on_checkBox_confirm_newpass_stateChanged()
{
    if (ui->checkBox_confirm_newpass->isChecked()){
        ui->lineEdit_change_pass->setEchoMode(QLineEdit::Normal);
    } else {
        ui->lineEdit_change_pass->setEchoMode(QLineEdit::Password);
    }
}

// ----------------------------------------------------------------------------
// Button Click Handlers
// ----------------------------------------------------------------------------

/**
 * @brief Handles the back button click event from change password to profile window.
 */
void MainWindow::on_pushButton_not_change_pass_clicked()
{
    ui->stackedWidget->setCurrentIndex(PROFILE_WINDOW);
}

/**
 * @brief Handles the change password button click event.
 */
void MainWindow::on_pushButton_change_pass_clicked() {
    // Retrieve old password, new password, and confirm password from input fields
    QString oldPassword = ui->lineEdit_old_pass->text();
    QString newPassword = ui->lineEdit_new_pass->text();
    QString confirmPassword = ui->lineEdit_change_pass->text();

    // Check if any of the fields are empty
    if (oldPassword.isEmpty() || newPassword.isEmpty() || confirmPassword.isEmpty()) {
        QMessageBox::warning(this, "Error", "Username or password can't be empty.");
        return; // Exit the function early
    }

    // Check if the new password and confirm password match
    if (newPassword != confirmPassword) {
        QMessageBox::warning(this, "Error", "Passwords don't match");
        return;
    }

    // Hash the old and new passwords before sending for verification
    oldPassword = hashing(oldPassword);
    newPassword = hashing(newPassword);

    // Attempt to change password with provided credentials
    int handl = db.changePassword(player.getId(), oldPassword, newPassword);

    // Handle different change password scenarios
    switch (handl) {
    case DATABASE_ERROR:
        // Display error message for database error
        QMessageBox::warning(this, "Error", "Error in database, try again later.");
        break;
    case WRONG_PASSWORD:
        // Display error message for wrong password
        QMessageBox::warning(this, "Error", "Wrong Password.");
        // Clear old password field
        ui->lineEdit_old_pass->setText("");
        break;
    case DATABASE_SUCCESS:
        // Display success message for successful password change
        QMessageBox::information(this, "Success", "Password changed");
        // Clear input fields
        ui->lineEdit_old_pass->setText("");
        ui->lineEdit_new_pass->setText("");
        ui->lineEdit_change_pass->setText("");

        // Update player's hashed password
        player.setHashedPassword(newPassword);

        // Update password in local storage
        QSettings settings("MyApp", "MyApp");
        settings.setValue("password", newPassword);

        // Navigate to profile window
        ui->stackedWidget->setCurrentIndex(PROFILE_WINDOW);
        break;
    }
}
