#ifndef PAINTINGAREA_H
#define PAINTINGAREA_H
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QTimer>
#include <QPainter>
#include <QString>
#include "locator.h"
#include "polygon.h"
#include "pointinpolygon.h"
#include "random"

// Расширяем класс QGraphicsView
class PaintingArea: public QGraphicsView
{
    Q_OBJECT
public:
    explicit PaintingArea(QWidget *parent = 0);
    void addPolygon(int num);
    void loadDataFromFile(QString filename);
    ~PaintingArea();

public slots:
    void mousePressEvent(QMouseEvent * e);


//protected:
//    void paintEvent(QPaintEvent *event);

signals:

private slots:
    void slotAlarmTimer();  /* слот для обработчика переполнения таймера
                             * в нём будет производиться перерисовка
                             * виджета
                             * */

private:
    QGraphicsScene      *scene;     // Объявляем сцену для отрисовки
    QGraphicsItemGroup  *group_1;   // Объявляем первую группу элементов
    QGraphicsItemGroup  *group_2;   // Объявляем вторую группу элементов
    Locator* locator;
    Polygon polygon;
    QVector<QPointF> points;
    QList<QGraphicsItem *> drawnLines;
    QList<QGraphicsItem *> drawnPoints;
    PointInPolygon pip;
    QTimer              *timer;

private:
    /* Перегружаем событие изменения размера окна,
     * чтобы перехватывать его
     * */
    void resizeEvent(QResizeEvent *event);
    /* Метод для удаления всех элементов
     * из группы элементов
     * */
    void deleteItemsFromGroup(QGraphicsItemGroup *group_1);
    void erasePolygon();
    void erasePoints();
    void addPoint(QPointF point, qreal rad, QPen pen);
public:
    void calculate();
    void addRandomPoints(int n);
    void clearPolygon();
    void clearPoints();
};
#endif // PAINTINGAREA_H
