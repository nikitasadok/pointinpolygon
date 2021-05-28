#ifndef POINTINPOLYGON_H
#define POINTINPOLYGON_H
#include "QPointF"
#include "QVector"
#include "polygon.h"

int direction(QPointF pi, QPointF pj, QPointF pk);

bool onSegment(QPointF pi, QPointF pj, QPointF pk);

bool segmentIntersect(QPointF p1, QPointF p2, QPointF p3, QPointF p4);

struct BoundingBox {
    qreal xmin;
    qreal xmax;
    qreal ymin;
    qreal ymax;
};

class PointInPolygon {
private:
    QVector<QPointF> points;
    Polygon polygon;
    BoundingBox bbox;
    bool inBoundingBox(QPointF point);
    bool inPolygon(QPointF point);

private:
    void calcBoundingBox();

public:
    PointInPolygon(Polygon poly, QVector<QPointF> points);
    void addPoint(QPointF point);
    QVector<QPointF> getPointsInside();
    PointInPolygon();
};

#endif // POINTINPOLYGON_H
