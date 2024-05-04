/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *main;
    QPushButton *pushButton_login_from_main;
    QPushButton *pushButton_close_main;
    QPushButton *pushButton_enter_player2name;
    QPushButton *pushButton_3;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton_from_main_to_profile;
    QPushButton *pushButton_load_session;
    QLabel *label_picture;
    QWidget *profile;
    QPushButton *pushButton_back_from_profile_to_main;
    QPushButton *pushButton_change_username_from_profile;
    QPushButton *pushButton_change_password_from_profile;
    QLabel *label_52;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_17;
    QLabel *label_19;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_18;
    QLabel *label_20;
    QLabel *label_pic;
    QWidget *change_username;
    QPushButton *pushButton_not_change_username;
    QPushButton *pushButton_change_username;
    QLabel *label_23;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_21;
    QLineEdit *lineEdit_change_username;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_22;
    QLineEdit *lineEdit_pass_to_change_user;
    QWidget *change_password;
    QLabel *label_48;
    QPushButton *pushButton_not_change_pass;
    QPushButton *pushButton_change_pass;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_49;
    QLineEdit *lineEdit_old_pass;
    QHBoxLayout *horizontalLayout_22;
    QLabel *label_47;
    QLineEdit *lineEdit_new_pass;
    QHBoxLayout *horizontalLayout_23;
    QLabel *label_50;
    QLineEdit *lineEdit_change_pass;
    QWidget *login;
    QPushButton *back_from_login_to_main;
    QCheckBox *showPasswordCheckbox;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QPushButton *pushButton_signup_from_login;
    QPushButton *pushButton_change_user_pass;
    QPushButton *pushButton_login_to_main;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_user;
    QLineEdit *lineEdit_user;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_pass;
    QLineEdit *lineEdit_pass;
    QWidget *signup;
    QLabel *label_11;
    QPushButton *pushButton_back_from_signup_to_login;
    QPushButton *pushButton_signup_to_main;
    QWidget *layoutWidget4;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_8;
    QLineEdit *lineEdit_user_signup;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_9;
    QLineEdit *lineEdit_pass_signup;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_10;
    QLineEdit *lineEdit_pass2_signup;
    QWidget *player2;
    QPushButton *pushButton_back_from_player2_to_main;
    QPushButton *pushButton_confirm_player2;
    QLabel *label_16;
    QWidget *layoutWidget5;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_15;
    QLineEdit *lineEdit_player2;
    QWidget *board;
    QPushButton *pushButton;
    QPushButton *pushButton_7;
    QPushButton *pushButton_10;
    QPushButton *pushButton_11;
    QPushButton *pushButton_12;
    QPushButton *pushButton_13;
    QPushButton *pushButton_14;
    QPushButton *pushButton_16;
    QPushButton *pushButton_17;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QPushButton *pushButton_back_from_board_to_main;
    QLabel *label_53;
    QLabel *label_54;
    QLabel *label_55;
    QPushButton *pushButton_8;
    QPushButton *pushButton_9;
    QWidget *sessions;
    QLabel *label_51;
    QPushButton *pushButton_back_from_session_to_main;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 0, 801, 541));
        stackedWidget->setMaximumSize(QSize(801, 541));
        stackedWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 85, 127);"));
        main = new QWidget();
        main->setObjectName("main");
        main->setMinimumSize(QSize(0, 531));
        pushButton_login_from_main = new QPushButton(main);
        pushButton_login_from_main->setObjectName("pushButton_login_from_main");
        pushButton_login_from_main->setGeometry(QRect(660, 10, 81, 31));
        pushButton_login_from_main->setMinimumSize(QSize(81, 31));
        pushButton_login_from_main->setStyleSheet(QString::fromUtf8("font: 10pt \"Segoe UI\";\n"
""));
        pushButton_close_main = new QPushButton(main);
        pushButton_close_main->setObjectName("pushButton_close_main");
        pushButton_close_main->setGeometry(QRect(80, 430, 91, 31));
        pushButton_enter_player2name = new QPushButton(main);
        pushButton_enter_player2name->setObjectName("pushButton_enter_player2name");
        pushButton_enter_player2name->setGeometry(QRect(290, 160, 191, 31));
        pushButton_enter_player2name->setStyleSheet(QString::fromUtf8("font: 700 12pt \"Segoe UI\";"));
        pushButton_3 = new QPushButton(main);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(290, 230, 191, 31));
        pushButton_3->setStyleSheet(QString::fromUtf8("font: 700 12pt \"Segoe UI\";"));
        label = new QLabel(main);
        label->setObjectName("label");
        label->setGeometry(QRect(130, 10, 41, 21));
        label_2 = new QLabel(main);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(290, 50, 181, 31));
        label_2->setStyleSheet(QString::fromUtf8("font: 900 italic 24pt \"Segoe UI\";\n"
"\n"
"color: rgb(255, 255, 255);"));
        pushButton_from_main_to_profile = new QPushButton(main);
        pushButton_from_main_to_profile->setObjectName("pushButton_from_main_to_profile");
        pushButton_from_main_to_profile->setGeometry(QRect(110, 40, 80, 24));
        pushButton_load_session = new QPushButton(main);
        pushButton_load_session->setObjectName("pushButton_load_session");
        pushButton_load_session->setGeometry(QRect(330, 320, 111, 31));
        pushButton_load_session->setMinimumSize(QSize(81, 31));
        pushButton_load_session->setStyleSheet(QString::fromUtf8("font: 10pt \"Segoe UI\";\n"
""));
        label_picture = new QLabel(main);
        label_picture->setObjectName("label_picture");
        label_picture->setGeometry(QRect(10, 10, 71, 61));
        stackedWidget->addWidget(main);
        profile = new QWidget();
        profile->setObjectName("profile");
        pushButton_back_from_profile_to_main = new QPushButton(profile);
        pushButton_back_from_profile_to_main->setObjectName("pushButton_back_from_profile_to_main");
        pushButton_back_from_profile_to_main->setGeometry(QRect(60, 460, 81, 31));
        pushButton_change_username_from_profile = new QPushButton(profile);
        pushButton_change_username_from_profile->setObjectName("pushButton_change_username_from_profile");
        pushButton_change_username_from_profile->setGeometry(QRect(430, 280, 191, 41));
        pushButton_change_username_from_profile->setStyleSheet(QString::fromUtf8("font: 12pt \"Segoe UI\";"));
        pushButton_change_password_from_profile = new QPushButton(profile);
        pushButton_change_password_from_profile->setObjectName("pushButton_change_password_from_profile");
        pushButton_change_password_from_profile->setGeometry(QRect(430, 350, 191, 41));
        pushButton_change_password_from_profile->setStyleSheet(QString::fromUtf8("font: 12pt \"Segoe UI\";"));
        label_52 = new QLabel(profile);
        label_52->setObjectName("label_52");
        label_52->setGeometry(QRect(320, 40, 91, 31));
        label_52->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 700 16pt \"Segoe UI\";"));
        layoutWidget = new QWidget(profile);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(340, 140, 361, 91));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_17 = new QLabel(layoutWidget);
        label_17->setObjectName("label_17");
        label_17->setStyleSheet(QString::fromUtf8("font: 700 16pt \"Segoe UI\";\n"
"color: rgb(255, 255, 255);\n"
""));

        horizontalLayout_7->addWidget(label_17);

        label_19 = new QLabel(layoutWidget);
        label_19->setObjectName("label_19");

        horizontalLayout_7->addWidget(label_19);


        verticalLayout_3->addLayout(horizontalLayout_7);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label_18 = new QLabel(layoutWidget);
        label_18->setObjectName("label_18");
        label_18->setStyleSheet(QString::fromUtf8("font: 700 16pt \"Segoe UI\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_8->addWidget(label_18);

        label_20 = new QLabel(layoutWidget);
        label_20->setObjectName("label_20");

        horizontalLayout_8->addWidget(label_20);


        verticalLayout_3->addLayout(horizontalLayout_8);

        label_pic = new QLabel(profile);
        label_pic->setObjectName("label_pic");
        label_pic->setGeometry(QRect(10, 90, 241, 221));
        stackedWidget->addWidget(profile);
        change_username = new QWidget();
        change_username->setObjectName("change_username");
        pushButton_not_change_username = new QPushButton(change_username);
        pushButton_not_change_username->setObjectName("pushButton_not_change_username");
        pushButton_not_change_username->setGeometry(QRect(80, 440, 91, 31));
        pushButton_change_username = new QPushButton(change_username);
        pushButton_change_username->setObjectName("pushButton_change_username");
        pushButton_change_username->setGeometry(QRect(550, 440, 91, 31));
        label_23 = new QLabel(change_username);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(280, 50, 201, 41));
        label_23->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 700 16pt \"Segoe UI\";"));
        layoutWidget1 = new QWidget(change_username);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(190, 180, 431, 101));
        verticalLayout_4 = new QVBoxLayout(layoutWidget1);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        label_21 = new QLabel(layoutWidget1);
        label_21->setObjectName("label_21");
        label_21->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 700 16pt \"Segoe UI\";"));

        horizontalLayout_10->addWidget(label_21);

        lineEdit_change_username = new QLineEdit(layoutWidget1);
        lineEdit_change_username->setObjectName("lineEdit_change_username");

        horizontalLayout_10->addWidget(lineEdit_change_username);


        verticalLayout_4->addLayout(horizontalLayout_10);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        label_22 = new QLabel(layoutWidget1);
        label_22->setObjectName("label_22");
        label_22->setStyleSheet(QString::fromUtf8("font: 700 16pt \"Segoe UI\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_9->addWidget(label_22);

        lineEdit_pass_to_change_user = new QLineEdit(layoutWidget1);
        lineEdit_pass_to_change_user->setObjectName("lineEdit_pass_to_change_user");
        lineEdit_pass_to_change_user->setEchoMode(QLineEdit::Password);

        horizontalLayout_9->addWidget(lineEdit_pass_to_change_user);


        verticalLayout_4->addLayout(horizontalLayout_9);

        stackedWidget->addWidget(change_username);
        change_password = new QWidget();
        change_password->setObjectName("change_password");
        label_48 = new QLabel(change_password);
        label_48->setObjectName("label_48");
        label_48->setGeometry(QRect(280, 50, 181, 51));
        label_48->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 700 16pt \"Segoe UI\";"));
        pushButton_not_change_pass = new QPushButton(change_password);
        pushButton_not_change_pass->setObjectName("pushButton_not_change_pass");
        pushButton_not_change_pass->setGeometry(QRect(80, 443, 91, 31));
        pushButton_change_pass = new QPushButton(change_password);
        pushButton_change_pass->setObjectName("pushButton_change_pass");
        pushButton_change_pass->setGeometry(QRect(590, 440, 91, 31));
        layoutWidget2 = new QWidget(change_password);
        layoutWidget2->setObjectName("layoutWidget2");
        layoutWidget2->setGeometry(QRect(150, 140, 451, 171));
        verticalLayout_9 = new QVBoxLayout(layoutWidget2);
        verticalLayout_9->setObjectName("verticalLayout_9");
        verticalLayout_9->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setObjectName("horizontalLayout_21");
        label_49 = new QLabel(layoutWidget2);
        label_49->setObjectName("label_49");
        label_49->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 700 16pt \"Segoe UI\";"));

        horizontalLayout_21->addWidget(label_49);

        lineEdit_old_pass = new QLineEdit(layoutWidget2);
        lineEdit_old_pass->setObjectName("lineEdit_old_pass");
        lineEdit_old_pass->setEchoMode(QLineEdit::Password);

        horizontalLayout_21->addWidget(lineEdit_old_pass);


        verticalLayout_9->addLayout(horizontalLayout_21);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setObjectName("horizontalLayout_22");
        label_47 = new QLabel(layoutWidget2);
        label_47->setObjectName("label_47");
        label_47->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 700 16pt \"Segoe UI\";\n"
