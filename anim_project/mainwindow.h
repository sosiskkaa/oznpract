#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QVector>
#include <QMainWindow>
#include <QTimer>
#include <QList>
#include <QPainter>
#include <QGraphicsEffect>
#include <QPainterPath>
#include <QRandomGenerator>


namespace Ui
{
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void on_knop_clicked();
    void updateAnimation();

private:
    Ui::MainWindow *ui;
    QTimer *animationTimer;
    QPointF velocity;
    QVector<QPoint> trailPositions;

    double jumpHeight;
    double jumpVelocity;
    const double JUMP_FORCE = -10;
    const double GRAVITY = 0.5;
    const int MAX_JUMP_HEIGHT = 150;
    int label2_groundY;
    int label3_groundY;

    const int TRAIL_LENGTH = 100;
    const float SPEED = 20.0f;

    void initEffects();
    void updateTrail();
    void updateMainLabel();
    void updateJumpingLabels();
};
#endif // MAINWINDOW_H
