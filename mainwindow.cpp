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

void MainWindow::on_pushButton_from_main_to_profile_clicked()
{
    ui->stackedWidget->setCurrentIndex(PROFILE_WINDOW);
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


