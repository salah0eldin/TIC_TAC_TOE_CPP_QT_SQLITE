#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    button[0] = ui->b0;
    button[1] = ui->b2;
    button[2] = ui->b7;
    button[3] = ui->b1;
    button[4] = ui->b6;
    button[5] = ui->b5;
    button[6] = ui->b4;
    button[7] = ui->b8;
    button[8] = ui->b3;

    ui->label_6->setAlignment(Qt::AlignCenter);
    ui->label_31->setAlignment(Qt::AlignCenter);
    ui->label_32->setAlignment(Qt::AlignCenter);
    ui->label_28->setAlignment(Qt::AlignCenter);
    ui->label_29->setAlignment(Qt::AlignCenter);
    ui->label_30->setAlignment(Qt::AlignCenter);
    ui->label_33->setAlignment(Qt::AlignCenter);
    ui->label_34->setAlignment(Qt::AlignCenter);
    ui->label_35->setAlignment(Qt::AlignCenter);

    ui->label_picture->setCursor(Qt::PointingHandCursor);
    ui->label_guest->installEventFilter(this);

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

    ui->lineEdit_user->setPlaceholderText("Username");
    ui->lineEdit_pass->setPlaceholderText("Password");

    QIcon user("../../pictures/user.jpg");
    ui->lineEdit_user->addAction(user, QLineEdit::LeadingPosition);
    QIcon pass("../../pictures/password.png");
    ui->lineEdit_pass->addAction(pass, QLineEdit::LeadingPosition);

    ui->lineEdit_pass->setClearButtonEnabled(true);
    ui->lineEdit_user->setClearButtonEnabled(true);

    // Load user session if exists
    loadUserSession();

    ui->stackedWidget->setCurrentIndex(MAIN_WINDOW);
}

MainWindow::~MainWindow()
{
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
            ui->label_40->setText("Guest");
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
        }
    }
}

void MainWindow::on_pushButton_enter_player2name_clicked()
{
    Ai = false;
    if(loggedIN){
        ui->stackedWidget->setCurrentIndex(PLAYER2_WINDOW);
    }else{
        ui->label->setText("Guest2");
        ui->label_40->setText("Guest2");
        ui->stackedWidget->setCurrentIndex(BOARD_WINDOW);
    }
}


void MainWindow::on_pushButton_play_withAI_clicked()
{
    Ai = true;
    ui->stackedWidget->setCurrentIndex(AI_WINDOW);
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

