#include "dcel.h"

DCEL::DCEL()
{

}

void addVertexAt(Vertex* v, HalfEdge* h) {
    auto h1 = new HalfEdge();
    auto h2 = new HalfEdge();

    v->halfedge = h2;
    h1->twin = h2;
    h2->twin = h1;
    h1->target = &v->coords;
    h2->target = h->target;
    h1->face = h->face;
    h2->face = h->face;
    h1->next = h2;
    h2->next = h->next;
    h1->prev = h;
    h2->prev = h1;
    h->next = h1;
    h2->next->prev = h2;
}
