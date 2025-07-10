#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QToolBar>
#include <QSpinBox>
#include <QSlider>
#include <QLabel>
#include <QActionGroup>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new PaintScene();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::slotTimer);
    timer->start(100);

    currentColor = Qt::black;

    QToolBar *toolBar = addToolBar(tr("Tools"));
    QActionGroup *toolActionGroup = new QActionGroup(this);

    QAction *penAction = new QAction(tr("Pen"), this);
    penAction->setCheckable(true);
    penAction->setChecked(true);
    connect(penAction, &QAction::triggered, this, &MainWindow::on_pen_clicked);
    toolBar->addAction(penAction);
    toolActionGroup->addAction(penAction);

    QAction *eraserAction = new QAction(tr("Eraser"), this);
    eraserAction->setCheckable(true);
    connect(eraserAction, &QAction::triggered, this, &MainWindow::on_eraser_clicked);
    toolBar->addAction(eraserAction);
    toolActionGroup->addAction(eraserAction);

    toolBar->addSeparator();

    QSpinBox *sizeSpinBox = new QSpinBox(this);
    sizeSpinBox->setRange(1, 50);
    sizeSpinBox->setValue(10);
    sizeSpinBox->setSuffix(" px");
    connect(sizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::on_penSize_valueChanged);
    toolBar->addWidget(sizeSpinBox);

    toolBar->addSeparator();

    QSlider *opacitySlider = new QSlider(Qt::Horizontal, this);
    opacitySlider->setRange(10, 100);
    opacitySlider->setValue(100);
    opacitySlider->setMaximumWidth(100);
    connect(opacitySlider, &QSlider::valueChanged,
            this, &MainWindow::on_opacitySlider_valueChanged);
    toolBar->addWidget(opacitySlider);
    toolBar->addWidget(new QLabel(tr("Opacity:"), this));
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

void MainWindow::on_pen_clicked()
{
    scene->setTypeFigure(PaintScene::LineType);
    scene->setEraser(false);
}

void MainWindow::on_eraser_clicked()
{
    scene->setTypeFigure(PaintScene::LineType);
    scene->setEraser(true);
}

void MainWindow::on_penSize_valueChanged(int size)
{
    scene->setPenSize(size);
}

void MainWindow::on_opacitySlider_valueChanged(int value)
{
    scene->setPenOpacity(value / 100.0);
}

void MainWindow::on_col_clicked()
{
    QColor color = QColorDialog::getColor(currentColor, this, "Выберите цвет");
    if (color.isValid())
    {
        currentColor = color;
        scene->setCurrentColor(color);
    }
}

void MainWindow::on_sav_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Сохранить сцену", "", "Текстовые файлы (*.txt)");
    if (!fileName.isEmpty())
    {
        scene->saveToFile(fileName);
    }
}

void MainWindow::on_loa_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Загрузить сцену", "", "Текстовые файлы (*.txt)");
    if (!fileName.isEmpty())
    {
        scene->loadFromFile(fileName);
    }
}
