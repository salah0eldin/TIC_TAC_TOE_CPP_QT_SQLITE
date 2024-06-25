#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMessageBox>
#include <QFileDialog>
#include <QMainWindow>
#include <QCheckBox>
#include <QPainter>
#include <QBuffer>
#include <QString>
#include <QImage>
#include <QDebug>

#include "databasemanager.h"
#include "aiAlgorithm.h"
#include "player.h"

#define MAIN_WINDOW             0
#define PROFILE_WINDOW          1
#define CHANGE_USERNAME_WINDOW  2
#define CHANGE_PASSWORD_WINDOW  3
#define LOGIN_WINDOW            4
#define SIGNUP_WINDOW           5
#define PLAYER2_WINDOW          6
#define BOARD_WINDOW            8
#define SESSIONS_WINDOW         9
#define GAMES_WINDOW            10
#define AI_WINDOW               7

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    DatabaseManager db;
    Player player;
    Session CurrentSession;
    Game CurrentGame;
    int diff; //difficulty
    bool Ai;
    bool loggedIN;
    QPushButton *button[9];

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:

    void on_pushButton_login_from_main_clicked();

    void on_back_from_login_to_main_clicked();

    void on_pushButton_back_from_signup_to_login_clicked();

    void on_pushButton_login_to_main_clicked();

    void on_pushButton_signup_from_login_clicked();

    void on_pushButton_signup_to_main_clicked();

    void on_pushButton_back_from_board_to_main_clicked();

    void on_pushButton_back_from_player2_to_main_clicked();

    void on_pushButton_enter_player2name_clicked();

    void on_pushButton_confirm_player2_clicked();

    void on_pushButton_back_from_profile_to_main_clicked();

    void on_pushButton_from_main_to_profile_clicked();

    void on_pushButton_change_pass_clicked();

    void on_pushButton_not_change_pass_clicked();

    void on_pushButton_change_username_clicked();

    void on_pushButton_not_change_username_clicked();

    void on_pushButton_change_username_from_profile_clicked();

    void on_pushButton_change_password_from_profile_clicked();

    void on_pushButton_load_session_clicked();

    void on_pushButton_back_from_session_to_main_clicked();

    void on_pushButton_close_main_clicked();

    void on_showPasswordCheckbox_stateChanged();

    void on_pushButton_play_withAI_clicked();

    void on_checkBox_oldpass_stateChanged();

    void on_checkBox_pass_signup_stateChanged();

    void on_checkBox_changeuser_stateChanged();

    void on_checkBox_confirm_pass_signup_stateChanged();

    void on_checkBox_newpass_stateChanged();

    void on_checkBox_confirm_newpass_stateChanged();

    void on_pushButton_back_from_history_to_session_clicked();

    void on_pushButton_replay_clicked();

    void on_pushButton_back_from_history_to_session_2_clicked();

    void on_pushButton_session1_clicked();

    void on_Change_photo_clicked();

    void changePictures(QImage &image);

    // Function to load user session if it exists
    void loadUserSession();

    QString hashing(const QString& str);

    void on_checkBox_changeuser_stateChanged(int arg1);

    void boardPlaceMarker(int index1,int index2);

    void on_b0_clicked();

    void on_b2_clicked();

    void on_b7_clicked();

    void on_b3_clicked();

    void on_b1_clicked();

    void on_b6_clicked();

    void on_b5_clicked();

    void on_b4_clicked();

    void on_b8_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void ai_to_board(QString opponame);

    void resetBoard_checkAi();

    void on_pushButton_15_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
