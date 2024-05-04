#include "mainwindow.h"
#include "ui_mainwindow.h"

// Function to center align labels
void MainWindow::centerLabels() {
    ui->label_6->setAlignment(Qt::AlignCenter);
    ui->label_31->setAlignment(Qt::AlignCenter);
    ui->label_32->setAlignment(Qt::AlignCenter);
    ui->label_28->setAlignment(Qt::AlignCenter);
    ui->label_29->setAlignment(Qt::AlignCenter);
    ui->label_30->setAlignment(Qt::AlignCenter);
    ui->label_33->setAlignment(Qt::AlignCenter);
    ui->label_34->setAlignment(Qt::AlignCenter);
    ui->label_35->setAlignment(Qt::AlignCenter);
}

// Function to make a QLabel clickable
void MainWindow::makeLabelClickable(QLabel* label) {
    label->setCursor(Qt::PointingHandCursor);
    label->installEventFilter(this);
}

// Function to set initial pictures
void MainWindow::setInitialPictures() {
    // Set default picture for label_picture
    QPixmap pix1("../../pictures/user.jpg");
    int w1 = ui->label_picture->width();
    int h1 = ui->label_picture->height();
    ui->label_picture->setPixmap(pix1.scaled(w1, h1, Qt::KeepAspectRatio));

    // Set default picture for label_pic
    QPixmap pix("../../pictures/aaa.jpg");
    int w = ui->label_pic->width();
    int h = ui->label_pic->height();
    ui->label_pic->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));
}

// Function to add placeholder text to line edits
void MainWindow::addPlaceholderText() {
    ui->lineEdit_user->setPlaceholderText("Username");
    ui->lineEdit_pass->setPlaceholderText("Password");
}

// Function to add pictures to icons
void MainWindow::addPicturesToIcons() {
    QIcon user("../../pictures/user.jpg");
    ui->lineEdit_user->addAction(user, QLineEdit::LeadingPosition);
    QIcon pass("../../pictures/password.png");
    ui->lineEdit_pass->addAction(pass, QLineEdit::LeadingPosition);
}

// Function to enable clear buttons for line edits
void MainWindow::enableClearButtons() {
    ui->lineEdit_pass->setClearButtonEnabled(true);
    ui->lineEdit_user->setClearButtonEnabled(true);
    // Add more line edits as needed
}

// Function to load user session data
void MainWindow::loadUserSession() {
    QSettings settings("MyApp", "MyApp");
    if (settings.contains("id")) {
        // Retrieve user session data from settings
        int id = settings.value("id").toInt();
        QString username = settings.value("username").toString();
        QString password = settings.value("password").toString();
        QString base64Image = settings.value("ImageData").toString();

        // Decode image data from Base64
        QByteArray imageData = QByteArray::fromBase64(base64Image.toLatin1());
        QImage image;
        image.loadFromData(imageData, "PNG");

        // Update UI with user session data
        changePictures(image);
        player = new Player(id, username, password, image);
        ui->label_guest->setText(username);
        ui->label_19->setText(username);

        // Update login status
        loggedIN = true;
        ui->pushButton_login_from_main->setText("Log Out");

    } else {
        loggedIN = false;
    }
}

// Function to hash a QString
QString MainWindow::hashing(const QString& str) {
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

// Function to change pictures in labels
void MainWindow::changePictures(QImage &originalImage) {
    if (originalImage.isNull())
        originalImage = QImage("../../pictures/user.jpg");

    // Check if resizing is necessary
    if (originalImage.width() > 200 || originalImage.height() > 200) {
        // Resize the image while maintaining aspect ratio if it's larger than 200x200 pixels
        originalImage = originalImage.scaled(200, 200, Qt::KeepAspectRatio);
    }

    // Set the pixmap of the QLabel
    ui->label_pic->setPixmap(QPixmap::fromImage(originalImage));

    QImage image2 = originalImage.scaled(75, 75, Qt::KeepAspectRatio);
    ui->label_picture->setPixmap(QPixmap::fromImage(image2));
}
