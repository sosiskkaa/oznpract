#ifndef TST_TESTIK_H
#define TST_TESTIK_H

#include <QtTest>
#include "../chisla/chisl.h"

class testik : public QObject
{
    Q_OBJECT

public:
    testik();
    ~testik();

private slots:
    //setup/cleanup
    void init();

    //test_dan
    void test_nod_data();
    void test_nok_data();
    void test_prostx_data();
    void test_prosty_data();
    void test_isarmstrongx_data();
    void test_isarmstrongy_data();

    //testi
    void test_nod();
    void test_nok();
    void test_prostx();
    void test_prosty();
    void test_isarmstrongx();
    void test_isarmstrongy();
private:
    const int A0 = 0;
    const int B0 = 0;

private:
    chisl a,b;
};

#endif // TST_TESTIK_H
