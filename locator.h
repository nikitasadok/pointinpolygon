#ifndef LOCATOR_H
#define LOCATOR_H
#include "shape.h"
#include <QHash>

struct Slab {
    int id;
    QLineF* start;
    QLineF* end;
};

struct SearchHelperEntry {
    QVector<QLineF> edges;
    QVector<QLineF> edgesAdd;
    QVector<QLineF> edgesDel;
};

class Locator
{
private:
    GeomShape* shape;
    QVector<QPointF> sortedPoints;
    QHash<int, SearchHelperEntry> searcher;
    QVector<SearchHelperEntry> entries;
    QVector<Slab> slubs;
    void construct_searcher();
    SearchHelperEntry fill_edges_data(const SearchHelperEntry& prev_entry, const Slab& cur);
    int findSlubId(const QPointF& p);
    bool liesBetween(const QPointF& p, const QLineF& l1, const QLineF& l2);
    bool liesAbove(const QPointF& p, const QLineF& l1, const QLineF& l2);
    bool liesUnder(const QPointF& p, const QLineF& l1, const QLineF& l2);
    bool liesLeftFrom(const QPointF& p, const QLineF& l);
    bool liesRightFrom(const QPointF& p, const QLineF& l);
public:
    Locator(GeomShape* shape);
    QVector<SearchHelperEntry> get_entries();
    void addPoint(const QPointF& p);
    GeomShape* get_shape();
    bool isInside(const QPointF& p);
};

#endif // LOCATOR_H
