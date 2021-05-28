#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paintingarea.h"
#include "shape.h"
#include "locator.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myPicture = new PaintingArea();
    ui->graphicLayout->addWidget(myPicture);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    auto numVerts = ui->polygonSlider->value();
    myPicture->addPolygon(numVerts);
}

void MainWindow::on_pushButton_2_clicked()
{
    myPicture->calculate();
}

void MainWindow::on_pushButton_3_clicked()
{
    auto numPoints = ui->pointsSlider->value();
    std::cout << "n: " << numPoints << std::endl;
    myPicture->addRandomPoints(numPoints);
}

void MainWindow::on_pushButton_4_clicked()
{
    myPicture->clearPoints();
    myPicture->clearPolygon();
}

void MainWindow::on_pointsSlider_valueChanged(int value)
{
    ui->pointsSliderValue->setText(QString::number(value));
}

void MainWindow::on_polygonSlider_valueChanged(int value)
{
    ui->polygonSliderValue->setText(QString::number(value));
}
