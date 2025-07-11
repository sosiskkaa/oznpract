#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->fillButton, &QPushButton::toggled, this, &MainWindow::on_fillButton_toggled);

    scene = new PaintScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::slotTimer);
    timer->start(100);

    currentColor = Qt::black;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotTimer()
{
    timer->stop();
    scene->setSceneRect(0,0, ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    timer->start(100);
    QMainWindow::resizeEvent(event);
}

void MainWindow::on_rom_clicked()
{
    scene->setTypeFigure(PaintScene::RombType);
}

void MainWindow::on_squ_clicked()
{
    scene->setTypeFigure(PaintScene::SquareType);
}

void MainWindow::on_tri_clicked()
{
    scene->setTypeFigure(PaintScene::TriangleType);
}

void MainWindow::on_col_clicked()
{
    QColor color = QColorDialog::getColor(currentColor, this, "Выберите цвет");
    if (color.isValid()) {
        currentColor = color;
        scene->setCurrentColor(color);
    }
}

void MainWindow::on_sav_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить сцену", "", "Текстовые файлы (*.txt)");
    if (!fileName.isEmpty()) {
        scene->saveToFile(fileName);
    }
}

void MainWindow::on_loa_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Загрузить сцену", "", "Текстовые файлы (*.txt)");
    if (!fileName.isEmpty()) {
        scene->loadFromFile(fileName);
    }
}

void MainWindow::on_fillButton_toggled(bool checked)
{
    scene->setFillMode(checked);
}
