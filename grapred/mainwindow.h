#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include <QFileDialog>

#include "paintscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void slotTimer();
    void resizeEvent(QResizeEvent *event) override;

    void on_rom_clicked();
    void on_squ_clicked();
    void on_tri_clicked();
    void on_col_clicked();
    void on_sav_clicked();
    void on_loa_clicked();
    void on_fillButton_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    PaintScene *scene;
    QTimer *timer;
    QColor currentColor;
};
#endif // MAINWINDOW_H
