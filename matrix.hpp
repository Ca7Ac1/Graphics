#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class Point
{
private:
    double x;
    double y;
    double z;
    double t;

public:
    Point(double x, double y, double z, double t = 1);

    double getX() const;
    double getY() const;
    double getZ() const;
    double getT() const;

    void setX(double x);
    void setY(double y);
    void setZ(double z);
    void setT(double t);
    void set(double x, double y, double z, double t = 1);

    void normalize();
    
    Point operator+(const Point &p) const;
    Point operator-(const Point &p) const;

    Point operator+(double v) const;
    Point operator-(double v) const;
    Point operator*(double v) const;
    
    double &operator[](int i);
    double operator[](int i) const;
};

bool cmprX(const Point &a, const Point &b);
bool cmprY(const Point &a, const Point &b);
bool cmprZ(const Point &a, const Point &b);

class Matrix
{
private:
    std::vector<Point> matrix;

public:
    Matrix();

    void add(Point p);
    void clear();
    void setIdentity();
    void print();
    void mult(Matrix &m);

    int getSize() const;

    Point &operator[](int i);
    const Point &operator[](int i) const;
    Matrix &operator=(const Matrix &m);
};

Point crossProduct(Point a, Point b);
double dotProduct(Point a, Point b);

#endif