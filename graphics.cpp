#include "graphics.hpp"
#include "matrix.hpp"
#include "transform.hpp"

Graphics::Graphics() : edges() {}

void Graphics::addEdge(Point p1, Point p2)
{
    edges.add(p1);
    edges.add(p2);
}

void Graphics::addEdge(double x1, double y1, double z1, double t1, double x2, double y2, double z2, double t2)
{
    Point p1(x1, y1, z1, t1);
    Point p2(x2, y2, z2, t2);

    addEdge(p1, p2);
}

void Graphics::addEdge(double x1, double y1, double z1, double x2, double y2, double z2)
{
    addEdge(x1, y1, z1, 1, x2, y2, z2, 1);
}

int Graphics::getCount() const
{
    return edges.getSize();
}

void Graphics::transform(Matrix &m)
{
    m.mult(edges);
}

void Graphics::transform(Transform &t)
{
    t.apply(edges);
}

void Graphics::printEdges()
{
    edges.print();
}

void Graphics::clear()
{
    edges.clear();
}

const Point &Graphics::operator[](int i) const
{
    return edges[i];
}
