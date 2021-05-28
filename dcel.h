#ifndef DCEL_H
#define DCEL_H
#include <QVector>
#include <QPointF>

struct Face {

};

struct HalfEdge {
    QPointF* target;
    Face*   face;
    HalfEdge* twin;
    HalfEdge* next;
    HalfEdge* prev;
};

struct Vertex {
    QPointF coords;
    HalfEdge* halfedge;
};

class DCEL
{
private:
    QVector<QPointF> vertices;
    QVector<HalfEdge> halfedges;
    QVector<Face> faces;
public:
    void addVertexAt(Vertex* v, HalfEdge* h);
    DCEL();
};

#endif // DCEL_H
