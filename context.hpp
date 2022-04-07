#ifndef CONTEXT_H
#define CONTEXT_H

#include <stack>

#include "matrix.hpp"
#include "transform.hpp"

class Context
{
private:
    std::stack<Transform> coordinateSystem;

public:
    Context();

    void push();
    void pop();
    void reset();
    void addTransformation(Matrix &m);
    void addTransformation(Transform &t);

    void apply(Matrix &m);
};

#endif