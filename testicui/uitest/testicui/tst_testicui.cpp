#include "tst_testicui.h"
#include "../build/Desktop_Qt_6_8_2_MinGW_64_bit-Debug/chisla/ui_chislui.h"

testicui::testicui() {}

testicui::~testicui() {}

void testicui::initTestCase()
{
    m_window = new chislui();
    //m_window->show();
}

void testicui::cleanupTestCase()
{
    if (m_window)
    {
        delete m_window;
        m_window = nullptr;
    }
}

/*void testicui::init()
{
    m_window->ui->in1->clear();
    m_window->ui->in2->clear();
    m_window->ui->out->clear();
    m_window->ui->oper->setCurrentIndex(0);
    m_window->x = 0;
}*/

void testicui::cleanup() {}

/*void testicui::testUiElements()
{
    QVERIFY2(m_window->ui->in1, "Input field 1 not created");
    QVERIFY2(m_window->ui->in2, "Input field 2 not created");
    QVERIFY2(m_window->ui->out, "Output field not created");
    QVERIFY2(m_window->ui->oper, "Operation selector not created");
    QVERIFY2(m_window->ui->res, "Result button not created");
}*/

void testicui::testNodCalculation()
{
    m_window->ui->in1->setText("12");
    m_window->ui->in2->setText("18");
    m_window->ui->oper->setCurrentIndex(0);
    m_window->x = 0;

    QTest::mouseClick(m_window->ui->res, Qt::LeftButton);

    QCOMPARE(m_window->ui->out->text(), QString("6"));
}

void testicui::testNokCalculation()
{
    m_window->ui->in1->setText("12");
    m_window->ui->in2->setText("18");
    m_window->ui->oper->setCurrentIndex(1);
    m_window->x = 1;

    QTest::mouseClick(m_window->ui->res, Qt::LeftButton);

    QCOMPARE(m_window->ui->out->text(), QString("36"));
}

void testicui::testProstNumbers()
{
    m_window->ui->in1->setText("7");
    m_window->ui->in2->setText("8");
    m_window->ui->oper->setCurrentIndex(2);
    m_window->x = 2;

    QTest::mouseClick(m_window->ui->res, Qt::LeftButton);

    QString expected = "7 prostoe, 8 ne prostoe";
    QCOMPARE(m_window->ui->out->text(), expected);
}

void testicui::testArmstrongNumbers()
{
    m_window->ui->in1->setText("153");
    m_window->ui->in2->setText("154");
    m_window->ui->oper->setCurrentIndex(3);
    m_window->x = 3;

    QTest::mouseClick(m_window->ui->res, Qt::LeftButton);

    QString expected = "153 chislo armstronga, 154 ne chislo armstronga";
    QCOMPARE(m_window->ui->out->text(), expected);
}

void testicui::testOperations_data()
{
    QTest::addColumn<QString>("input1");
    QTest::addColumn<QString>("input2");
    QTest::addColumn<int>("operation");
    QTest::addColumn<QString>("expected");

    QTest::newRow("NOD 15 and 25") << "15" << "25" << 0 << "5";
    QTest::newRow("NOD 17 and 31") << "17" << "31" << 0 << "1";
    QTest::newRow("NOD 0 and 10") << "0" << "10" << 0 << "10";

    QTest::newRow("NOK 4 and 6") << "4" << "6" << 1 << "12";
    QTest::newRow("NOK 5 and 7") << "5" << "7" << 1 << "35";
    QTest::newRow("NOK 0 and 5") << "0" << "5" << 1 << "0";

    // Тест простых чисел
    QTest::newRow("Prime 11 and 12") << "11" << "12" << 2
                                     << "11 prostoe, 12 ne prostoe";
    QTest::newRow("Prime 1 and 2") << "1" << "2" << 2
                                   << "1 ne prostoe, 2 prostoe";
    QTest::newRow("Prime 0 and 1") << "0" << "1" << 2
                                   << "0 ne prostoe, 1 ne prostoe";

    QTest::newRow("Armstrong 370 and 371") << "370" << "371" << 3
                                           << "370 chislo armstronga, 371 ne chislo armstronga";
    QTest::newRow("Armstrong 407 and 408") << "407" << "408" << 3
                                           << "407 chislo armstronga, 408 ne chislo armstronga";
    QTest::newRow("Armstrong 0 and 1") << "0" << "1" << 3
                                       << "0 chislo armstronga, 1 chislo armstronga";
}

void testicui::testOperations()
{
    QFETCH(QString, input1);
    QFETCH(QString, input2);
    QFETCH(int, operation);
    QFETCH(QString, expected);

    m_window->ui->in1->setText(input1);
    m_window->ui->in2->setText(input2);
    m_window->ui->oper->setCurrentIndex(operation);
    m_window->x = operation;

    QTest::mouseClick(m_window->ui->res, Qt::LeftButton);

    QCOMPARE(m_window->ui->out->text(), expected);
}

QTEST_MAIN(testicui)
//#include "testicui.moc"
