#ifndef POLYGON_H
#define POLYGON_H
#include "QVector"
#include "QLineF"

class Polygon
{
private:
    QVector<QLineF> sides;
    QVector<QPointF> points;
    qreal xMin;
    qreal xMax;
    qreal yMin;
    qreal yMax;
    static double clip(qreal x, qreal min, qreal max);
public:
    QVector<QLineF> getSides();
public:
    Polygon();
    Polygon(QVector<QLineF> sides, qreal xMin, qreal xMax, qreal yMin, qreal yMax);
    static Polygon generateRandomSimplePoly(qreal cX, qreal cY, qreal rad, qreal irreg, qreal spikes, int numVerts);
    qreal getXMin();
    qreal getXMax();
    qreal getYMin();
    qreal getYMax();
};

#endif // POLYGON_H
