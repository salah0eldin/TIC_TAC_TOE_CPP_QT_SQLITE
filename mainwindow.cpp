#include "mainwindow.h"
#include "ui_mainwindow.h"

QString hashing(const QString& str) {
    const int p = 31; // Prime number
    const int m = 1e9 + 9; // Modulo value
    unsigned long long hash_value = 0;
    unsigned long long p_pow = 1;

    for (QChar c : str) {
        hash_value = (hash_value + (c.unicode() - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }

    return QString::number(hash_value); // Convert hash_value to QString before returning
}

void MainWindow::changePictures(QImage &originalImage){
    if(originalImage.isNull())
        originalImage = QImage("../../pictures/user.jpg");
    // Check if resizing is necessary
    if (originalImage.width() > 200 || originalImage.height() > 200) {
        // Resize the image while maintaining aspect ratio if it's larger than 200x200 pixels
        originalImage = originalImage.scaled(200, 200, Qt::KeepAspectRatio);
    }

    // Set the pixmap of the QLabel
    ui->label_pic->setPixmap(QPixmap::fromImage(originalImage));

    QImage image2 = originalImage.scaled(75,75, Qt::KeepAspectRatio);

    ui->label_picture->setPixmap(QPixmap::fromImage(image2));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Center the text in the label of board at history
    ui->label_6->setAlignment(Qt::AlignCenter);
    ui->label_31->setAlignment(Qt::AlignCenter);
    ui->label_32->setAlignment(Qt::AlignCenter);
    ui->label_28->setAlignment(Qt::AlignCenter);
    ui->label_29->setAlignment(Qt::AlignCenter);
    ui->label_30->setAlignment(Qt::AlignCenter);
    ui->label_33->setAlignment(Qt::AlignCenter);
    ui->label_34->setAlignment(Qt::AlignCenter);
    ui->label_35->setAlignment(Qt::AlignCenter);

    //add a default text "Guest" to the line edit of player2
    ui->lineEdit_player2->setText("Guest");

    //make picture label clickable
    ui->label_picture->setCursor(Qt::PointingHandCursor);
    ui->label_picture->installEventFilter(this);

    //make label clickable
    ui->label_guest->setCursor(Qt::PointingHandCursor);
    ui->label_guest->installEventFilter(this);

    //add picture at label
    QPixmap pix1 ("../../pictures/user.jpg");
    int w1 =ui->label_picture->width();
    int h1 =ui->label_picture->height();
    ui->label_picture->setPixmap(pix1.scaled(w1,h1,Qt::KeepAspectRatio));

    QPixmap pix ("../../pictures/aaa.jpg");
    int w =ui->label_pic->width();
    int h =ui->label_pic->height();
    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    //add holder text at line edit
    ui->lineEdit_user->setPlaceholderText("Username");
    ui->lineEdit_pass->setPlaceholderText("Password");

    //add picture to icons
    QIcon user ("../../pictures/user.jpg");
    ui->lineEdit_user->addAction(user,QLineEdit ::LeadingPosition);
    QIcon pass ("../../pictures/password.png");
    ui->lineEdit_pass->addAction(pass,QLineEdit ::LeadingPosition);

    //add close buttom to clear the text at line edit
    ui->lineEdit_pass->setClearButtonEnabled(true);
    ui->lineEdit_user->setClearButtonEnabled(true);
    ui->lineEdit_old_pass->setClearButtonEnabled(true);
    ui->lineEdit_new_pass->setClearButtonEnabled(true);
    ui->lineEdit_change_pass->setClearButtonEnabled(true);
    ui->lineEdit_change_username->setClearButtonEnabled(true);
    ui->lineEdit_pass_to_change_user->setClearButtonEnabled(true);
    ui->lineEdit_player2->setClearButtonEnabled(true);
    ui->lineEdit_user_signup->setClearButtonEnabled(true);
    ui->lineEdit_pass_signup->setClearButtonEnabled(true);
    ui->lineEdit_pass2_signup->setClearButtonEnabled(true);

    QSettings settings("MyApp", "MyApp");
    if(settings.contains("id")){
    int id = settings.value("id").toInt();
    QString username = settings.value("username").toString();
    QString password = settings.value("password").toString();

    QString base64Image = settings.value("ImageData").toString();
    QByteArray imageData = QByteArray::fromBase64(base64Image.toLatin1());
    QImage image;
    image.loadFromData(imageData, "PNG");

    changePictures(image);

    player = new Player(id,username,password,image);
    ui->label_guest->setText(username);
    ui->label_19->setText(username);

    loggedIN = true;
    ui->pushButton_login_from_main->setText("Log Out");

    } else
        loggedIN = false;

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

void MainWindow::on_pushButton_login_from_main_clicked()
{
    if (!loggedIN) {
        ui->stackedWidget->setCurrentIndex(LOGIN_WINDOW);
    } else {
        QMessageBox::StandardButton confirmLogout;
        confirmLogout = QMessageBox::question(this, "Logout", "Are you sure you want to logout?",
                                              QMessageBox::Yes | QMessageBox::No);
        if (confirmLogout == QMessageBox::Yes) {
            ui->label_guest->setText("Guest");
            ui->label_19->setText("Quest");

            QImage image("../../pictures/user.jpg");
            changePictures(image);
            loggedIN = false;
            ui->pushButton_login_from_main->setText("Sign In");
            QSettings settings("MyApp", "MyApp");
            settings.remove("id");
            settings.remove("username");
            settings.remove("password");
            settings.remove("ImageData");
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

void MainWindow::on_pushButton_login_to_main_clicked()
{
    QString username = ui->lineEdit_user->text();
    QString password = hashing(ui->lineEdit_pass->text());
    // Check if username or password is empty
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Username or password can't be empty.");
        return; // Exit the function early
    }
    int id;
    QImage image;
    int handl = db.signIn(username,password,id,image);
    if (handl == DATABASE_ERROR) {
        QMessageBox::warning(this, "Error", "Error in database, try again later.");
    } else if (handl == WRONG_USERNAME || handl == WRONG_PASSWORD) {
        QMessageBox::warning(this, "Error", "Wrong username or password.");
        ui->lineEdit_user->setText("");
        ui->lineEdit_pass->setText("");
    } else if (handl == SIGNED_IN) {
        QMessageBox::information(this, "Success", "You have successfully signed In!");
        ui->lineEdit_user->setText("");
        ui->lineEdit_pass->setText("");

        Player *tempPlayer = new Player(id,username,password,image);
        player = tempPlayer;
        ui->label_guest->setText(username);
        ui->label_19->setText(username);
        changePictures(image);
        // Save the credentials to local storage
        QSettings settings("MyApp", "MyApp");
        settings.setValue("id",id);
        settings.setValue("username", username);
        settings.setValue("password", password);

        // Convert the displayed image to Base64 format and save it to QSettings
        QByteArray imageData;
        QBuffer buffer(&imageData);
        buffer.open(QIODevice::WriteOnly);
        image.save(&buffer, "PNG"); // Save as PNG format
        QString base64Image = QString::fromLatin1(imageData.toBase64().data());
        settings.setValue("ImageData", base64Image);

        loggedIN = true;
        ui->pushButton_login_from_main->setText("Log Out");
        ui->stackedWidget->setCurrentIndex(MAIN_WINDOW);
    }


}

void MainWindow::on_pushButton_signup_from_login_clicked()
{
    ui->stackedWidget->setCurrentIndex(SIGNUP_WINDOW);
}

void MainWindow::on_pushButton_signup_to_main_clicked()
{
    QString username = ui->lineEdit_user_signup->text();
    QString password = ui->lineEdit_pass_signup->text();
    QString confirmPassword = ui->lineEdit_pass2_signup->text();

    // Check if username or password is empty
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Username or password can't be empty.");
        return; // Exit the function early
    }
    else{
        if(password != confirmPassword){
            QMessageBox::warning(this, "Error", "Passwords don't match.");
            ui->lineEdit_pass_signup->setText("");
            ui->lineEdit_pass2_signup->setText("");
            return;
        }
        password = hashing(password);
        int handl = db.signUp(username,password);
        if (handl == DATABASE_ERROR) {
            QMessageBox::warning(this, "Error", "Error in database, try again later.");
        } else if (handl == USERNAME_TAKEN) {
            QMessageBox::warning(this, "Error", "Username already taken.");
            ui->lineEdit_user_signup->setText("");
            ui->lineEdit_pass_signup->setText("");
            ui->lineEdit_pass2_signup->setText("");
        } else if (handl == SIGNED_UP) {
            QMessageBox::information(this, "Success", "You have successfully signed up!,please sign in");
            ui->lineEdit_user_signup->setText("");
            ui->lineEdit_pass_signup->setText("");
            ui->lineEdit_pass2_signup->setText("");
            ui->stackedWidget->setCurrentIndex(LOGIN_WINDOW);
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

void MainWindow::on_pushButton_change_pass_clicked()
{
    QString oldPassword = ui->lineEdit_old_pass->text();
    QString newPassword = ui->lineEdit_new_pass->text();
    QString confirmPassword = ui->lineEdit_change_pass->text();

    if (oldPassword.isEmpty() || newPassword.isEmpty() || confirmPassword.isEmpty()) {
        QMessageBox::warning(this, "Error", "Username or password can't be empty.");
        return; // Exit the function early
    }

    if(newPassword != confirmPassword){
        QMessageBox::warning(this, "Error", "Passwords don't match");
        return;
    }

    oldPassword = hashing(oldPassword);
    newPassword = hashing(newPassword);

    int handl = db.changePassword(player->getId(),oldPassword,newPassword);

    switch(handl){
    case DATABASE_ERROR:
        QMessageBox::warning(this, "Error", "Error in database, try again later.");
        break;
    case WRONG_PASSWORD:
        QMessageBox::warning(this, "Error", "Wrong Password.");
        ui->lineEdit_old_pass->setText("");
        break;
    case DATABASE_SUCCESS:
        QMessageBox::information(this, "Success", "Password changed");
        ui->lineEdit_old_pass->setText("");
        ui->lineEdit_change_pass->setText("");
        ui->lineEdit_change_pass->setText("");

        player->setHashedPassword(newPassword);
        QSettings settings("MyApp", "MyApp");
        settings.setValue("password", newPassword);

        ui->stackedWidget->setCurrentIndex(PROFILE_WINDOW);
        break;
    }
}

void MainWindow::on_pushButton_not_change_pass_clicked()
{
    ui->stackedWidget->setCurrentIndex(PROFILE_WINDOW);
}

void MainWindow::on_pushButton_change_username_clicked()
{
    QString newUsername = ui->lineEdit_change_username->text();
    QString password = ui->lineEdit_pass_to_change_user->text();

    if (newUsername.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Username or password can't be empty.");
        return; // Exit the function early
    }

    password = hashing(password);

    int handl = db.changeUsername(player->getId(),newUsername,password);

    switch(handl){
    case DATABASE_ERROR:
        QMessageBox::warning(this, "Error", "Error in database, try again later.");
        break;
    case WRONG_PASSWORD:
        QMessageBox::warning(this, "Error", "Wrong Password.");
        ui->lineEdit_pass_to_change_user->setText("");
        break;
    case USERNAME_TAKEN:
        QMessageBox::warning(this, "Error", "Username already taken.");
        ui->lineEdit_pass_to_change_user->setText("");
        ui->lineEdit_pass_to_change_user->setText("");
        break;
    case DATABASE_SUCCESS:
        QMessageBox::information(this, "Success", "Username changed");
        ui->lineEdit_pass_to_change_user->setText("");
        ui->lineEdit_pass_to_change_user->setText("");

        ui->label_guest->setText(newUsername);
        ui->label_19->setText(newUsername);

        player->setUsername(newUsername);
        QSettings settings("MyApp", "MyApp");
        settings.setValue("username", newUsername);

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

void MainWindow::on_Change_photo_clicked()
{
    // Open file dialog to select an image
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Select Image", QDir::homePath(), "Images (*.png *.jpg *.bmp)");

    if (!filePath.isEmpty()) {
        // Load the selected image into a QImage variable
        QImage originalImage(filePath);
        player->setImage(originalImage);
        changePictures(originalImage);

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

        db.changeImage(player->getId(),imageData);

        qDebug() << "Image selected and loaded successfully!";
    } else {
        qDebug() << "No image selected.";
    }
}

