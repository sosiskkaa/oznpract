#ifndef CHISLUI_H
#define CHISLUI_H
//SOURCES += moc_chislui.cpp
#include <QMainWindow>
#include <QWidget>
#include "chisl.h"
#include "ui_chislui.h"

class chislui : public QMainWindow
{
    Q_OBJECT
    friend class testicui;

public:
    chislui(QWidget *parent = nullptr) : QMainWindow(parent), ui(new Ui::chislui)
    {
        ui->setupUi(this);
    }
    ~chislui()
    {
        delete ui;
    }

private slots:
    void on_oper_activated(int index)
    {
        if(index == 0)
            x = 0;
        if(index == 1)
            x = 1;
        if(index == 2)
            x = 2;
        if(index == 3)
            x = 3;
    }

    void on_res_clicked()
    {
        QString qs1, qs2;
        qs1 = ui->in1->text();
        qs2 = ui->in2->text();
        int a = qs1.toInt();
        int b = qs2.toInt();
        chisl temp(a, b);

        if(x == 0)
        {
            int r1 = temp.nod();
            ui->out->setText(QString::number(r1));
        }
        if(x == 1)
        {
            int r1 = temp.nok();
            ui->out->setText(QString::number(r1));
        }
        if(x == 2)
        {
            int r1 = temp.prostx();
            int r2 = temp.prosty();

            QString q1, q2, re;
            if(r1 == 0)
                q1 = " ne prostoe, ";
            else
                q1 = " prostoe, ";
            if(r2 == 0)
                q2 = " ne prostoe";
            else
                q2 = " prostoe";
            re = QString::number(a) + q1 + QString::number(b) + q2;
            ui->out->setText(re);
        }
        if(x == 3)
        {
            bool b1 = temp.isarmstrongx();
            bool b2 = temp.isarmstrongy();

            QString q1, q2, re;
            if(b1 == 0)
                q1 = " ne chislo armstronga, ";
            else
                q1 = " chislo armstronga, ";
            if(b2 == 0)
                q2 = " ne chislo armstronga";
            else
                q2 = " chislo armstronga";
            re = QString::number(a) + q1 + QString::number(b) + q2;
            ui->out->setText(re);
        }

    }
private:
    Ui::chislui *ui;
    int x = 0;
};
#endif // CHISLUI_H
