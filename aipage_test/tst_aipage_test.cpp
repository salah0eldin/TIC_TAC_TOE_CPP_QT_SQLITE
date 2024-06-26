#include <QtTest>

// add necessary includes here

class aipage_test : public QObject
{
    Q_OBJECT

public:
    aipage_test();
    ~aipage_test();

private slots:
    void test_case1();
};

aipage_test::aipage_test() {}

aipage_test::~aipage_test() {}

void aipage_test::test_case1() {}

QTEST_APPLESS_MAIN(aipage_test)

#include "tst_aipage_test.moc"
