#include "mainwindow.h"
#include "ui_mainwindow.h"

/**
 * @brief Populates the session view with a button representing the given session.
 * @param s The session object containing information to populate the button.
 */
void MainWindow::populateSession(const Session &s) {
    // Get the container widget for the scroll area
    QWidget *container = ui->scrollAreaWidgetContents_4;

    // Create a layout for the container if it doesn't have one
    QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(container->layout());
    if (!layout) {
        layout = new QVBoxLayout(container);
        container->setLayout(layout);
    }

    QPushButton *button = new QPushButton(this);
    sessionsButtons.push_back(button);

    // Set the button text with specificId() + 1
    QString buttonText = QString("(%1) - Vs %2 || Score(win: %3 ,ties: %4, loss: %5) || Date: %6")
                             .arg(s.getSpecificId() + 1)  // Increment specificId() by 1
                             .arg(s.getOpponentName())
                             .arg(s.getScore().wins)
                             .arg(s.getScore().ties)
                             .arg(s.getScore().losses)
                             .arg(s.getTimestamp().date().toString("MM-dd") + " " + s.getTimestamp().time().toString("HH:mm"));
    button->setText(buttonText);

    // Apply the stylesheet
    button->setStyleSheet(R"(
        QPushButton {
            background-color: rgb(50,50,200);
            border: none;
            color: white;
            width: 400px;
            height: 50px;
            padding: 15px 32px;
            text-align: center;
            text-decoration: none;
            font-size: 18px;
            margin: 4px 2px;
        }

        QPushButton:hover {
            background-color: white;
            color: black;
            border: 2px solid #4CAF50;
        }
    )");

    // Connect the button click to the signal mapper
    connect(button, &QPushButton::clicked, [this, button](){
        signalMapper->map(button);
    });

    // Set a unique identifier for the button
    signalMapper->setMapping(button, s.getSpecificId());

    // Insert the button at the top of the layout
    layout->insertWidget(0, button);
}

/**
 * @brief Updates the button representing the given session with new information.
 * @param s The updated session object.
 */
void MainWindow::updatePopulateSession(const Session &s){
    QPushButton *button = sessionsButtons[s.getSpecificId()];
    QString buttonText = QString("(%1) - Vs %2 || Score(win: %3 ,ties: %4, loss: %5) || Date: %6")
                             .arg(s.getSpecificId() + 1)  // Increment specificId() by 1
                             .arg(s.getOpponentName())
                             .arg(s.getScore().wins)
                             .arg(s.getScore().ties)
                             .arg(s.getScore().losses)
                             .arg(s.getTimestamp().date().toString("MM-dd") + " " + s.getTimestamp().time().toString("HH:mm"));
    button->setText(buttonText);
}

/**
 * @brief Loads and displays the games associated with a session.
 * @param sessionId The ID of the session whose games are to be loaded.
 */
void MainWindow::loadSessionGames(int sessionId) {
    CurrentSession = player.getSessions()[sessionId];

    // Get the container widget for the scroll area
    QFrame *container = ui->frame;
    QLayoutItem *item;

    // Clear previous widgets in the container
    while ((item = container->layout()->takeAt(0)) != nullptr) {
        delete item->widget(); // Delete the widget
        delete item;           // Delete the layout item
    }

    // Create a layout for the container if it doesn't have one
    QVBoxLayout *layout = qobject_cast<QVBoxLayout *>(container->layout());
    if (!layout) {
        layout = new QVBoxLayout(container);
        container->setLayout(layout);
    }

    // Iterate through games in the current session and create buttons for each game
    for (const Game &game : CurrentSession.getGames()) {
        QPushButton *button = new QPushButton(this);

        // Set the button text with specificId() + 1
        QString buttonText = QString("Game%1")
                                 .arg(game.getSpeceifiedId() + 1);  // Increment specificId() by 1
        button->setText(buttonText);

        // Apply the stylesheet
        button->setStyleSheet(R"(
            QPushButton {
                background-color: rgb(50,50,200);
                border: none;
                color: white;
                height: 20px;
                padding: 15px 32px;
                text-align: center;
                text-decoration: none;
                font-size: 18px;
                margin: 4px 2px;
            }

            QPushButton:hover {
                background-color: white;
                color: black;
                border: 2px solid #4CAF50;
            }
        )");

        // Connect the button click to the signal mapper
        connect(button, &QPushButton::clicked, [this, button](){
            signalMapper2->map(button);
        });

        // Set a unique identifier for the button
        signalMapper2->setMapping(button, game.getSpeceifiedId());

        // Insert the button into the layout
        layout->addWidget(button);
    }

    // Switch to the games window in the stacked widget
    ui->stackedWidget->setCurrentIndex(GAMES_WINDOW);

    // Load the first game in the session
    loadGame(0);
}

/**
 * @brief Handles the action when the "Back" button is clicked from session view to main window.
 */
void MainWindow::on_pushButton_back_from_session_to_main_clicked()
{
    ui->stackedWidget->setCurrentIndex(MAIN_WINDOW);
}
