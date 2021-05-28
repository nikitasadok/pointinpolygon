#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>

#include "shape.h"
QVector<QLineF> GeomShape::read_coordinates(QString filename) {
    QFile file(filename);
    QVector<QLineF> out;

    if (!file.open(QIODevice::ReadOnly)) {
        auto errMsg = file.errorString();
        std::cout << errMsg.toStdString() << std::endl;
        return out;
    }

    QTextStream in(&file);

    int numPoints = in.readLine().toInt();
    int readPoints = 0;

    while (readPoints < numPoints) {
        QString line = in.readLine();

        auto coordinates = line.split(", ");
        auto x = coordinates[0].toDouble();
        auto y = coordinates[1].toDouble();
        this->points.push_back(QPointF(x, y));
        readPoints++;
    }

    int numEdges = in.readLine().toInt();
    int readEdges = 0;

    while(readEdges < numEdges) {
        QString line = in.readLine();

        auto coordinates = line.split(" -> ");
        auto startCoords = coordinates[0];
        auto endCoords = coordinates[1];

        startCoords = startCoords.replace("(", "");
        startCoords = startCoords.replace(")", "");
        endCoords = endCoords.replace("(", "");
        endCoords = endCoords.replace(")", "");

        auto startX = startCoords.split(",")[0];
        auto startY = startCoords.split(",")[1];
        auto endX = endCoords.split(",")[0];
        auto endY = endCoords.split(",")[1];

        auto startPoint = QPointF{startX.toDouble(), startY.toDouble()};
        auto endPoint = QPointF{endX.toDouble(), endY.toDouble()};

        out.push_back(QLineF(startPoint, endPoint));
        readEdges++;
    }

    return out;
}

QVector<QPointF> GeomShape::get_points() {
    return this->points;
}

QVector<QLineF> GeomShape::get_edges() {
    return this->edges;
}

GeomShape::GeomShape(QString filename)
{
    this->edges = this->read_coordinates(filename);
}
