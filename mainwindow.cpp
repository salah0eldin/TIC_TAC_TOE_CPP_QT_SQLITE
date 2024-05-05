#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Center the text in the label of board at history
    centerLabels();

    // Add default text "Guest" to the line edit of player2
    ui->lineEdit_player2->setText("Guest");

    // Make picture label clickable
    makeLabelClickable(ui->label_picture);
    makeLabelClickable(ui->label_guest);

    // Set initial pictures
    setInitialPictures();

    // Add placeholder text to line edits
    addPlaceholderText();

    // Add pictures to icons
    addPicturesToIcons();

    // Enable clear buttons for line edits
    enableClearButtons();

    // Load user session if exists
    loadUserSession();

    ui->stackedWidget->setCurrentIndex(MAIN_WINDOW);
}

MainWindow::~MainWindow()
{
    delete player;
    delete ui;
}

//add a function to a clickable label
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->label_picture && event->type() == QEvent::MouseButtonPress) {
        if(loggedIN){
            ui->stackedWidget->setCurrentIndex(PROFILE_WINDOW);
        }
        return true;
    }
    if (obj == ui->label_guest && event->type() == QEvent::MouseButtonPress) {
        if(loggedIN){
            ui->stackedWidget->setCurrentIndex(PROFILE_WINDOW);
        }
        return true;
    }
    return false;
}

void MainWindow::on_pushButton_close_main_clicked()
{
    close();
}

void MainWindow::on_pushButton_login_from_main_clicked() {
    // Check if user is not logged in
    if (!loggedIN) {
        // Navigate to the login window
        ui->stackedWidget->setCurrentIndex(LOGIN_WINDOW);
    } else {
        // Ask for confirmation before logging out
        QMessageBox::StandardButton confirmLogout;
        confirmLogout = QMessageBox::question(this, "Logout", "Are you sure you want to logout?",
                                              QMessageBox::Yes | QMessageBox::No);
        // If user confirms logout
        if (confirmLogout == QMessageBox::Yes) {
            // Set labels to default values
            ui->label_guest->setText("Guest");
            ui->label_19->setText("Guest");

            // Change profile picture to default
            QImage image("../../pictures/user.jpg");
            changePictures(image);

            // Update login status
            loggedIN = false;
            ui->pushButton_login_from_main->setText("Sign In");

            // Clear user session data from local storage
            QSettings settings("MyApp", "MyApp");
            settings.remove("id");
            settings.remove("username");
            settings.remove("password");
            settings.remove("ImageData");

            // Delete player object
            delete player;
        }
    }
}

void MainWindow::on_back_from_login_to_main_clicked()
{
    ui->stackedWidget->setCurrentIndex(MAIN_WINDOW);
}

void MainWindow::on_pushButton_back_from_signup_to_login_clicked()
{
    ui->stackedWidget->setCurrentIndex(LOGIN_WINDOW);
}

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
        QMessageBox::information(this, "Success", "You have successfully signed In!");
        // Clear input fields
        ui->lineEdit_user->setText("");
        ui->lineEdit_pass->setText("");

        // Create player object with retrieved data
        Player *tempPlayer = new Player(id, username, password, image);
        player = tempPlayer;

        // Update UI with user information
        ui->label_guest->setText(username);
        ui->label_19->setText(username);
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

void MainWindow::on_pushButton_signup_from_login_clicked()
{
    ui->stackedWidget->setCurrentIndex(SIGNUP_WINDOW);
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

void MainWindow::on_pushButton_back_from_board_to_main_clicked()
{
    ui->stackedWidget->setCurrentIndex(MAIN_WINDOW);
}

void MainWindow::on_pushButton_back_from_player2_to_main_clicked()
{
    ui->stackedWidget->setCurrentIndex(MAIN_WINDOW);
}

void MainWindow::on_pushButton_enter_player2name_clicked()
{
    ui->stackedWidget->setCurrentIndex(PLAYER2_WINDOW);
}

void MainWindow::on_pushButton_confirm_player2_clicked()
{
    ui->stackedWidget->setCurrentIndex(BOARD_WINDOW);
}

void MainWindow::on_pushButton_play_withAI_clicked()
{
    ui->stackedWidget->setCurrentIndex(BOARD_WINDOW);
}

void MainWindow::on_pushButton_back_from_profile_to_main_clicked()
{
    ui->stackedWidget->setCurrentIndex(MAIN_WINDOW);
}

void MainWindow::on_pushButton_from_main_to_profile_clicked()
{
    ui->stackedWidget->setCurrentIndex(PROFILE_WINDOW);
}

void MainWindow::on_pushButton_change_user_pass_clicked()
{
    ui->stackedWidget->setCurrentIndex(PROFILE_WINDOW);
}

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
    int handl = db.changePassword(player->getId(), oldPassword, newPassword);

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
        player->setHashedPassword(newPassword);

        // Update password in local storage
        QSettings settings("MyApp", "MyApp");
        settings.setValue("password", newPassword);

        // Navigate to profile window
        ui->stackedWidget->setCurrentIndex(PROFILE_WINDOW);
        break;
    }
}

