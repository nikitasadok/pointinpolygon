#include "polygon.h"
#include "QVector"
#include "QLineF"
#include "QtMath"
#include <random>
#include <iostream>

std::random_device rd;  //Will be used to obtain a seed for the random number engine
std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()

Polygon::Polygon()
{

}

qreal Polygon::getXMin() {
    return xMin;
}

qreal Polygon::getXMax() {
    return xMax;
}

qreal Polygon::getYMin() {
    return yMin;
}

qreal Polygon::getYMax() {
    return yMax;
}


Polygon::Polygon(QVector<QLineF> sides, qreal xMin, qreal xMax, qreal yMin, qreal yMax) {
    this->sides = sides;
    this->xMin = xMin;
    this->xMax = xMax;
    this->yMin = yMin;
    this->yMax = yMax;
}

Polygon Polygon::generateRandomSimplePoly(qreal cX, qreal cY, qreal rad, qreal irreg, qreal spikes, int numVerts) {
    irreg = clip(irreg, 0, 1) * 2 * M_PI / numVerts;
    spikes = clip(spikes, 0, 1) * rad;

    QVector<qreal> angleSteps;
    auto lower = (2 * M_PI / numVerts) - irreg;
    auto upper = (2 * M_PI / numVerts) + irreg;
    qreal sum = 0;

    std::uniform_real_distribution<double> unif(lower,upper);

    for (auto i = 0; i < numVerts; i++) {
        auto tmp = unif(gen);
        std::cout << tmp << std::endl;
        angleSteps.push_back(tmp);
        sum += tmp;
    }

    auto k = sum / (2 * M_PI);
    for (auto i = 0; i < angleSteps.size(); i++) {
        angleSteps[i] = angleSteps[i] / k;
    }

    QVector<QPointF> points;

    std::uniform_real_distribution<double> unifAngle(0,2 * M_PI);
    std::normal_distribution<double> distribution(rad,spikes);

    qreal xMin = INT_FAST64_MAX;
    qreal xMax = -1;
    qreal yMin = INT_FAST64_MAX;
    qreal yMax = -1;

    auto angle = unifAngle(gen);
    for (auto i = 0; i < numVerts; i++) {
        auto r_i = clip(distribution(gen), 0, 2 * rad);
        auto x = cX + r_i * qCos(angle);
        if (x > xMax)
            xMax = x;
        if (x < xMin)
            xMin = x;

        auto y = cY + r_i * qSin(angle);
        if (y > yMax)
            yMax = y;
        if (y < yMin)
            yMin = y;

        points.push_back(QPointF(x,y));
        angle += angleSteps[i];
    }

    QVector<QLineF> sides;

    for (auto i = 0; i  < points.size(); i++) {
        auto side = QLineF(points[i], points[(i + 1) % points.size()]);
        sides.push_back(side);
    }

    return Polygon(sides, xMin, xMax, yMin, yMax);
}

double Polygon::clip(qreal x, qreal min, qreal max) {
    if (min > max) {
        return x;
    } else if (x < min) {
        return min;
    } else if (x > max) {
        return max;
    }
    return x;
}

QVector<QLineF> Polygon::getSides() {
    return sides;
}
