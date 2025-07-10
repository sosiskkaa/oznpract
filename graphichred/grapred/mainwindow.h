#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QResizeEvent>
#include <QColorDialog>
#include <QFileDialog>

#include "paintscene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    PaintScene *scene;
    QTimer *timer;
    QColor currentColor;

    void resizeEvent(QResizeEvent *event);

private slots:
    void slotTimer();
    void on_rom_clicked();
    void on_squ_clicked();
    void on_tri_clicked();
    void on_col_clicked();
    void on_sav_clicked();
    void on_loa_clicked();
};

#endif // MAINWINDOW_H
