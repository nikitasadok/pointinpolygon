#include <iostream>
#include "paintingarea.h"
#include "shape.h"
#include "locator.h"
#include <QMouseEvent>
#include <random>

inline uint qHash (const QPointF & key)
{
    return qHash (QPair<int,int>(qRound(key.x()), qRound(key.y())) );
}


std::random_device rd_paint;  //Will be used to obtain a seed for the random number engine
std::mt19937 gen_paint(rd_paint()); //Standard mersenne_twister_engine seeded with rd()

PaintingArea::PaintingArea(QWidget *parent)
    : QGraphicsView(parent)
{

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключим скроллбар по горизонтали
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // Отключим скроллбар по вертикали
    this->setAlignment(Qt::AlignCenter);                        // Делаем привязку содержимого к центру
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);    // Растягиваем содержимое по виджету

    this->setMinimumHeight(100);
    this->setMinimumWidth(100);

    scene = new QGraphicsScene();
    this->setScene(scene);

    group_1 = new QGraphicsItemGroup();
    group_2 = new QGraphicsItemGroup();

    this->scale(1,-1);

//     auto poly = Polygon::generateRandomSimplePoly(200, 200, 50, 0.5, 0.5, 15);


    timer = new QTimer();               // Инициализируем Таймер
    timer->setSingleShot(true);
    // Подключаем СЛОТ для отрисовки к таймеру
    connect(timer, SIGNAL(timeout()), this, SLOT(slotAlarmTimer()));
    timer->start(50);
}

PaintingArea::~PaintingArea()
{

}

void PaintingArea::mousePressEvent(QMouseEvent * e)
{
        QPointF pt = mapToScene(e->pos());
        this->points.push_back(pt);
        addPoint(pt, 1, QPen(Qt::black));
}

void PaintingArea::loadDataFromFile(QString filename) {
    GeomShape* s = new GeomShape(filename);
    this->locator = new Locator(s);
}

void PaintingArea::addPolygon(int num) {
     std::uniform_real_distribution<qreal> pars_generator(0,1);
     std::uniform_real_distribution<qreal> rad_generator(50,250);
     auto cX = this->scene->width() / 2;
     auto cY = this->scene->height() / 2;
     auto rad = rad_generator(gen_paint);
     this->erasePolygon();
     this->polygon = Polygon::generateRandomSimplePoly(cX, cY, rad, pars_generator(gen_paint), pars_generator(gen_paint), num);
     auto edges = this->polygon.getSides();


     std::cout << edges.length() << std::endl;

     for (auto e : edges) {
         QPen linepen(Qt::green);
         linepen.setCapStyle(Qt::RoundCap);
         linepen.setWidth(5);
         drawnLines << this->scene->addLine(e);
     }
}

void PaintingArea::erasePolygon() {
    int iNum = drawnLines.count();
        for (int i=0; i<iNum; i++)
            delete drawnLines.takeAt(0);
}

void PaintingArea::slotAlarmTimer()
{
    this->deleteItemsFromGroup(group_1);
    this->deleteItemsFromGroup(group_2);

    int width = this->width();
    int height = this->height();

    scene->setSceneRect(0,0,width,height);

    QPen penBlack(Qt::black);
    QPen penRed(Qt::red);

    group_1->addToGroup(scene->addLine(20,20, width - 20, 20, penBlack));
    group_1->addToGroup(scene->addLine(width - 20, 20, width - 20, height -20, penBlack));
    group_1->addToGroup(scene->addLine(width - 20, height -20, 20, height -20, penBlack));
    group_1->addToGroup(scene->addLine(20, height -20, 20, 20, penBlack));

    int sideOfSquare = (height > width) ? (width - 60) : (height - 60);
    int centerOfWidget_X = width/2;
    int centerOfWidget_Y = height/2;

    group_2->addToGroup(scene->addLine(centerOfWidget_X - (sideOfSquare/2),
                                       centerOfWidget_Y - (sideOfSquare/2),
                                       centerOfWidget_X + (sideOfSquare/2),
                                       centerOfWidget_Y - (sideOfSquare/2),
                                       penRed));

    group_2->addToGroup(scene->addLine(centerOfWidget_X + (sideOfSquare/2),
                                       centerOfWidget_Y - (sideOfSquare/2),
                                       centerOfWidget_X + (sideOfSquare/2),
                                       centerOfWidget_Y + (sideOfSquare/2),
                                       penRed));

    group_2->addToGroup(scene->addLine(centerOfWidget_X + (sideOfSquare/2),
                                       centerOfWidget_Y + (sideOfSquare/2),
                                       centerOfWidget_X - (sideOfSquare/2),
                                       centerOfWidget_Y + (sideOfSquare/2),
                                       penRed));

    group_2->addToGroup(scene->addLine(centerOfWidget_X - (sideOfSquare/2),
                                       centerOfWidget_Y + (sideOfSquare/2),
                                       centerOfWidget_X - (sideOfSquare/2),
                                       centerOfWidget_Y - (sideOfSquare/2),
                                       penRed));
}

void PaintingArea::resizeEvent(QResizeEvent *event)
{
    timer->start(50);
    QGraphicsView::resizeEvent(event);
}

void PaintingArea::deleteItemsFromGroup(QGraphicsItemGroup *group)
{
    foreach( QGraphicsItem *item, scene->items(group->boundingRect())) {
       if(item->group() == group ) {
          delete item;
       }
    }
}

void PaintingArea::calculate() {
    this->pip = PointInPolygon(this->polygon, this->points);
    auto res = pip.getPointsInside();
    for (auto pt : res) {
        QPen penRed(Qt::red);
        addPoint(pt, 2, penRed);
    }
}

void PaintingArea::erasePoints() {
    int iNum = drawnPoints.count();
        for (int i=0; i<iNum; i++)
            delete drawnPoints.takeAt(0);
}

void PaintingArea::addRandomPoints(int n) {
    this->erasePoints();
    this->points.clear();
    auto xMax = this->scene->width();
    auto yMax = this->scene->height();

    QSet<QPointF> existingPoints;

    std::uniform_real_distribution<double> distributionXs(0, xMax);
    std::uniform_real_distribution<double> distributionYs(0, yMax);
//    for (auto i = 0; i < n; ++i) {
//        auto x = distributionXs(gen_paint);
//        auto y = distributionYs(gen_paint);
//        auto pt = QPointF(x, y);
//        this->points.push_back(pt);
//        addPoint(pt, 0.8, QPen(Qt::black));
//    }

    int i = 0;
    while (i < n) {
        auto x = distributionXs(gen_paint);
        auto y = distributionYs(gen_paint);
        auto pt = QPointF(x, y);
        if (!existingPoints.contains(pt)) {
            this->points.push_back(pt);
            i++;
            addPoint(pt, 0.8, QPen(Qt::black));
        }
    }
}

void PaintingArea::addPoint(QPointF pt, qreal rad, QPen pen) {
    drawnPoints << scene->addEllipse(pt.x()-rad, pt.y()-rad, rad*2.0, rad*2.0,
        pen, QBrush(Qt::SolidPattern));
}

void PaintingArea::clearPolygon() {
    erasePolygon();
    this->polygon = Polygon();
}
void PaintingArea::clearPoints() {
    erasePoints();
    this->points.clear();
}
