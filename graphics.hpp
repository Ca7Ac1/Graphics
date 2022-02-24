#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>

class Point
{
private:
    int x;
    int y;
    int z;
    int t;

public:
    Point(int x, int y, int z, int t = 0);

    int getX() const;
    int getY() const;
    int getZ() const;
    int getT() const;

    void set(int x, int y, int z, int t = 1);
    int operator[](int i) const;
};

class Graphics
{
private:
    std::vector<Point> edges;

public:
    Graphics();

    void addEdge(Point p1, Point p2);
    void addEdge(int x1, int y1, int z1, int t1, int x2, int y2, int z2, int t2);
    void addEdge(int x1, int y1, int z1, int x2, int y2, int z2);

    int getEdgeCount() const;
    
    const Point &operator[](int i) const;
};

#endif