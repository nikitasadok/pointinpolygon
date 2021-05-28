#include <iostream>
#include "drawer.h"
#include "ui_drawer.h"
#include "shape.h"
#include "locator.h"
#include <QLine>
#include <QGraphicsScene>
#include "polygon.h"

Drawer::Drawer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Drawer)
{
    ui->setupUi(this);
}

void Drawer::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    // scene = new QGraphicsScene(this);

    auto poly = Polygon::generateRandomSimplePoly(200, 200, 50, 0.5, 0.5, 10);

    std::cout << poly.getSides().size() << std::endl;


    // GeomShape* s = new GeomShape("D:/test.txt");
    auto edges = poly.getSides();
   //  auto points = s->get_points();

    painter.translate(this->rect().bottomLeft());
    painter.scale(1.0, -1.0);



    std::cout << edges.length() << std::endl;
//    for (auto p : points) {
//        QPen linepen(Qt::red);
//           linepen.setCapStyle(Qt::RoundCap);
//           linepen.setWidth(10);
//           painter.setRenderHint(QPainter::Antialiasing,true);
//           painter.setPen(linepen);
      // painter.drawPoint(p);
//    }

    for (auto e : edges) {
        QPen linepen(Qt::green);
           linepen.setCapStyle(Qt::RoundCap);
           linepen.setWidth(5);
           painter.setRenderHint(QPainter::Antialiasing,true);
           painter.setPen(linepen);
        painter.drawLine(e);
    }
}

Drawer::~Drawer()
{
    delete ui;
}

void Drawer::on_pushButton_clicked()
{
    repaint();
}

void Drawer::on_pushButton_2_clicked()
{

}
