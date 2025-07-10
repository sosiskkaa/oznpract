#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    co1 = new COMP<Comp>;
    co2 = new COMP<Comp>;
    ba1 = new COMP<Bag>;
    ba2 = new COMP<Bag>;

    setupModels();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete co1;
    delete co2;
    delete ba1;
    delete ba2;
}

void MainWindow::setupModels()
{
    comp1Model = new QStandardItemModel(this);
    comp2Model = new QStandardItemModel(this);
    outCompModel = new QStandardItemModel(this);
    bag1Model = new QStandardItemModel(this);
    bag2Model = new QStandardItemModel(this);
    outBagModel = new QStandardItemModel(this);
    searchModel = new QStandardItemModel(this);

    QStringList compHeaders;
    compHeaders << "Name" << "Section" << "Price";
    comp1Model->setHorizontalHeaderLabels(compHeaders);
    comp2Model->setHorizontalHeaderLabels(compHeaders);
    outCompModel->setHorizontalHeaderLabels(compHeaders);

    QStringList bagHeaders;
    bagHeaders << "Name" << "Count" << "Section";
    bag1Model->setHorizontalHeaderLabels(bagHeaders);
    bag2Model->setHorizontalHeaderLabels(bagHeaders);
    outBagModel->setHorizontalHeaderLabels(bagHeaders);
    searchModel->setHorizontalHeaderLabels(bagHeaders);

    ui->incomp1->setModel(comp1Model);
    ui->incomp2->setModel(comp2Model);
    ui->outcomp->setModel(outCompModel);
    ui->inbag1->setModel(bag1Model);
    ui->inbag2->setModel(bag2Model);
    ui->outbag->setModel(outBagModel);
    ui->ressearch->setModel(searchModel);

    ui->incomp1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->incomp2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->outcomp->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->inbag1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->inbag2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->outbag->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->ressearch->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::fillCompModel(QStandardItemModel* model, const COMP<Comp>& x)
{
    model->removeRows(0, model->rowCount());

    for (int i = 0; i < x.getcount(); ++i)
    {
        QList<QStandardItem*> rowItems;
        rowItems << new QStandardItem(x[i].name);
        rowItems << new QStandardItem(x[i].sect);
        rowItems << new QStandardItem(QString::number(x[i].price));

        model->appendRow(rowItems);
    }
}

void MainWindow::fillBagModel(QStandardItemModel* model, const COMP<Bag>& x)
{
    model->removeRows(0, model->rowCount());

    for (int i = 0; i < x.getcount(); ++i)
    {
        QList<QStandardItem*> rowItems;
        rowItems << new QStandardItem(x[i].name);
        rowItems << new QStandardItem(QString::number(x[i].count));
        rowItems << new QStandardItem(x[i].sect);

        model->appendRow(rowItems);
    }
}

void MainWindow::on_incomp_clicked()
{
    co1->getdata("compin1");
    fillCompModel(comp1Model, *co1);
    co2->getdata("compin2");
    fillCompModel(comp2Model, *co2);
}


void MainWindow::on_inbag_clicked()
{
    ba1->getdata("bagin1");
    fillBagModel(bag1Model, *ba1);
    ba2->getdata("bagin2");
    fillBagModel(bag2Model, *ba2);
}


void MainWindow::on_unicomp_clicked()
{
    COMP<Comp> res = *co1 + *co2;
    res.writedata("compout");
    if (res.getcount() == 0)
        QMessageBox::information(this, "oh net? vot blin((", "NYAMAAA!!!😨😨😨");
    else
        fillCompModel(outCompModel, res);
}

void MainWindow::on_unibag_clicked()
{
    COMP<Bag> res = *ba1 + *ba2;
    res.writedata("bagout");
    if (res.getcount() == 0)
        QMessageBox::information(this, "oh net? vot blin((", "NYAMAAA!!!😨😨😨");
    else
        fillBagModel(outBagModel, res);
}


void MainWindow::on_search_clicked()
{
    QString chto = ui->chto->text();
    QString gde = ui->gde->text();
    if(gde == "Comp1")
    {
        COMP<Comp> res = co1->search(chto);
        if (res.getcount() == 0)
            QMessageBox::information(this, "oh net? vot blin((", "TAKOGO TOVARA TUT NYAMAAA!!!😨😨😨");
        else
            fillCompModel(searchModel, res);
    }
    else if(gde == "Comp2")
    {
        COMP<Comp> res = co2->search(chto);
        if (res.getcount() == 0)
            QMessageBox::information(this, "oh net? vot blin((", "TAKOGO TOVARA TUT NYAMAAA!!!😨😨😨");
        else
            fillCompModel(searchModel, res);
    }
    else if(gde == "Comp")
    {
        COMP<Comp> co = *co1 + *co2;
        COMP<Comp> res = co.search(chto);
        if (res.getcount() == 0)
            QMessageBox::information(this, "oh net? vot blin((", "TAKOGO TOVARA TUT NYAMAAA!!!😨😨😨");
        else
            fillCompModel(searchModel, res);
    }
    else if(gde == "Bag1")
    {
        COMP<Bag> res = ba1->search(chto);
        if (res.getcount() == 0)
            QMessageBox::information(this, "oh net? vot blin((", "TAKOGO TOVARA TUT NYAMAAA!!!😨😨😨");
        else
            fillBagModel(searchModel, res);
    }
    else if(gde == "Bag2")
    {
        COMP<Bag> res = ba2->search(chto);
        if (res.getcount() == 0)
            QMessageBox::information(this, "oh net? vot blin((", "TAKOGO TOVARA TUT NYAMAAA!!!😨😨😨");
        else
            fillBagModel(searchModel, res);
    }
    else if(gde == "Bag")
    {
        COMP<Bag> ba = *ba1 + *ba2;
        COMP<Bag> res = ba.search(chto);
        if (res.getcount() == 0)
            QMessageBox::information(this, "oh net? vot blin((", "TAKOGO TOVARA TUT NYAMAAA!!!😨😨😨");
        else
            fillBagModel(searchModel, res);
    }
    else
        QMessageBox::information(this, "oh net!!", "TAKOGO MASSIVA NYAMAAA!!!😨😨😨");
}

