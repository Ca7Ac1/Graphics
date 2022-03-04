#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>

#include "matrix.hpp"
#include "transform.hpp"

class Graphics
{
private:
    Matrix edges;

public:
    Graphics();

    void addEdge(Point p1, Point p2);
    void addEdge(double x1, double y1, double z1, double t1, double x2, double y2, double z2, double t2);
    void addEdge(double x1, double y1, double z1, double x2, double y2, double z2);
    void transform(Matrix &m);
    void transform(Transform &t);
    void printEdges();
    void clear();
    
    int getCount() const;

    const Point &operator[](int i) const;
};

#endif