void MainWindow::on_pushButton_not_change_pass_clicked()
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
    int handl = db.changeUsername(player->getId(), newUsername, password);

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
        player->setUsername(newUsername);

        // Update username in local storage
        QSettings settings("MyApp", "MyApp");
        settings.setValue("username", newUsername);

        // Navigate to profile window
        ui->stackedWidget->setCurrentIndex(PROFILE_WINDOW);
        break;
    }
}

void MainWindow::on_pushButton_not_change_username_clicked()
{
    ui->stackedWidget->setCurrentIndex(PROFILE_WINDOW);
}

void MainWindow::on_pushButton_change_username_from_profile_clicked()
{
    ui->stackedWidget->setCurrentIndex(CHANGE_USERNAME_WINDOW);
}

void MainWindow::on_pushButton_change_password_from_profile_clicked()
{
    ui->stackedWidget->setCurrentIndex(CHANGE_PASSWORD_WINDOW);
}

void MainWindow::on_pushButton_load_session_clicked()
{
    ui->stackedWidget->setCurrentIndex(SESSIONS_WINDOW);
}

void MainWindow::on_pushButton_back_from_session_to_main_clicked()
{
    ui->stackedWidget->setCurrentIndex(MAIN_WINDOW);
}

void MainWindow::on_pushButton_back_from_history_to_session_clicked()
{
    ui->stackedWidget->setCurrentIndex(SESSIONS_WINDOW);
}

void MainWindow::on_pushButton_back_from_history_to_session_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(SESSIONS_WINDOW);
}

void MainWindow::on_pushButton_session1_clicked()
{
    ui->stackedWidget->setCurrentIndex(GAMES_WINDOW);
}

void MainWindow::on_showPasswordCheckbox_stateChanged()
{
    if (ui->showPasswordCheckbox->isChecked()){
        ui->lineEdit_pass->setEchoMode(QLineEdit::Normal);
    } else {
        ui->lineEdit_pass->setEchoMode(QLineEdit::Password);
    }
}

void MainWindow::on_checkBox_oldpass_stateChanged()
{
    if (ui->checkBox_oldpass->isChecked()){
        ui->lineEdit_old_pass->setEchoMode(QLineEdit::Normal);
    } else {
        ui->lineEdit_old_pass->setEchoMode(QLineEdit::Password);
    }
}

void MainWindow::on_checkBox_newpass_stateChanged()
{
    if (ui->checkBox_newpass->isChecked()){
        ui->lineEdit_new_pass->setEchoMode(QLineEdit::Normal);
    } else {
        ui->lineEdit_new_pass->setEchoMode(QLineEdit::Password);
    }
}

void MainWindow::on_checkBox_confirm_newpass_stateChanged()
{
    if (ui->checkBox_confirm_newpass->isChecked()){
        ui->lineEdit_change_pass->setEchoMode(QLineEdit::Normal);
    } else {
        ui->lineEdit_change_pass->setEchoMode(QLineEdit::Password);
    }
}

void MainWindow::on_checkBox_changeuser_stateChanged()
{
    if (ui->checkBox_changeuser->isChecked()){
        ui->lineEdit_pass_to_change_user->setEchoMode(QLineEdit::Normal);
    } else {
        ui->lineEdit_pass_to_change_user->setEchoMode(QLineEdit::Password);
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

void MainWindow::on_pushButton_replay_clicked()
{
    ui->label_6->clear();
    ui->label_28->clear();
    ui->label_29->clear();
    ui->label_30->clear();
    ui->label_31->clear();
    ui->label_32->clear();
    ui->label_33->clear();
    ui->label_34->clear();
    ui->label_35->clear();
}

void MainWindow::on_Change_photo_clicked() {
    // Open file dialog to select an image
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Select Image", QDir::homePath(), "Images (*.png *.jpg *.bmp)");

    if (!filePath.isEmpty()) {
        // Load the selected image into a QImage variable
        QImage originalImage(filePath);

        // Update player's image
        player->setImage(originalImage);

        // Display the selected image
        changePictures(originalImage);

        // Resize the image to ensure it fits within desired dimensions
        originalImage = originalImage.scaled(200, 200, Qt::KeepAspectRatio);

        // Convert the displayed image to Base64 format and save it to QSettings
        QByteArray imageData;
        QBuffer buffer(&imageData);
        buffer.open(QIODevice::WriteOnly);
        originalImage.save(&buffer, "PNG"); // Save as PNG format
        QString base64Image = QString::fromLatin1(imageData.toBase64().data());

        // Save the Base64-encoded image data to QSettings
        QSettings settings("MyCompany", "MyApp");
        settings.setValue("ImageData", base64Image);

        // Update image in the database
        db.changeImage(player->getId(), imageData);

        qDebug() << "Image selected and loaded successfully!";
    } else {
        qDebug() << "No image selected.";
    }
}
