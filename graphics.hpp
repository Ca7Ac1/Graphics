#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>

#include "matrix.hpp"
#include "transform.hpp"

class Graphics
{
private:
    Matrix edges;
    
    void addCurve(Matrix x, Matrix y, Matrix z, int steps);

public:
    Graphics();

    void addEdge(Point p1, Point p2);
    void addEdge(double x1, double y1, double z1, double t1, double x2, double y2, double z2, double t2);
    void addEdge(double x1, double y1, double z1, double x2, double y2, double z2);
    void addBezierCurve(double x[4], double y[4], double z[4], int steps=100);
    void addBezierCurve(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, double x4, double y4, double z4, int steps=100);
    void addHermiteCurve(double x1, double y1, double z1, double dx1, double dy1, double x2, double y2, double z2, double dx2, double dy2, int steps=100);
    void addCircle(double cX, double cY, double cZ, double r, int steps=100);
    void transform(Matrix &m);
    void transform(Transform &t);
    void printEdges();
    void clear();
    
    int getCount() const;

    const Point &operator[](int i) const;
};

#endif