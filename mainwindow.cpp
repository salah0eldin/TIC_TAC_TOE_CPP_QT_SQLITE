#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCheckBox>
#include <QMessageBox>

#define main            0
#define profile         1
#define change_username 2
#define change_password 3
#define login           4
#define signup          5
#define player2         6
#define board           7
#define sessions        8

#include <QString>

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



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix ("../../pictures/aaa.jpg");
    int w =ui->label_pic->width();
    int h =ui->label_pic->height();
    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    QPixmap pix1 ("../../pictures/user.jpg");
    int w1 =ui->label_picture->width();
    int h1 =ui->label_picture->height();
    ui->label_picture->setPixmap(pix1.scaled(w1,h1,Qt::KeepAspectRatio));

    ui->lineEdit_user->setPlaceholderText("Username");
    ui->lineEdit_pass->setPlaceholderText("Password");

    QIcon user ("../../pictures/user.jpg");
    ui->lineEdit_user->addAction(user,QLineEdit ::LeadingPosition);
    QIcon pass ("../../pictures/password.png");
    ui->lineEdit_pass->addAction(pass,QLineEdit ::LeadingPosition);


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
    int id = settings.value("id").toInt();
    QString username = settings.value("username").toString();
    QString password = settings.value("password").toString();

    if(username != ""){
        player = new Player(id,username,password);
        ui->label->setText(username);
        loggedIN = true;
        ui->pushButton_login_from_main->setText("Log Out");
    }else
        loggedIN = false;

}

MainWindow::~MainWindow()
{
    delete player;
    delete ui;
}

void MainWindow::on_pushButton_close_main_clicked()
{
    close();
}

void MainWindow::on_showPasswordCheckbox_stateChanged(int arg1)
{
    if (ui->showPasswordCheckbox->isChecked()){
        ui->lineEdit_pass->setEchoMode(QLineEdit::Normal);
    } else {
        ui->lineEdit_pass->setEchoMode(QLineEdit::Password);
    }
}


void MainWindow::on_pushButton_login_from_main_clicked()
{
    if (!loggedIN) {
        ui->stackedWidget->setCurrentIndex(login);
    } else {
        QMessageBox::StandardButton confirmLogout;
        confirmLogout = QMessageBox::question(this, "Logout", "Are you sure you want to logout?",
                                              QMessageBox::Yes | QMessageBox::No);
        if (confirmLogout == QMessageBox::Yes) {
            ui->label->setText("Guest");
            loggedIN = false;
            ui->pushButton_login_from_main->setText("Sign In");
            QSettings settings("MyApp", "MyApp");
            settings.remove("id");
            settings.remove("username");
            settings.remove("password");
            delete player;
        }
    }
}

void MainWindow::on_back_from_login_to_main_clicked()
{
    ui->stackedWidget->setCurrentIndex(main);
}

void MainWindow::on_pushButton_back_from_signup_to_login_clicked()
{
    ui->stackedWidget->setCurrentIndex(main);
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
    int handl = db.signIn(username,password,id);
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
        Player *tempPlayer = new Player(id,username,password);
        player = tempPlayer;
        ui->label->setText(username);

        // Save the credentials to local storage
        QSettings settings("MyApp", "MyApp");
        settings.setValue("id",id);
        settings.setValue("username", username);
        settings.setValue("password", password);
        loggedIN = true;
        ui->pushButton_login_from_main->setText("Log Out");
        ui->stackedWidget->setCurrentIndex(main);
    }


}

void MainWindow::on_pushButton_signup_from_login_clicked()
{
    ui->stackedWidget->setCurrentIndex(signup);
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
            ui->stackedWidget->setCurrentIndex(login);
        }

    }
}


void MainWindow::on_pushButton_back_from_board_to_main_clicked()
{
    ui->stackedWidget->setCurrentIndex(main);
}

void MainWindow::on_pushButton_back_from_player2_to_main_clicked()
{
    ui->stackedWidget->setCurrentIndex(main);
}

void MainWindow::on_pushButton_enter_player2name_clicked()
{
    ui->stackedWidget->setCurrentIndex(player2);
}

void MainWindow::on_pushButton_confirm_player2_clicked()
{
    ui->stackedWidget->setCurrentIndex(board);
}

void MainWindow::on_pushButton_back_from_profile_to_main_clicked()
{
    ui->stackedWidget->setCurrentIndex(main);
}

void MainWindow::on_pushButton_from_main_to_profile_clicked()
{
    ui->stackedWidget->setCurrentIndex(profile);
}

void MainWindow::on_pushButton_change_user_pass_clicked()
{
    ui->stackedWidget->setCurrentIndex(profile);
}

void MainWindow::on_pushButton_change_pass_clicked()
{
    ui->stackedWidget->setCurrentIndex(profile);
}

void MainWindow::on_pushButton_not_change_pass_clicked()
{
    ui->stackedWidget->setCurrentIndex(profile);
}

void MainWindow::on_pushButton_change_username_clicked()
{
    ui->stackedWidget->setCurrentIndex(profile);
}

void MainWindow::on_pushButton_not_change_username_clicked()
{
    ui->stackedWidget->setCurrentIndex(profile);
}

void MainWindow::on_pushButton_change_username_from_profile_clicked()
{
    ui->stackedWidget->setCurrentIndex(change_username);
}

void MainWindow::on_pushButton_change_password_from_profile_clicked()
{
    ui->stackedWidget->setCurrentIndex(change_password);
}

void MainWindow::on_pushButton_load_session_clicked()
{
    ui->stackedWidget->setCurrentIndex(sessions);
}

void MainWindow::on_pushButton_back_from_session_to_main_clicked()
{
    ui->stackedWidget->setCurrentIndex(main);
}


