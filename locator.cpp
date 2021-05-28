#include "locator.h"
#include <algorithm>
#include <iostream>
#include <QHash>

bool operator<(const QPointF& a, const QPointF& b) { return a.y() < b.y(); }

void Locator::construct_searcher() {
    QHash<int, SearchHelperEntry> searcher;
    QVector<SearchHelperEntry> entries;
    QVector <Slab> slabs;

    double maxX  = -1;
    this->sortedPoints = this->shape->get_points();
    for (auto p : this->sortedPoints) {
        if (p.x() > maxX)
            maxX = p.x();
    }
    // sort by Y
    qSort(sortedPoints);

    entries.push_back(SearchHelperEntry{});
    auto t = QLineF(0,sortedPoints[0].y(), maxX + 1, sortedPoints[0].y());
    auto tk = QLineF(0,0, maxX + 1, 0);
    slabs.push_back(Slab{1, &tk, &t});
    for (int i = 1; i < sortedPoints.length() - 1; ++i) {
        auto slStart = new QLineF(0, sortedPoints[i - 1].y(), maxX + 1, sortedPoints[i - 1].y());
        auto slEnd = new QLineF(0, sortedPoints[i].y(), maxX + 1, sortedPoints[i].y());
        Slab sl = Slab{i + 1, slStart, slEnd};
        slabs.push_back(sl);
        auto entry = fill_edges_data(entries[i - 1], sl);
        searcher[i+1] = entry;
        entries.push_back(entry);
    }

    entries.push_back(SearchHelperEntry{edgesDel: entries[entries.length() - 1].edges});
    auto t1 = QLineF(0,sortedPoints[sortedPoints.length() - 1].y(), maxX + 1, sortedPoints[sortedPoints.length() - 1].y());
    auto t1k  = QLineF(0, 1920, maxX + 1, 1920);
    slabs.push_back(Slab{slabs.length() + 1, &t1, &t1k});

    this->entries = entries;
    this->searcher = searcher;
    this->slubs = slabs;

    for (auto sl : this->slubs) {
        std::cout << "SLUBS" << std::endl;
        std::cout << "id: " << sl.id << " start: " << sl.start->y1() << " end: " << sl.end->y2() << std::endl;
    }
    std::cout << "aaaa: " << findSlubId(QPointF{1,26}) << std::endl;
}

bool Locator::isInside(const QPointF& p) {
    auto id = findSlubId(p);
    auto entry = this->searcher[id];

    int l = 0;
    int r = entry.edges.length();

    while (l <= r) {
        int m = (l + r) / 2;
        if (liesRightFrom(p, entry.edges[m])) {
            l = m + 1;
        } else if (liesLeftFrom(p, entry.edges[m])) {
            r = m - 1;
        } else {
            return slubs[m].id;
        }
    }

    return -1;
}

int Locator::findSlubId(const QPointF &p) {
    int l = 0;
    int r = this->entries.length();

    while (l <= r) {
        int m = (l + r) / 2;
        if (liesAbove(p, *slubs[m].start, *slubs[m].end)) {
            l = m + 1;
        } else if (liesUnder(p, *slubs[m].start, *slubs[m].end)) {
            r = m - 1;
        } else {
            return slubs[m].id;
        }
    }

    return -1;
}

bool Locator::liesBetween(const QPointF& p, const QLineF &l1, const QLineF &l2) {
    return (p.y() >= l1.y1() && p.y() <= l2.y1());
}

bool Locator::liesAbove(const QPointF &p, const QLineF &l1, const QLineF &l2) {
    return p.y() >= l1.y1() && p.y() >= l2.y1();
}

bool Locator::liesUnder(const QPointF& p, const QLineF &l1, const QLineF &l2) {
    return p.y() <= l1.y1() && p.y() <= l2.y1();
}

bool Locator::liesLeftFrom(const QPointF& p, const QLineF& l) {
     // return ((b.X - a.X)*(c.Y - a.Y) - (b.Y - a.Y)*(c.X - a.X)) > 0;
    return ((l.x2() - l.x1()) * (p.y() - l.y1()) - (l.y2() - l.y1() * (p.x() - l.x1()))) > 0;
}

bool Locator::liesRightFrom(const QPointF& p, const QLineF& l) {
     // return ((b.X - a.X)*(c.Y - a.Y) - (b.Y - a.Y)*(c.X - a.X)) > 0;
    return ((l.x2() - l.x1()) * (p.y() - l.y1()) - (l.y2() - l.y1() * (p.x() - l.x1()))) < 0;
}

SearchHelperEntry Locator::fill_edges_data(const SearchHelperEntry& prev_entry, const Slab& cur) {
    SearchHelperEntry entry;
    for (auto e : this->shape->get_edges()) {
        if (e.intersects(*cur.start, nullptr) && e.intersects(*cur.end, nullptr)) {
            entry.edges.push_back(e);
        }
    }

    for (auto e :entry.edges) {
        if (!prev_entry.edges.contains(e))
            entry.edgesAdd.push_back(e);
    }

    for (auto e : prev_entry.edges) {
        if (prev_entry.edges.contains(e) && !entry.edges.contains(e))
            entry.edgesDel.push_back(e);
    }

    return entry;
}

QVector<SearchHelperEntry> Locator::get_entries() {
    return this->entries;
}

GeomShape* Locator::get_shape() {
    return this->shape;
}

void Locator::addPoint(const QPointF &p) {
    this->sortedPoints.push_back(p);
}

Locator::Locator(GeomShape* s)
{
    this->shape = s;
    this->construct_searcher();
}
