#include <QtTest/QtTest>
#include "../player.h"

class TestPlayer : public QObject
{
    Q_OBJECT

private slots:
    void testGetters()
    {
        const int id = 1;
        QString username = "testUser";
        QString hashedPassword = "hashedPassword";
        QImage image(100, 100, QImage::Format_RGB32); // Creating a dummy image for testing
        Player player(id, username, hashedPassword, image);

        QCOMPARE(player.getId(), id);
        QCOMPARE(player.getUsername(), username);
        QCOMPARE(player.getHashedPassword(), hashedPassword);
        QCOMPARE(player.getImage(), image);
    }

    void testSetters()
    {
        Player player;
        const int id = 2;
        QString username = "newUser";
        QString hashedPassword = "newHashedPassword";
        QImage image(200, 200, QImage::Format_RGB32); // Creating a dummy image for testing

        player.setId(id);
        player.setUsername(username);
        player.setHashedPassword(hashedPassword);
        player.setImage(image);

        QCOMPARE(player.getId(), id);
        QCOMPARE(player.getUsername(), username);
        QCOMPARE(player.getHashedPassword(), hashedPassword);
        QCOMPARE(player.getImage(), image);
    }

    void testSessionFunctions()
    {
        Player player;
        Session session;

        QCOMPARE(player.getSessions().size(), 0);

        player.addSession(session);
        QCOMPARE(player.getSessions().size(), 1);

        player.removeSessionAt(0);
        QCOMPARE(player.getSessions().size(), 0);
    }
};

QTEST_APPLESS_MAIN(TestPlayer)
#include "test_player.moc"
