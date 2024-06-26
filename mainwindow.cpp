#include "mainwindow.h"
#include "ui_mainwindow.h"

// ----------------------------------------------------------------------------
// Constructor and Destructor
// ----------------------------------------------------------------------------

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set fixed size for the main window
    setFixedSize(900, 700);

    // Get the board buttons in game board
    button[0] = ui->b0;
    button[1] = ui->b2;
    button[2] = ui->b7;
    button[3] = ui->b1;
    button[4] = ui->b6;
    button[5] = ui->b5;
    button[6] = ui->b4;
    button[7] = ui->b8;
    button[8] = ui->b3;

    // Get the board labels in history board
    labelBoard[0] = ui->label_6;
    labelBoard[1] = ui->label_32;
    labelBoard[2] = ui->label_28;
    labelBoard[3] = ui->label_34;
    labelBoard[4] = ui->label_31;
    labelBoard[5] = ui->label_35;
    labelBoard[6] = ui->label_29;
    labelBoard[7] = ui->label_33;
    labelBoard[8] = ui->label_30;

    // Set cursor for all QPushButton instances in MainWindow
    QList<QPushButton *> allButtons = findChildren<QPushButton *>();
    for (QPushButton *btn : allButtons) {
        btn->setCursor(Qt::PointingHandCursor); // Example cursor shape (hand cursor)
    }

    // Set Clear Button Enabled for all QLineEdit instances in MainWindow
    QList<QLineEdit *> allLineEdit = findChildren<QLineEdit *>();
    for (QLineEdit *ledit : allLineEdit) {
        ledit->setClearButtonEnabled(true);
    }

    // Insert styles
    // NORMAL
    styles.push_back(R"(
                        color:rgb(113, 113, 113);
                        font-weight:bold;
                        font-size:20px;
                        background-color:rgba(85, 170, 255, 0);
                        )");
    // SELECTED
    styles.push_back(R"(color:white;
                        font-weight:bold;
                        font-size:26px;
                        background-color:rgba(85, 170, 255, 100);
                        )");

    // MESSAGE_BOX
    styles.push_back(R"(
                        QMessageBox { background-image: url(../../pictures/mesbg.png); background-repeat: no-repeat; background-position: center; font-family:  sans-serif;font-size:12px;font-Weight:bold;color:white;}
                        QMessageBox QPushButton { background-color: rgb(92, 142, 146); color: white; padding: 5px 10px; border-radius: 3px; font-size: 14px; font-weight: bold; min-width: 30px; min-height: 10px; border: none; }
                        QMessageBox QPushButton:hover { background-color: rgb(204, 177, 161); }
                        QMessageBox QPushButton:disabled { background-color: #cccccc; color: #666666;}
                        )");

    // BUTTONS_STYLE
    styles.push_back(R"(
                        QPushButton {
                            background-color: rgb(92, 142, 146); /* Light gray background */
                            color: white; /* Dark text color */
                            padding: 10px;
                            border-radius: 5px; /* Rounded corners */
                            font-size: 22px;
                            font-weight: bold;
                            min-width: 100px;
                            min-height: 30px;
                            text-align:left;
                        }

                        QPushButton:hover {
                            background-color: rgb(143, 111, 117); /* Green background on hover */
                            color: white; /* White text on hover */
                        }

                        QPushButton:disabled {
                            background-color: #cccccc; /* Gray background when disabled */
                            border-color: #aaaaaa; /* Gray border when disabled */
                            color: #666666; /* Gray text when disabled */
                        }
                        )");

    // MESSAGE_BOX2
    styles.push_back(R"(
                        QPushButton {
                            background-color: rgb(92, 142, 146); /* Light gray background */
                            color: white; /* Dark text color */
                            padding: 10px;
                            border-radius: 5px; /* Rounded corners */
                            font-size: 18px;
                            font-weight: bold;
                            min-width: 100px;
                            min-height: 30px;
                        }

                        QPushButton:hover {
                            background-color: rgb(143, 111, 117); /* Green background on hover */
                            color: white; /* White text on hover */
                        }

                        QPushButton:disabled {
                            background-color: #cccccc; /* Gray background when disabled */
                            border-color: #aaaaaa; /* Gray border when disabled */
                            color: #666666; /* Gray text when disabled */
                        }
                        )");



    // Set cursor for label_picture
    ui->label_picture->setCursor(Qt::PointingHandCursor);
    ui->label_picture->installEventFilter(this);
    ui->label_guest->setCursor(Qt::PointingHandCursor);
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

    // Set placeholders and icons for line edits
    QIcon user("../../pictures/user.jpg");
    ui->lineEdit_user->addAction(user, QLineEdit::LeadingPosition);
    QIcon pass("../../pictures/password.png");
    ui->lineEdit_pass->addAction(pass, QLineEdit::LeadingPosition);

    // Initialize signal mapper for sessions
    signalMapper = new QSignalMapper(this);
    connect(signalMapper, &QSignalMapper::mappedInt, this, &MainWindow::loadSessionGames);

    // Initialize signal mapper for games
    signalMapper2 = new QSignalMapper(this);
    connect(signalMapper2, &QSignalMapper::mappedInt, this, &MainWindow::loadGame);

    // Load user session if exists
    loadUserSession();

    // Set initial index for stacked widget
    ui->stackedWidget->setCurrentIndex(MAIN_WINDOW);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ----------------------------------------------------------------------------
// Event Filter
// ----------------------------------------------------------------------------

/**
 * @brief Event filter for handling clickable labels.
 * @param obj The watched object.
 * @param event The event.
 * @return True if the event is handled, false otherwise.
 */
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->label_picture && event->type() == QEvent::MouseButtonPress) {
        if (loggedIN) {
            ui->stackedWidget->setCurrentIndex(PROFILE_WINDOW);
        }
        return true;
    }
    if (obj == ui->label_guest && event->type() == QEvent::MouseButtonPress) {
        if (loggedIN) {
            ui->stackedWidget->setCurrentIndex(PROFILE_WINDOW);
        }
        return true;
    }
    return false;
}

