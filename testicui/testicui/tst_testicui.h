#ifndef TST_TESTICUI_H
#define TST_TESTICUI_H

#include <QtTest>
#include <QMainWindow>
#include "../chisla/chislui.h"

class testicui : public QObject
{
    Q_OBJECT

public:
    testicui();
    ~testicui();

private slots:
    void initTestCase();
    void cleanupTestCase();
    //void init();
    void cleanup();

    //void testUiElements();
    void testNodCalculation();
    void testNokCalculation();
    void testProstNumbers();
    void testArmstrongNumbers();
    void testOperations_data();
    void testOperations();

private:
    chislui* m_window;
};

#endif // TST_TESTICUI_H
