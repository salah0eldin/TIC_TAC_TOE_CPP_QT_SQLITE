#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// ----------------------------------------------------------------------------
// Includes
// ----------------------------------------------------------------------------

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

// ----------------------------------------------------------------------------
// Defines
// ----------------------------------------------------------------------------

// @brief Window identifiers for different UI states.
#define MAIN_WINDOW             0
#define PROFILE_WINDOW          1
#define CHANGE_USERNAME_WINDOW  2
#define CHANGE_PASSWORD_WINDOW  3
#define LOGIN_WINDOW            4
#define SIGNUP_WINDOW           5
#define PLAYER2_WINDOW          6
#define AI_WINDOW               7
#define BOARD_WINDOW            8
#define SESSIONS_WINDOW         9
#define GAMES_WINDOW            10

// @brief index for styles in styles vector
#define NORMAL          0
#define SELECTED        1
#define MESSAGE_BOX     2
#define BUTTONS_STYLE   3
#define BUTTONS_STYLE2  4

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// ----------------------------------------------------------------------------
// Class Definitions
// ----------------------------------------------------------------------------

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Constructs the MainWindow object.
     * @param parent The parent widget.
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Destroys the MainWindow object.
     */
    ~MainWindow();

    DatabaseManager db;                // Database manager instance.
    Player player;                     // Player instance.
    Session CurrentSession;            // Current session instance.
    Game CurrentGame;                  // Current game instance.
    int diff;                          // Difficulty level.
    bool Ai;                           // AI mode flag.
    bool loggedIN;                     // Login status flag.
    QPushButton *button[9];            // Buttons array for the board.
    QLabel *labelBoard[9];             // Label array for the board.
    QVector<QString> styles;           // Vector for styles
    QVector<QPushButton *> sessionsButtons; // Vector of session buttons.

protected:
    /**
     * @brief Filters events if this object has been installed as an event filter for the watched object.
     * @param obj The object watched.
     * @param event The event.
     * @return True if the event should be filtered, false otherwise.
     */
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
    void loadUserSession();
    QString hashing(const QString& str);
    void on_checkBox_changeuser_stateChanged(int arg1);
    void boardPlaceMarker(int index1, int index2);
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
    void loadSessionGames(int sessionId);
    void populateSession(const Session &s);
    void updatePopulateSession(const Session &s);
    void loadGame(int gameId);
    void on_pushButton_31_clicked();
    void on_pushButton_30_clicked();
    void change_playing_styles();
    void change_revew_styles();

private:
    QSignalMapper *signalMapper;      // Signal mapper instance.
    QSignalMapper *signalMapper2;     // Second signal mapper instance.
    Ui::MainWindow *ui;               // UI instance.
};

#endif // MAINWINDOW_H
