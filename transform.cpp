#include <cmath>

#include "transform.hpp"
#include "graphics.hpp"

Transform::Transform() : transformation(), radians(false)
{
    reset();
}

void Transform::reset()
{
    transformation.setIdentity();
}

void Transform::addTransformation(Transform &t)
{
    t.transformation.mult(transformation);
}

void Transform::addTranslation(double x, double y, double z)
{
    Matrix translation;
    translation.setIdentity();

    translation[3][0] = x;
    translation[3][1] = y;
    translation[3][2] = z;

    translation.mult(transformation);
}

void Transform::addDilation(double x, double y, double z)
{
    Matrix dilation;
    dilation.setIdentity();

    dilation[0][0] = x;
    dilation[1][1] = y;
    dilation[2][2] = z;

    dilation.mult(transformation);
}

void Transform::addRotation(double angle, Axis axis)
{
    Matrix rotation;
    rotation.setIdentity();

    if (!radians)
    {
        angle = (angle / 360.0) * 2.0 * M_PI;
    }

    switch (axis)
    {
    case Axis::X:
        rotation[1][1] = cos(angle);
        rotation[2][1] = -sin(angle);
        rotation[1][2] = sin(angle);
        rotation[2][2] = cos(angle);

        break;
 
    case Axis::Y:
        rotation[3][2] = cos(angle);
        rotation[0][2] = -sin(angle);
        rotation[3][0] = sin(angle);
        rotation[0][0] = cos(angle);

        break;

    case Axis::Z:
        rotation[0][0] = cos(angle);
        rotation[1][0] = -sin(angle);
        rotation[0][1] = sin(angle);
        rotation[1][1] = cos(angle);

        break;
    }

    rotation.mult(transformation);
}

void Transform::setRadiansMode()
{
    radians = true;
}

void Transform::setDegreesMode()
{
    radians = false;
}

void Transform::apply(Matrix &m)
{
    transformation.mult(m);
}