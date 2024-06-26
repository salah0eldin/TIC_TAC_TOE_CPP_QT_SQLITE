#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_Change_photo_clicked() {
    // Open file dialog to select an image
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Select Image", QDir::homePath(), "Images (*.png *.jpg *.bmp)");

    if (!filePath.isEmpty()) {
        // Load the selected image into a QImage variable
        QImage originalImage(filePath);

        // Update player's image
        player.setImage(originalImage);

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
        QSettings settings("MyApp", "MyApp");
        settings.setValue("ImageData", base64Image);

        // Update image in the database
        db.changeImage(player.getId(), imageData);

        qDebug() << "Image selected and loaded successfully!";
    } else {
        qDebug() << "No image selected.";
    }
}

// Back button from profile to main window
void MainWindow::on_pushButton_back_from_profile_to_main_clicked()
{
    ui->stackedWidget->setCurrentIndex(MAIN_WINDOW);
}

// Change username button from profile
void MainWindow::on_pushButton_change_username_from_profile_clicked()
{
    ui->stackedWidget->setCurrentIndex(CHANGE_USERNAME_WINDOW);
}

// Change password button from profile
void MainWindow::on_pushButton_change_password_from_profile_clicked()
{
    ui->stackedWidget->setCurrentIndex(CHANGE_PASSWORD_WINDOW);
}
