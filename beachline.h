#ifndef BEACHLINE_H
#define BEACHLINE_H
#include "QPointF"
#include "dcel.h"
#include "event.h"

struct Arc {

};

class BeachLineItem {
    BeachLineItem* left;
    BeachLineItem* right;
};

struct BreakPoint {
    QPointF* p_i;
    QPointF* p_j;
};

class InnerNode : public BeachLineItem{
public:
    InnerNode(double x1, double x2, double y1, double y2) {
        auto p = QPointF(x1, y1);
        auto q = QPointF(x2, y2);
        auto bp = BreakPoint{&p, &q};
        breakpoint = &bp;
    }
    QPointF getBreakPoint() {
        return *breakpoint->p_i;
    };
private:
    BreakPoint* breakpoint;
    HalfEdge* halfedge;
};

class Leaf : public BeachLineItem{
private:
    BreakPoint* breakpoint;
    Event* event;
};

class BeachLine
{
    BeachLineItem* root = nullptr;
public:
    BeachLine();
    BeachLineItem* insert(BeachLineItem* item, BeachLineItem** toReplace);
};

#endif // BEACHLINE_H
