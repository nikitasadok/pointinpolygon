//
// Created by nikita on 13.05.21.
//

#ifndef POINTINPOLYGON_POINTINPOLYGON_H
#define POINTINPOLYGON_POINTINPOLYGON_H

#include <vector>
#include <limits>
#include <algorithm>
#include "pointinpolygon.h"
#include "QLineF"
#include "QSet"
#include "iostream"

inline uint qHash (const QPointF & key)
{
    return qHash (QPair<int,int>(key.x(), key.y()) );
}

PointInPolygon::PointInPolygon() {

}

PointInPolygon::PointInPolygon(Polygon poly, QVector<QPointF> points) {
    this->polygon = poly;
    this->points = points;
    calcBoundingBox();
}

bool PointInPolygon::inBoundingBox(QPointF point) {
        if (point.x() < bbox.xmin || point.x() > bbox.xmax || point.y() < bbox.ymin || point.y() > bbox.ymax) {
            return false;
        } else {
            return true;
        }
    }

    bool PointInPolygon::inPolygon(QPointF point) {
        if (!inBoundingBox(point)) {
            return false;
        }

        QSet<QPointF> intersectPoints;
        auto edges = this->polygon.getSides();

        QPointF outside(bbox.xmax + 1, point.y());
        int intersections = 0;
        for (int i = 0; i < edges.size(); ++i) {
            QPointF intPoint;
            auto l = QLineF(point, outside);
            if (l.intersects(edges[i], &intPoint) == 1 && !intersectPoints.contains(intPoint)) {
                intersections++;
                intersectPoints.insert(intPoint);
            }
        }
        return (intersections % 2 != 0);
    }

    void PointInPolygon::calcBoundingBox() {
        bbox.xmin = this->polygon.getXMin();
        bbox.xmax = this->polygon.getXMax();
        bbox.ymin = this->polygon.getYMin();
        bbox.ymax = this->polygon.getYMax();
    }

    void PointInPolygon::addPoint(QPointF point) {
        this->points.push_back(point);
    }

    QVector<QPointF> PointInPolygon::getPointsInside() {
        QVector<QPointF> result;
        for (auto i = 0; i < points.size(); i++) {
            if (inPolygon(points[i]))
                result.push_back(points[i]);
        }

        return result;
    }

#endif //POINTINPOLYGON_POINTINPOLYGON_H
