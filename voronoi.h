#ifndef VORONOI_H
#define VORONOI_H
#include "QPointF"
#include <queue>
#include "event.h"
#include "beachline.h"


class Voronoi
{
    std::priority_queue<Event> eventQueue;
    BeachLine statusStructure;
public:
    Voronoi();
};

bool operator <(Event p, Event q) {
    return p.getPoint().y() < q.getPoint().y();
}

bool operator >(Event p, Event q) {
    return p.getPoint().y() > q.getPoint().y();
}

#endif // VORONOI_H
