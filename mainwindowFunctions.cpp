#include "mainwindow.h"
#include "ui_mainwindow.h"

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
        Player p(id, username, password, image);
        player = p;
        ui->label_guest->setText(username);
        ui->label_19->setText(username);

        QVector<Session> s = db.loadHistory(id);
        player.setSessions(s);
        int ssize = s.size();
        player.setSessoinsCount(ssize);
        // Clear existing buttons if any

        QLayoutItem *item;
        QWidget *container = ui->scrollAreaWidgetContents_4;

        while ((item = container->layout()->takeAt(0)) != nullptr) {
            delete item->widget(); // Delete the widget
            delete item;           // Delete the layout item
        }

        for (Session s : player.getSessions()) {
            populateSession(s);
        }

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
