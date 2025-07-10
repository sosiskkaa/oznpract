#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "comp.h"
#include <QMainWindow>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_incomp_clicked();

    void on_inbag_clicked();

    void on_unicomp_clicked();

    void on_unibag_clicked();

    void on_search_clicked();

private:
    Ui::MainWindow *ui;

    COMP<Comp> *co1;
    COMP<Bag> *ba1;
    COMP<Comp> *co2;
    COMP<Bag> *ba2;

    QStandardItemModel *comp1Model;
    QStandardItemModel *comp2Model;
    QStandardItemModel *outCompModel;
    QStandardItemModel *bag1Model;
    QStandardItemModel *bag2Model;
    QStandardItemModel *outBagModel;
    QStandardItemModel *searchModel;

    void setupModels();
    void fillCompModel(QStandardItemModel* model, const COMP<Comp>& x);
    void fillBagModel(QStandardItemModel* model, const COMP<Bag>& x);
};
#endif // MAINWINDOW_H
