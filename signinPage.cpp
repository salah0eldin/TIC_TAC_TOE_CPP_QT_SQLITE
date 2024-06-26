#include "mainwindow.h"
#include "ui_mainwindow.h"

// ----------------------------------------------------------------------------
// Button Click Handlers
// ----------------------------------------------------------------------------

/**
 * @brief Handles the back button click event from login to main window.
 */
void MainWindow::on_back_from_login_to_main_clicked()
{
    ui->stackedWidget->setCurrentIndex(MAIN_WINDOW);
}

/**
 * @brief Handles the signup button click event from login to signup window.
 */
void MainWindow::on_pushButton_signup_from_login_clicked()
{
    ui->stackedWidget->setCurrentIndex(SIGNUP_WINDOW);
}

/**
 * @brief Handles the login button click event.
 */
void MainWindow::on_pushButton_login_to_main_clicked() {
    // Retrieve username and password from input fields
    QString username = ui->lineEdit_user->text();
    QString password = ui->lineEdit_pass->text();

    // Check if username or password is empty
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Username or password can't be empty.");
        return; // Exit the function early
    }

    // Hash the password before sending it for authentication
    password = hashing(password);

    // Variables to store user data
    int id;
    QImage image;

    // Attempt to sign in using provided credentials
    int handl = db.signIn(username, password, id, image);

    // Handle different sign-in scenarios
    switch (handl) {
    case DATABASE_ERROR:
        // Display error message for database error
        QMessageBox::warning(this, "Error", "Error in database, try again later.");
        break;
    case WRONG_USERNAME:
    case WRONG_PASSWORD:
        // Display error message for wrong username or password
        QMessageBox::warning(this, "Error", "Wrong username or password.");
        // Clear input fields
        ui->lineEdit_user->setText("");
        ui->lineEdit_pass->setText("");
        break;
    case SIGNED_IN:
        // Display success message for successful sign-in
        QMessageBox::information(this, "Success", "You have successfully signed in!");
        // Clear input fields
        ui->lineEdit_user->setText("");
        ui->lineEdit_pass->setText("");

        // Create player object with retrieved data
        Player *tempPlayer = new Player(id, username, password, image);
        QVector<Session> s = db.loadHistory(id);
        tempPlayer->setSessions(s);
        int ssize = s.size();
        player = *tempPlayer;
        player.setSessionsCount(ssize);

        // Clear existing buttons if any
        QLayoutItem *item;
        QWidget *container = ui->scrollAreaWidgetContents_4;
        while ((item = container->layout()->takeAt(0)) != nullptr) {
            delete item->widget(); // Delete the widget
            delete item;           // Delete the layout item
        }
        sessionsButtons.clear();

        for (Session s : player.getSessions()) {
            populateSession(s);
        }

        // Update UI with user information
        ui->label_guest->setText(username);
        ui->label_19->setText(username);
        ui->label_40->setText(username);
        changePictures(image);

        // Save user credentials to local storage
        QSettings settings("MyApp", "MyApp");
        settings.setValue("id", id);
        settings.setValue("username", username);
        settings.setValue("password", password);

        // Convert image to Base64 and save to settings
        QByteArray imageData;
        QBuffer buffer(&imageData);
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, "PNG"); // Save as PNG format
        QString base64Image = QString::fromLatin1(imageData.toBase64().data());
        settings.setValue("ImageData", base64Image);

        // Update login status and navigate to main window
        loggedIN = true;
        ui->pushButton_login_from_main->setText("Log Out");
        ui->stackedWidget->setCurrentIndex(MAIN_WINDOW);
        break;
    }
}

/**
 * @brief Handles the show password checkbox state change event.
 */
void MainWindow::on_showPasswordCheckbox_stateChanged()
{
    if (ui->showPasswordCheckbox->isChecked()){
        ui->lineEdit_pass->setEchoMode(QLineEdit::Normal);
    } else {
        ui->lineEdit_pass->setEchoMode(QLineEdit::Password);
    }
}
