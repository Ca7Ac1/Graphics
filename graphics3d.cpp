#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>

#include "graphics.hpp"
#include "graphics3d.hpp"
#include "matrix.hpp"
#include "transform.hpp"

Graphics::Graphics() : edges() {}

void Graphics3D::addPolygon(Point p1, Point p2, Point p3)
{
    polygons.push_back(Graphics());
    
    polygons[polygons.size() - 1].addEdge(p1, p2);
    polygons[polygons.size() - 1].addEdge(p2, p3);
    polygons[polygons.size() - 1].addEdge(p3, p1);
}

void Graphics3D::addPolygon(double x1, double y1, double z1, double t1, double x2, double y2, double z2, double t2, double x3, double y3, double z3, double t3)
{
    Point p1(x1, y1, z1, t1);
    Point p2(x2, y2, z2, t2);
    Point p3(x3, y3, z3, t3);

    addPolygon(p1, p2, p3);
}

void Graphics3D::addPolygon(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3)
{
    addPolygon(x1, y1, z1, 1, x2, y2, z2, 1, x3, y3, z3, 1);
}

std::vector<Point> *Graphics3D::generateSphere(int x, int y, int z, int r, int steps, int turns)
{
    std::vector<Point> *points = new std::vector<Point>();

    for (int i = 0; i < turns; i++)
    {
        for (int j = 0; j <= steps; j++)
        {
            double rot = i * 2.0 * M_PI / turns;
            double cir = j * M_PI / steps;

            points->push_back(Point(r * cos(cir) + x, 
                                   r * sin(cir) * cos(rot) + y, 
                                   r * sin(cir) * sin(rot) + z));
        }
    }

    return points;
}

std::vector<Point> *Graphics3D::generateTorus(int x, int y, int z, int r1, int r2, int steps, int turns)
{
    std::vector<Point> *points = new std::vector<Point>();

    for (int i = 0; i < turns; i++)
    {
        for (int j = 0; j < steps; j++)
        {
            double rot = i * 2.0 * M_PI / turns;
            double cir = j * 2.0 * M_PI / steps;

            points->push_back(Point(cos(rot) * (r1 * cos(cir) + r2) + x, 
                                   r1 * sin(cir) + y, 
                                   -sin(rot) * (r1 * cos(cir) + r2) + z));
        }
    }

    return points;
}

void Graphics3D::addBox(int x, int y, int z, int w, int h, int d)
{
    // Front
    addPolygon(x, y, z, x, y - h, z, x + w, y, z);
    addPolygon(x + w, y, z, x, y - h, z, x + w, y - h, z);

    // Back
    addPolygon(x, y, z - d, x + w, y, z - d, x, y - h, z - d);
    addPolygon(x + w, y, z - d, x + w, y - h, z - d, x, y - h, z - d);

    // Top
    addPolygon(x, y, z - d, x, y, z, x + w, y, z - d);
    addPolygon(x + w, y, z - d, x, y, z, x + w, y, z);

    // Bottom
    addPolygon(x, y - h, z - d, x + w, y - h, z - d, x, y - h, z);
    addPolygon(x + w, y - h, z - d, x + w, y - h, z, x, y - h, z);

    // Left
    addPolygon(x, y, z, x, y, z - d, x, y - h, z - d);
    addPolygon(x, y, z, x, y - h, z - d, x, y - h, z);

    // Right
    addPolygon(x + w, y, z, x + w, y - h, z - d, x + w, y, z - d);
    addPolygon(x + w, y, z, x + w, y - h, z, x + w, y - h, z - d);
}

void Graphics3D::addSphere(int x, int y, int z, int r, int steps, int turns)
{
    std::vector<Point> *points = generateSphere(x, y, z, r, steps, turns);
    int numPoints = points->size();

    for (int i = 0; i < numPoints; i++)
    {
        if (i % steps == 0)
        {
            continue;
        }

        addPolygon((*points)[i], (*points)[i + 1], (*points)[(i + 2 + steps) % numPoints]);

        if (i % (steps + 1) != 0)
        {
            addPolygon((*points)[i], (*points)[(i + 3 + steps) % numPoints], (*points)[(i + 2 + steps) % numPoints]);
        }
    }

    delete points;
}

void Graphics3D::addTorus(int x, int y, int z, int r1, int r2, int steps, int turns)
{
    std::vector<Point> *points = generateTorus(x, y, z, r1, r2, steps, turns);
    int numPoints = points->size();

    for (int i = 0; i < numPoints; i++)
    {
        if (i % steps == 0)
        {
            continue;
        }

        addPolygon((*points)[i], (*points)[(i + steps) % numPoints], (*points)[i + 1]);
        addPolygon((*points)[i + 1], (*points)[(i + steps) % numPoints], (*points)[(i + 1 + steps) % numPoints]);
    }

    delete points;
}


int Graphics3D::getCount() const
{
    return polygons.size();
}

void Graphics3D::transform(Matrix &m)
{
    for (Graphics &triangle : polygons)
    {
        triangle.transform(m);
    }
}

void Graphics3D::transform(Transform &t)
{
    for (Graphics &triangle : polygons)
    {
        triangle.transform(t);
    }
}

void Graphics3D::printPolygons()
{
    for (Graphics &triangle : polygons)
    {
        triangle.printEdges();
    }
}

void Graphics3D::clear()
{
    for (Graphics &triangle : polygons)
    {
        triangle.clear();
    }
}

const Graphics &Graphics3D::operator[](int i) const
{
    return polygons[i];
}
