#ifndef GRAPHICS3D_H
#define GRAPHICS3D_H

#include <vector>
#include <unordered_map>

#include "window.hpp"
#include "matrix.hpp"
#include "graphics.hpp"
#include "transform.hpp"

class Graphics3D
{
private:
    std::vector<Graphics> polygons;
    
    Point ambient;
    Point diffuse;
    Point specular;

    std::vector<std::vector<Point>> *generateSphere(int x, int y, int z, int r, int steps, int turns);
    std::vector<std::vector<Point>> *generateTorus(int x, int y, int z, int r1, int r2, int steps, int turns);

    void addVertex();

public:
    Graphics3D();

    void addPolygon(Point p1, Point p2, Point p3);
    void addPolygon(double x1, double y1, double z1, double t1, double x2, double y2, double z2, double t2, double x3, double y3, double z3, double t3);
    void addPolygon(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3);

    Point getNormal(int i) const;
    bool drawFace(int i) const;

    void addBox(int x, int y, int z, int w, int h, int d);
    void addSphere(int x, int y, int z, int r, int steps = 30, int turns = 40);
    void addTorus(int x, int y, int z, int r1, int r2, int steps = 30, int turns = 40);

    void transform(Matrix &m);
    void transform(Transform &t);
    void printPolygons();
    void clear();

    int getCount() const;

    void setAmbient(double r, double g, double b);
    void setDiffuse(double r, double g, double b);
    void setSpecular(double r, double g, double b);

    Point getAmbient() const;
    Point getDiffuse() const;
    Point getSpecular() const;

    Graphics &operator[](int i);
};

#endif