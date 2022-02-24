#include "graphics.hpp"

Point::Point(int x, int y, int z, int t) : x(x), y(x), z(z), t(t) {}

int Point::getX() const
{
    return x;
}

int Point::getY() const
{
    return y;
}

int Point::getZ() const
{
    return z;
}

int Point::getT() const
{
    return t;
}

void Point::set(int x, int y, int z, int t = 1)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->t = t;
}

Graphics::Graphics() : edges() {}

void Graphics::addEdge(Point p1, Point p2)
{
    edges.push_back(p1);
    edges.push_back(p2);
}

void Graphics::addEdge(int x1, int y1, int z1, int t1, int x2, int y2, int z2, int t2)
{
    Point p1(x1, y1, z1, t1);
    Point p2(x2, y2, z2, t2);

    addEdge(p1, p2);
}

void Graphics::addEdge(int x1, int y1, int z1, int x2, int y2, int z2)
{   
    addEdge(x1, y1, z1, 1, x2, y2, z2, 1);
}

int Graphics::getEdgeCount() const
{
    return edges.size() / 2;
}

const Point &Graphics::operator[](int i) const
{
    return edges[i];
}