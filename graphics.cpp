#include <cmath>
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

void addCurve(Matrix x, Matrix y, Matrix z, int steps)
{
    double prevX = x[3];
    double prevY = y[3];
    double prevZ = z[3];

    double step = 1.0 / (double) steps;
    for (double t = step; t <= 1; t += step)
    {
        double currX = (t * t * t * x[0]) + (t * t * x[1]) + (t * x[2]) + x[3];
        double currY = (t * t * t * y[0]) + (t * t * y[1]) + (t * y[2]) + y[3];
        double currZ = (t * t * t * z[0]) + (t * t * z[1]) + (t * z[2]) + z[3];

        addEdge(prevX, prevY, prevZ, currX, currY, currZ);

        prevX = currX;
        prevY = currY;
        prevZ = currZ;
    }
}

void addBezierCurve(double x[4], double y[4], double z[4], int steps)
{
    Matrix xCoeficients;
    Matrix yCoeficients;
    Matrix zCoeficients;

    xCoeficients.add(Point(x[0], x[1], x[2], x[3]));
    yCoeficients.add(Point(y[0], y[1], y[2], y[3]));
    zCoeficients.add(Point(z[0], z[1], z[2], z[3]));

    Matrix bezier;
    bezier.setIdentity();

    bezier[0][0] = -1;
    bezier[0][1] = 3;
    bezier[0][2] = -3;
    bezier[0][3] = 1;
    bezier[1][0] = 3;
    bezier[1][1] = -6;
    bezier[1][2] = 3;
    bezier[1][3] = 0;
    bezier[2][0] = -3;
    bezier[2][1] = 3;
    bezier[2][2] = 0;
    bezier[2][3] = 0;
    bezier[3][0] = 1;
    bezier[3][1] = 0;
    bezier[3][2] = 0;
    bezier[3][3] = 0;

    bezier.mult(xCoeficients);
    bezier.mult(yCoeficients);
    bezier.mult(zCoeficients);

    addCurve(xCoeficients, yCoeficients, zCoeficients, steps);
}

void addBezierCurve(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, double x4, double y4, double z4, int steps)
{
    double x[4] = {x1, x2, x3, x4};
    double y[4] = {y1, y2, y3, y4};
    double z[4] = {z1, z2, z3, z4};

    addBezierCurve(x, y, z, steps);
}

void addHermiteCurve(double x1, double y1, double z1, double dx1, double dy1, double x2, double y2, double z2, double dx2, double dy2, int steps=100)
{
    Matrix xCoeficients;
    Matrix yCoeficients;
    Matrix yCoeficients;

    Matrix hermite;
    hermite.setIdentity();

    hermite[0][0] = 2;
    hermite[0][1] = -3;
    hermite[0][2] = 0;
    hermite[0][3] = 1;
    hermite[1][0] = -2;
    hermite[1][1] = 3;
    hermite[1][2] = 0;
    hermite[1][3] = 0;
    hermite[2][0] = 1;
    hermite[2][1] = -2;
    hermite[2][2] = 1;
    hermite[2][3] = 0;
    hermite[3][0] = 1;
    hermite[3][1] = -1;
    hermite[3][2] = 0;
    hermite[3][3] = 0;

    hermite.mult(xCoeficients);
    hermite.mult(yCoeficients);
    hermite.mult(zCoeficients);

    addCurve(xCoeficients, yCoeficients, zCoeficients, steps);
}

void addCircle(double cX, double cY, double cZ, double r, bool radians, int steps)
{
    double prevX = cX + (r * cos(0.0))
    double prevY = cY + (r * sin(0.0));

    double step = (2.0 * M_PI) / (double) steps;
    for (double t = step; t <= (2 * M_PI); t += step)
    {
        double currX = cX + (r * cos(t))
        double currY = cY + (r * sin(t));

        addEdge(prevX, prevY, z, currX, currY, z);

        prevX = currX;
        prevY = currY;
    }
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
