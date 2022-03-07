#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "matrix.hpp"

enum Axis { X, Y, Z };

class Transform
{
private:
    Matrix transformation;

public:
    Transform();

    void reset();
    void addTransformation(Matrix &m);
    void addTransformation(Transform &t);
    void addTranslation(double x, double y, double z);
    void addDilation(double x, double y, double z);
    void addRotation(double angle, Axis axis, bool degrees=false);

    void apply(Matrix &m);
};

#endif