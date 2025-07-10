#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QRandomGenerator>
#include <QPainterPath>
#include <cmath>
#include <QLabel>
#include <QMovie>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800, 600);

    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &MainWindow::updateAnimation);

    //случайное начальное направление
    float angle = QRandomGenerator::global()->generateDouble() * 2 * M_PI;
    velocity = QPointF(cos(angle) * SPEED, sin(angle) * SPEED);

    trailPositions.reserve(TRAIL_LENGTH);

    jumpHeight = 0;
    jumpVelocity = JUMP_FORCE;
    label2_groundY = ui->label_2->y();
    label3_groundY = ui->label_3->y();

    QLabel *label_4 = new QLabel(this);
    QMovie *movie = new QMovie(":/new/prefix1/8gmI.gif");

    label_4->setMovie(movie);
    movie->start();

    label_4->setFixedSize(movie->frameRect().size());
    label_4->move(400 - label_4->width() / 2,
        300 - label_4->height() / 2 );
    label_4->lower();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    for(int i = 0; i < trailPositions.size() - 1; i++)
    {
        float ratio = float(i) / TRAIL_LENGTH;
        QColor trailColor = QColor::fromHsvF(ratio, 1.0, 1.0, 0.7 - ratio * 0.5);

        QPen pen(trailColor);
        pen.setWidth(100);
        pen.setCapStyle(Qt::RoundCap);
        painter.setPen(pen);

        painter.drawLine(trailPositions[i], trailPositions[i+1]);
    }
}

void MainWindow::updateTrail()
{
    trailPositions.prepend(ui->label->geometry().center());

    if(trailPositions.size() > TRAIL_LENGTH)
        trailPositions.removeLast();
}

void MainWindow::updateAnimation()
{
    updateMainLabel();

    updateJumpingLabels();

    update();
}

void MainWindow::updateMainLabel()
{
    QRect labelRect = ui->label->geometry();
    QRect parentRect = ui->centralwidget->rect();

    QPoint newPos = labelRect.topLeft() + velocity.toPoint();

    if(newPos.x() <= 0)
    {
        newPos.setX(0);
        velocity.setX(-velocity.x());
    }
    else if(newPos.x() >= parentRect.width() - labelRect.width())
    {
        newPos.setX(parentRect.width() - labelRect.width());
        velocity.setX(-velocity.x());
    }

    if(newPos.y() <= 0)
    {
        newPos.setY(0);
        velocity.setY(-velocity.y());
    }
    else if(newPos.y() >= parentRect.height() - labelRect.height())
    {
        newPos.setY(parentRect.height() - labelRect.height());
        velocity.setY(-velocity.y());
    }

    ui->label->move(newPos.x(), newPos.y());
    updateTrail();
}

void MainWindow::updateJumpingLabels()
{
    jumpVelocity += GRAVITY;
    jumpHeight += jumpVelocity;

    if (jumpHeight < -MAX_JUMP_HEIGHT)
    {
        jumpHeight = -MAX_JUMP_HEIGHT;
        jumpVelocity = 0;
    }

    if (jumpHeight > 0)
    {
        jumpHeight = 0;
        jumpVelocity = JUMP_FORCE * (0.8 + 0.4 * QRandomGenerator::global()->generateDouble());
    }

    ui->label_2->move(ui->label_2->x(), label2_groundY + jumpHeight);
    ui->label_3->move(ui->label_3->x(), label3_groundY + jumpHeight);
}

void MainWindow::on_knop_clicked()
{
    if(animationTimer->isActive())
    {
        animationTimer->stop();
        ui->knop->setText("run");
    } else
    {
        animationTimer->start(16); //~60 FPS
        ui->knop->setText("stop");

        jumpHeight = 0;
        jumpVelocity = JUMP_FORCE;

        ui->label_2->move(ui->label_2->x(), label2_groundY);
        ui->label_3->move(ui->label_3->x(), label3_groundY);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
