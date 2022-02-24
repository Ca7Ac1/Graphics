#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>

class Point
{
private:
    double x;
    double y;
    double z;
    double t;

public:
    Point(double x, double y, double z, double t = 0);

    double getX() const;
    double getY() const;
    double getZ() const;
    double getT() const;

    void setX(double x);
    void setY(double y);
    void setZ(double z);
    void setT(double t);
    void set(double x, double y, double z, double t = 1);
    
    double &operator[](double i);
};

class Matrix
{
private:
    std::vector<Point> matrix;

public:
    Matrix();

    void add(Point p);
    void setIdentity();
    void print();
    void mult();

    int getSize() const;

    const Point &operator[](int i) const;
};

class Graphics
{
private:
    Matrix edges;

public:
    Graphics();

    void addEdge(Point p1, Point p2);
    void addEdge(double x1, double y1, double z1, double t1, double x2, double y2, double z2, double t2);
    void addEdge(double x1, double y1, double z1, double x2, double y2, double z2);
    void printEdges();

    int getEdgeCount() const;

    const Point &operator[](int i) const;
};

#endif