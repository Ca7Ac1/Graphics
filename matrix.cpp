#include <iostream>
#include <cmath>

#include "matrix.hpp"

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

void Point::normalize()
{
    double m = sqrt(x * x + y * y + z * z);
    set(x / m, y / m, z / m);
}

Point Point::operator+(const Point &p) const
{
    return Point(x + p.getX(), y + p.getY(), z + p.getZ());
}

Point Point::operator-(const Point &p) const
{
    return Point(x - p.getX(), y - p.getY(), z - p.getZ());
}

Point Point::operator+(double v) const
{
    return Point(x + v, y + v, z + v);
}

Point Point::operator-(double v) const
{
    return Point(x - v, y - v, z - v);
}

Point Point::operator*(double v) const
{
    return Point(x * v, y * v, z * v);
}

Point Point::operator/(double v) const
{
    return Point(x / v, y / v, z / v);
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
        throw std::runtime_error("Wrong index for point");
    }
}

double Point::operator[](int i) const
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
        throw std::runtime_error("Wrong index for point");
    }
}

bool Point::operator==(const Point &p) const
{
    return x == p.getX() &&
           y == p.getY() &&
           z == p.getZ();
}

Point crossProduct(Point a, Point b)
{
    return Point(
        a.getY() * b.getZ() - a.getZ() * b.getY(),
        a.getZ() * b.getX() - a.getX() * b.getZ(),
        a.getX() * b.getY() - a.getY() * b.getX());
}

double dotProduct(Point a, Point b)
{
    return a.getX() * b.getX() +
           a.getY() * b.getY() +
           a.getZ() * b.getZ();
}

bool cmprX(const Point &a, const Point &b)
{
    return a.getX() < b.getX();
}

bool cmprY(const Point &a, const Point &b)
{
    return a.getY() < b.getY();
}

bool cmprZ(const Point &a, const Point &b)
{
    return a.getZ() < b.getZ();
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
        throw std::runtime_error("Trying to multiply wrong sized matrix");
    }

    for (int i = 0; i < m.getSize(); i++)
    {
        double sums[] = {0.0, 0.0, 0.0, 0.0};

        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                sums[j] += matrix[k][j] * m[i][k];
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

Matrix &Matrix::operator=(const Matrix &m)
{
    if (&m == this)
    {
        return *this;
    }

    clear();

    for (int i = 0; i < m.getSize(); i++)
    {
        add(Point(m[i][0], m[i][1], m[i][2], m[i][3]));
    }

    return *this;
}
