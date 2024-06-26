#include <QtTest>

// add necessary includes here

class game_test : public QObject
{
    Q_OBJECT

public:
    game_test();
    ~game_test();

private slots:
    void test_case1();
};

game_test::game_test() {}

game_test::~game_test() {}

void game_test::test_case1() {}

QTEST_APPLESS_MAIN(game_test)

#include "tst_game_test.moc"
