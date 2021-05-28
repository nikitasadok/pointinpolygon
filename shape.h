#ifndef SHAPE_H
#define SHAPE_H

#include <QVector>
#include <QPair>
#include <QPoint>
#include <QLineF>

struct Point {
    double x;
    double y;
};

struct Edge {
    QPointF* start;
    QPointF* end;
};

class GeomShape
{
private:
    QVector<QPointF> points;
    QVector<QLineF> edges;
    QVector<QLineF> read_coordinates(QString filename);
public:
    QVector<QPointF> get_points();
    QVector<QLineF> get_edges();
    GeomShape(QString filename);
};

#endif // SHAPE_H
