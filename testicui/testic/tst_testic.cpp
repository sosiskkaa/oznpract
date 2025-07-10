#include <QtTest>
#include "tst_testic.h"

//setup/cleanup
void testik::init()
{
    a = A0;
    b = B0;
}

//test_dan
void testik::test_nod_data()
{
    QTest::addColumn<int>("x");
    QTest::addColumn<int>("y");
    QTest::addColumn<int>("result");

    QTest::newRow("5 10") << 5 << 10 << 5;
    QTest::newRow("10 10") << 10 << 10 << 10;
    QTest::newRow("10 110") << 10 << 110 << 10;
    QTest::newRow("10 23") << 10 << 23 << 1;
    QTest::newRow("1 5") << 1 << 5 << 1;
    QTest::newRow("0 5") << 0 << 5 << 5;
    QTest::newRow("12 18") << 12 << 18 << 6;
}

void testik::test_nok_data()
{
    QTest::addColumn<int>("x");
    QTest::addColumn<int>("y");
    QTest::addColumn<int>("result");

    QTest::newRow("5 10") << 5 << 10 << 10;
    QTest::newRow("10 10") << 10 << 10 << 10;
    QTest::newRow("7 5") << 7 << 5 << 35;
    QTest::newRow("1 5") << 1 << 5 << 5;
    QTest::newRow("0 5") << 0 << 5 << 0;
}

void testik::test_prostx_data()
{
    QTest::addColumn<int>("x");
    QTest::addColumn<int>("result");

    QTest::newRow("5 - prost") << 5 << 5;
    QTest::newRow("10 - ne prost") << 10 << 0;
    QTest::newRow("1 - ne prost") << 1 << 0;
    QTest::newRow("25 - ne prost") << 25 << 0;
    QTest::newRow("23 - prost") << 23 << 23;
}

void testik::test_prosty_data()
{
    QTest::addColumn<int>("y");
    QTest::addColumn<int>("result");

    QTest::newRow("5 - prost") << 5 << 5;
    QTest::newRow("10 - ne prost") << 10 << 0;
    QTest::newRow("1 - ne prost") << 1 << 0;
    QTest::newRow("25 - ne prost") << 25 << 0;
    QTest::newRow("23 - prost") << 23 << 23;
}

void testik::test_isarmstrongx_data()
{
    QTest::addColumn<int>("x");
    QTest::addColumn<bool>("result");

    QTest::newRow("153 - arm") << 153 << true;
    QTest::newRow("370 - arm") << 370 << true;
    QTest::newRow("123 - ne arm") << 123 << false;
    QTest::newRow("1 - arm") << 1 << true;
    QTest::newRow("0 - arm") << 0 << true;
}

void testik::test_isarmstrongy_data()
{
    QTest::addColumn<int>("y");
    QTest::addColumn<bool>("result");

    QTest::newRow("153 - arm") << 153 << true;
    QTest::newRow("371 - arm") << 371 << true;
    QTest::newRow("123 - ne arm") << 123 << false;
    QTest::newRow("1 - arm") << 1 << true;
    QTest::newRow("0 - arm") << 0 << true;
}

//testi
void testik::test_nod()
{
    QFETCH(int, x);
    QFETCH(int, y);
    QFETCH(int, result);

    chisl c(x, y);
    QCOMPARE(c.nod(), result);
}

void testik::test_nok()
{
    QFETCH(int, x);
    QFETCH(int, y);
    QFETCH(int, result);

    chisl c(x, y);
    QCOMPARE(c.nok(), result);
}

void testik::test_prostx()
{
    QFETCH(int, x);
    QFETCH(int, result);

    chisl c(x, 0);
    QCOMPARE(c.prostx(), result);
}

// Тест prosty()
void testik::test_prosty()
{
    QFETCH(int, y);
    QFETCH(int, result);

    chisl c(0, y);
    QCOMPARE(c.prosty(), result);
}

void testik::test_isarmstrongx()
{
    QFETCH(int, x);
    QFETCH(bool, result);

    chisl c(x, 0);
    QCOMPARE(c.isarmstrongx(), result);
}

void testik::test_isarmstrongy()
{
    QFETCH(int, y);
    QFETCH(bool, result);

    chisl c(0, y);
    QCOMPARE(c.isarmstrongy(), result);
}

testik::testik() {}
testik::~testik() {}

QTEST_APPLESS_MAIN(testik)

//#include "tst_testik.moc"
