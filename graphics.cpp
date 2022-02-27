#include <iostream>

#include "graphics.hpp"

Point::Point(double x, double y, double z, double t) : x(x), y(y), z(z), t(t) {}

double Point::getX() const
{
    return x;
}

double Point::getY() const
{
    return y;
}

double Point::getZ() const
{
    return z;
}

double Point::getT() const
{
    return t;
}

void Point::setX(double x)
{
    this->x = x;
}
void Point::setY(double y)
{
    this->y = y;
}
void Point::setZ(double z)
{
    this->z = z;
}
void Point::setT(double t)
{
    this->t = t;
}

void Point::set(double x, double y, double z, double t)
{
    setX(x);
    setY(y);
    setZ(z);
    setT(t);
}

double &Point::operator[](int i)
{
    switch (i)
    {
    case 0:
        return x;
    case 1:
        return y;
    case 2:
        return z;
    case 3:
        return t;
    default:
        throw std::exception("Wrong index for point");
    }
}

Matrix::Matrix() : matrix() {}

void Matrix::add(Point p)
{
    matrix.push_back(p);
}

void Matrix::clear()
{
    matrix.clear();
}

void Matrix::setIdentity()
{
    matrix.clear();

    for (int i = 0; i < 4; i++)
    {
        matrix.push_back(Point(0, 0, 0, 0));

        for (int j = 0; j < 4; j++)
        {
            if (i == j)
            {
                matrix[i][j] = 1;
            }
        }
    }
}

void Matrix::mult(Matrix &m)
{
    if (matrix.size() != 4)
    {
        throw std::exception("Trying to multiply wrong sized matrix");
    }

    for (int i = 0; i < matrix.size(); i++)
    {
        double sums[] = {0.0, 0.0, 0.0, 0.0};

        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                sums[j] = matrix[k][j] * m[i][j];
            }
        }

        m[i].set(sums[0], sums[1], sums[2], sums[3]);
    }
}

void Matrix::print()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < matrix.size(); j++)
        {
            std::cout << matrix[j][i] << " ";
        }

        std::cout << '\n';
    }
}

int Matrix::getSize() const
{
    return matrix.size();
}

const Point &Matrix::operator[](int i) const
{
    return matrix[i];
}

Point &Matrix::operator[](int i)
{
    return matrix[i];
}

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
