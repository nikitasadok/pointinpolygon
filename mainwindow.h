#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <paintingarea.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pointsSlider_valueChanged(int value);

    void on_polygonSlider_valueChanged(int value);

private:
    Ui::MainWindow  *ui;
    PaintingArea   *myPicture;     // Наш кастомный виджет
};

#endif // MAINWINDOW_H