""));

        horizontalLayout_22->addWidget(label_47);

        lineEdit_new_pass = new QLineEdit(layoutWidget2);
        lineEdit_new_pass->setObjectName("lineEdit_new_pass");
        lineEdit_new_pass->setEchoMode(QLineEdit::Password);

        horizontalLayout_22->addWidget(lineEdit_new_pass);


        verticalLayout_9->addLayout(horizontalLayout_22);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setObjectName("horizontalLayout_23");
        label_50 = new QLabel(layoutWidget2);
        label_50->setObjectName("label_50");
        label_50->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 700 16pt \"Segoe UI\";"));

        horizontalLayout_23->addWidget(label_50);

        lineEdit_change_pass = new QLineEdit(layoutWidget2);
        lineEdit_change_pass->setObjectName("lineEdit_change_pass");
        lineEdit_change_pass->setEchoMode(QLineEdit::Password);

        horizontalLayout_23->addWidget(lineEdit_change_pass);


        verticalLayout_9->addLayout(horizontalLayout_23);

        stackedWidget->addWidget(change_password);
        login = new QWidget();
        login->setObjectName("login");
        back_from_login_to_main = new QPushButton(login);
        back_from_login_to_main->setObjectName("back_from_login_to_main");
        back_from_login_to_main->setGeometry(QRect(40, 460, 80, 24));
        back_from_login_to_main->setStyleSheet(QString::fromUtf8("font: 10pt \"Segoe UI\";"));
        showPasswordCheckbox = new QCheckBox(login);
        showPasswordCheckbox->setObjectName("showPasswordCheckbox");
        showPasswordCheckbox->setGeometry(QRect(180, 210, 121, 31));
        showPasswordCheckbox->setStyleSheet(QString::fromUtf8("font: 9pt \"Segoe UI\";\n"
"color: rgb(255, 255, 255);"));
        label_5 = new QLabel(login);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(210, 300, 131, 21));
        label_6 = new QLabel(login);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(210, 270, 161, 21));
        label_7 = new QLabel(login);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(320, 20, 81, 31));
        label_7->setStyleSheet(QString::fromUtf8("font: 700 14pt \"Segoe UI\";\n"
"color: rgb(255, 255, 255);"));
        pushButton_signup_from_login = new QPushButton(login);
        pushButton_signup_from_login->setObjectName("pushButton_signup_from_login");
        pushButton_signup_from_login->setGeometry(QRect(340, 300, 80, 24));
        pushButton_change_user_pass = new QPushButton(login);
        pushButton_change_user_pass->setObjectName("pushButton_change_user_pass");
        pushButton_change_user_pass->setGeometry(QRect(380, 270, 80, 24));
        pushButton_login_to_main = new QPushButton(login);
        pushButton_login_to_main->setObjectName("pushButton_login_to_main");
        pushButton_login_to_main->setGeometry(QRect(290, 360, 111, 31));
        pushButton_login_to_main->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";"));
        layoutWidget3 = new QWidget(login);
        layoutWidget3->setObjectName("layoutWidget3");
        layoutWidget3->setGeometry(QRect(160, 100, 401, 111));
        verticalLayout = new QVBoxLayout(layoutWidget3);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_user = new QLabel(layoutWidget3);
        label_user->setObjectName("label_user");
        label_user->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 700 14pt \"Segoe UI\";"));

        horizontalLayout->addWidget(label_user);

        lineEdit_user = new QLineEdit(layoutWidget3);
        lineEdit_user->setObjectName("lineEdit_user");
        lineEdit_user->setEchoMode(QLineEdit::Normal);

        horizontalLayout->addWidget(lineEdit_user);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_pass = new QLabel(layoutWidget3);
        label_pass->setObjectName("label_pass");
        label_pass->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 700 14pt \"Segoe UI\";"));

        horizontalLayout_2->addWidget(label_pass);

        lineEdit_pass = new QLineEdit(layoutWidget3);
        lineEdit_pass->setObjectName("lineEdit_pass");
        lineEdit_pass->setEchoMode(QLineEdit::Password);

        horizontalLayout_2->addWidget(lineEdit_pass);


        verticalLayout->addLayout(horizontalLayout_2);

        stackedWidget->addWidget(login);
        signup = new QWidget();
        signup->setObjectName("signup");
        label_11 = new QLabel(signup);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(320, 50, 81, 31));
        label_11->setStyleSheet(QString::fromUtf8("\n"
"color: rgb(255, 255, 255);\n"
"font: 700 14pt \"Segoe UI\";"));
        pushButton_back_from_signup_to_login = new QPushButton(signup);
        pushButton_back_from_signup_to_login->setObjectName("pushButton_back_from_signup_to_login");
        pushButton_back_from_signup_to_login->setGeometry(QRect(50, 460, 80, 24));
        pushButton_signup_to_main = new QPushButton(signup);
        pushButton_signup_to_main->setObjectName("pushButton_signup_to_main");
        pushButton_signup_to_main->setGeometry(QRect(310, 340, 121, 31));
        layoutWidget4 = new QWidget(signup);
        layoutWidget4->setObjectName("layoutWidget4");
        layoutWidget4->setGeometry(QRect(150, 110, 451, 171));
        verticalLayout_2 = new QVBoxLayout(layoutWidget4);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_8 = new QLabel(layoutWidget4);
        label_8->setObjectName("label_8");
        label_8->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 700 12pt \"Segoe UI\";"));

        horizontalLayout_3->addWidget(label_8);

        lineEdit_user_signup = new QLineEdit(layoutWidget4);
        lineEdit_user_signup->setObjectName("lineEdit_user_signup");
        lineEdit_user_signup->setEchoMode(QLineEdit::Normal);

        horizontalLayout_3->addWidget(lineEdit_user_signup);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_9 = new QLabel(layoutWidget4);
        label_9->setObjectName("label_9");
        label_9->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 700 12pt \"Segoe UI\";"));

        horizontalLayout_4->addWidget(label_9);

        lineEdit_pass_signup = new QLineEdit(layoutWidget4);
        lineEdit_pass_signup->setObjectName("lineEdit_pass_signup");
        lineEdit_pass_signup->setEchoMode(QLineEdit::Password);

        horizontalLayout_4->addWidget(lineEdit_pass_signup);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_10 = new QLabel(layoutWidget4);
        label_10->setObjectName("label_10");
        label_10->setStyleSheet(QString::fromUtf8("font: 700 12pt \"Segoe UI\";\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_5->addWidget(label_10);

        lineEdit_pass2_signup = new QLineEdit(layoutWidget4);
        lineEdit_pass2_signup->setObjectName("lineEdit_pass2_signup");
        lineEdit_pass2_signup->setEchoMode(QLineEdit::Password);

        horizontalLayout_5->addWidget(lineEdit_pass2_signup);


        verticalLayout_2->addLayout(horizontalLayout_5);

        stackedWidget->addWidget(signup);
        player2 = new QWidget();
        player2->setObjectName("player2");
        pushButton_back_from_player2_to_main = new QPushButton(player2);
        pushButton_back_from_player2_to_main->setObjectName("pushButton_back_from_player2_to_main");
        pushButton_back_from_player2_to_main->setGeometry(QRect(70, 440, 91, 31));
        pushButton_confirm_player2 = new QPushButton(player2);
        pushButton_confirm_player2->setObjectName("pushButton_confirm_player2");
        pushButton_confirm_player2->setGeometry(QRect(550, 440, 91, 31));
        label_16 = new QLabel(player2);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(260, 30, 261, 41));
        label_16->setStyleSheet(QString::fromUtf8("font: 700 14pt \"Segoe UI\";\n"
"color: rgb(255, 255, 255);"));
        layoutWidget5 = new QWidget(player2);
        layoutWidget5->setObjectName("layoutWidget5");
        layoutWidget5->setGeometry(QRect(180, 130, 341, 31));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget5);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        label_15 = new QLabel(layoutWidget5);
        label_15->setObjectName("label_15");
        label_15->setStyleSheet(QString::fromUtf8("font: 700 14pt \"Segoe UI\";\n"
"color: rgb(255, 255, 255);\n"
"\n"
""));

        horizontalLayout_6->addWidget(label_15);

        lineEdit_player2 = new QLineEdit(layoutWidget5);
        lineEdit_player2->setObjectName("lineEdit_player2");

        horizontalLayout_6->addWidget(lineEdit_player2);

        stackedWidget->addWidget(player2);
        board = new QWidget();
        board->setObjectName("board");
        pushButton = new QPushButton(board);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(250, 140, 81, 81));
        pushButton_7 = new QPushButton(board);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setGeometry(QRect(340, 140, 81, 81));
        pushButton_10 = new QPushButton(board);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setGeometry(QRect(250, 230, 81, 81));
        pushButton_11 = new QPushButton(board);
        pushButton_11->setObjectName("pushButton_11");
        pushButton_11->setGeometry(QRect(430, 320, 81, 81));
        pushButton_12 = new QPushButton(board);
        pushButton_12->setObjectName("pushButton_12");
        pushButton_12->setGeometry(QRect(340, 320, 81, 81));
        pushButton_13 = new QPushButton(board);
        pushButton_13->setObjectName("pushButton_13");
        pushButton_13->setGeometry(QRect(250, 320, 81, 81));
        pushButton_14 = new QPushButton(board);
        pushButton_14->setObjectName("pushButton_14");
        pushButton_14->setGeometry(QRect(430, 230, 81, 81));
        pushButton_16 = new QPushButton(board);
        pushButton_16->setObjectName("pushButton_16");
        pushButton_16->setGeometry(QRect(620, 460, 91, 31));
        pushButton_17 = new QPushButton(board);
        pushButton_17->setObjectName("pushButton_17");
        pushButton_17->setGeometry(QRect(330, 460, 91, 31));
        label_12 = new QLabel(board);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(90, 10, 41, 21));
        label_12->setStyleSheet(QString::fromUtf8("font: 11pt \"Segoe UI\";\n"
"color: rgb(255, 255, 255);"));
        label_13 = new QLabel(board);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(360, 10, 51, 21));
        label_13->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 12pt \"Segoe UI\";"));
        label_14 = new QLabel(board);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(610, 10, 31, 21));
        label_14->setStyleSheet(QString::fromUtf8("font: 12pt \"Segoe UI\";\n"
"color: rgb(255, 255, 255);"));
        pushButton_back_from_board_to_main = new QPushButton(board);
        pushButton_back_from_board_to_main->setObjectName("pushButton_back_from_board_to_main");
        pushButton_back_from_board_to_main->setGeometry(QRect(40, 460, 91, 31));
        label_53 = new QLabel(board);
        label_53->setObjectName("label_53");
        label_53->setGeometry(QRect(100, 40, 41, 21));
        label_54 = new QLabel(board);
        label_54->setObjectName("label_54");
        label_54->setGeometry(QRect(370, 40, 41, 21));
        label_55 = new QLabel(board);
        label_55->setObjectName("label_55");
        label_55->setGeometry(QRect(610, 40, 41, 21));
        pushButton_8 = new QPushButton(board);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setGeometry(QRect(430, 140, 81, 81));
        pushButton_9 = new QPushButton(board);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setGeometry(QRect(340, 230, 81, 81));
        stackedWidget->addWidget(board);
        sessions = new QWidget();
        sessions->setObjectName("sessions");
        label_51 = new QLabel(sessions);
        label_51->setObjectName("label_51");
        label_51->setGeometry(QRect(300, 110, 141, 51));
        label_51->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 900 italic 20pt \"Segoe UI\";"));
        pushButton_back_from_session_to_main = new QPushButton(sessions);
        pushButton_back_from_session_to_main->setObjectName("pushButton_back_from_session_to_main");
        pushButton_back_from_session_to_main->setGeometry(QRect(60, 440, 91, 31));
        stackedWidget->addWidget(sessions);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(pushButton_close_main, &QPushButton::clicked, pushButton_close_main, qOverload<>(&QPushButton::hide));

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
#if QT_CONFIG(whatsthis)
        pushButton_login_from_main->setWhatsThis(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-weight:700;\">fff</span></p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        pushButton_login_from_main->setText(QCoreApplication::translate("MainWindow", "login", nullptr));
        pushButton_close_main->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        pushButton_enter_player2name->setText(QCoreApplication::translate("MainWindow", "Player Vs Player", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Player Vs AI", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Guest", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Tic Tac Toe", nullptr));
        pushButton_from_main_to_profile->setText(QCoreApplication::translate("MainWindow", "User", nullptr));
#if QT_CONFIG(whatsthis)
        pushButton_load_session->setWhatsThis(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-weight:700;\">fff</span></p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        pushButton_load_session->setText(QCoreApplication::translate("MainWindow", "Load", nullptr));
        label_picture->setText(QString());
        pushButton_back_from_profile_to_main->setText(QCoreApplication::translate("MainWindow", "Back", nullptr));
        pushButton_change_username_from_profile->setText(QCoreApplication::translate("MainWindow", "Change username", nullptr));
        pushButton_change_password_from_profile->setText(QCoreApplication::translate("MainWindow", "Change password", nullptr));
        label_52->setText(QCoreApplication::translate("MainWindow", "Profile", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "Username :", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "name", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "Password :", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "pass", nullptr));
        label_pic->setText(QString());
        pushButton_not_change_username->setText(QCoreApplication::translate("MainWindow", "Cancel", nullptr));
        pushButton_change_username->setText(QCoreApplication::translate("MainWindow", "Confirm", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "Change Username", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "New Username :", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "Password :", nullptr));
        label_48->setText(QCoreApplication::translate("MainWindow", "Change Password", nullptr));
        pushButton_not_change_pass->setText(QCoreApplication::translate("MainWindow", "Cancel", nullptr));
        pushButton_change_pass->setText(QCoreApplication::translate("MainWindow", "Confirm", nullptr));
        label_49->setText(QCoreApplication::translate("MainWindow", "Old Password", nullptr));
        label_47->setText(QCoreApplication::translate("MainWindow", "New Password", nullptr));
        label_50->setText(QCoreApplication::translate("MainWindow", "Confirm Password", nullptr));
        back_from_login_to_main->setText(QCoreApplication::translate("MainWindow", "Back", nullptr));
        showPasswordCheckbox->setText(QCoreApplication::translate("MainWindow", "Show Password", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Don't have an account? ", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Forget Username / Password?", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "LogIn", nullptr));
        pushButton_signup_from_login->setText(QCoreApplication::translate("MainWindow", "Sign Up", nullptr));
        pushButton_change_user_pass->setText(QCoreApplication::translate("MainWindow", "Click here", nullptr));
        pushButton_login_to_main->setText(QCoreApplication::translate("MainWindow", "Login", nullptr));
        label_user->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        label_pass->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Sign Up", nullptr));
        pushButton_back_from_signup_to_login->setText(QCoreApplication::translate("MainWindow", "Back", nullptr));
        pushButton_signup_to_main->setText(QCoreApplication::translate("MainWindow", "signup", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Confirm Password", nullptr));
        pushButton_back_from_player2_to_main->setText(QCoreApplication::translate("MainWindow", "Back", nullptr));
        pushButton_confirm_player2->setText(QCoreApplication::translate("MainWindow", "confirm", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Choose Name for Opponent", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Name :", nullptr));
        pushButton->setText(QString());
        pushButton_7->setText(QString());
        pushButton_10->setText(QString());
        pushButton_11->setText(QString());
        pushButton_12->setText(QString());
        pushButton_13->setText(QString());
        pushButton_14->setText(QString());
        pushButton_16->setText(QCoreApplication::translate("MainWindow", "Restart", nullptr));
        pushButton_17->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Wins", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Losses", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Tie", nullptr));
        pushButton_back_from_board_to_main->setText(QCoreApplication::translate("MainWindow", "Back", nullptr));
        label_53->setText(QCoreApplication::translate("MainWindow", "00", nullptr));
        label_54->setText(QCoreApplication::translate("MainWindow", "00", nullptr));
        label_55->setText(QCoreApplication::translate("MainWindow", "00", nullptr));
        pushButton_8->setText(QString());
        pushButton_9->setText(QString());
        label_51->setText(QCoreApplication::translate("MainWindow", "Sessions", nullptr));
        pushButton_back_from_session_to_main->setText(QCoreApplication::translate("MainWindow", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
