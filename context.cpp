#include <stack>

#include "context.hpp"
#include "transform.hpp"
#include "graphics.hpp"
#include "graphics3d.hpp"

Context::Context() : coordinateSystem()
{
    coordinateSystem.push(Transform());
}

void Context::push()
{
    Transform t = coordinateSystem.top();
    coordinateSystem.push(t);
}

bool Context::pop()
{
    if (!atEnd())
    {
        coordinateSystem.pop();
        return true;
    }

    return false;
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
    top.addTransformation(t);
    top.addTransformation(coordinateSystem.top());
    
    coordinateSystem.top() = top;

}

bool Context::atEnd()
{
    return coordinateSystem.size() == 1;
}

void Context::apply(Graphics &g)
{
    g.transform(coordinateSystem.top());
}

void Context::apply(Graphics3D &g3d)
{
    g3d.transform(coordinateSystem.top());
}