// ----------------------------------------------------------------------------
// Button Click Handlers
// ----------------------------------------------------------------------------

/**
 * @brief Handles the close button click event.
 */
void MainWindow::on_pushButton_close_main_clicked()
{
    close();
}

/**
 * @brief Handles the login/logout button click event.
 */
void MainWindow::on_pushButton_login_from_main_clicked()
{
    if (!loggedIN) {
        ui->stackedWidget->setCurrentIndex(LOGIN_WINDOW);
    } else {
        // Ask for confirmation before logging out
        QMessageBox::StandardButton confirmLogout;
        confirmLogout = QMessageBox::question(this, "Logout", "Are you sure you want to logout?",
                                              QMessageBox::Yes | QMessageBox::No);
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

/**
 * @brief Handles the player vs player button click event.
 */
void MainWindow::on_pushButton_enter_player2name_clicked()
{
    Ai = false;
    if (loggedIN) {
        ui->stackedWidget->setCurrentIndex(PLAYER2_WINDOW);
    } else {
        ui->label->setText("Guest2");
        ui->label_40->setText("Guest");
        ui->stackedWidget->setCurrentIndex(BOARD_WINDOW);
    }
}

/**
 * @brief Handles the play vs AI button click event.
 */
void MainWindow::on_pushButton_play_withAI_clicked()
{
    Ai = true;
    ui->stackedWidget->setCurrentIndex(AI_WINDOW);
}

/**
 * @brief Handles the load session button click event.
 */
void MainWindow::on_pushButton_load_session_clicked()
{
    if (loggedIN) {
        ui->stackedWidget->setCurrentIndex(SESSIONS_WINDOW);
    } else {
        QMessageBox::warning(this, "Not Logged In", "Log in first to save history and load.");
    }
}

// Placeholder functions for unused buttons
void MainWindow::on_pushButton_session1_clicked(){}
void MainWindow::on_pushButton_back_from_history_to_session_2_clicked(){}
void MainWindow::on_pushButton_from_main_to_profile_clicked(){}

// ----------------------------------------------------------------------------
// Utility Functions
// ----------------------------------------------------------------------------

/**
 * @brief Loads user session data from local storage.
 * If user data exists, updates the UI and player information.
 */
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
        player.setSessionsCount(ssize);

        // Clear existing buttons if any
        QLayoutItem *item;
        QWidget *container = ui->scrollAreaWidgetContents_4;
        while ((item = container->layout()->takeAt(0)) != nullptr) {
            delete item->widget(); // Delete the widget
            delete item;           // Delete the layout item
        }
        sessionsButtons.clear();

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

/**
 * @brief Hashes a given QString using a custom algorithm.
 * @param str The input string to be hashed.
 * @return The resulting hash as a QString.
 */
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

/**
 * @brief Updates the UI with new user pictures.
 * @param originalImage The new user image to be set.
 */
void MainWindow::changePictures(QImage &originalImage) {
    if (originalImage.isNull())
        originalImage = QImage("../../pictures/user.jpg");

    // Resize the image if it's larger than 300x300 pixels
    if (originalImage.width() > 300 || originalImage.height() > 300) {
        originalImage = originalImage.scaled(300, 300, Qt::KeepAspectRatio);
    }

    // Set the pixmap of the QLabel
    ui->label_pic->setPixmap(QPixmap::fromImage(originalImage));

    QImage image2 = originalImage.scaled(100, 100, Qt::KeepAspectRatio);
    ui->label_picture->setPixmap(QPixmap::fromImage(image2));
}
