#include <stack>

#include "context.hpp"
#include "transform.hpp"

Context::Context() : coordinateSystem()
{
    coordinateSystem.push(Transform());
}

void Context::push()
{
    Transform t = coordinateSystem.top();
    coordinateSystem.push(t);
}

void Context::pop()
{
    coordinateSystem.pop();
}

void Context::reset()
{
    coordinateSystem.top().reset();
}

void Context::addTransformation(Matrix &m)
{
    Transform top;
    top.addTransformation(m);
    top.addTransformation(coordinateSystem.top());

    coordinateSystem.top() = top;
}

void Context::addTransformation(Transform &t)
{
    Transform top;
    t.addTransformation(t);
    t.addTransformation(coordinateSystem.top());
    
    coordinateSystem.top() = t;

}

void Context::apply(Matrix &m)
{
    coordinateSystem.top().apply(m);
}