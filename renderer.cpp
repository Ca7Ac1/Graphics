#include "renderer.hpp"
#include "window.hpp"
#include "transform.hpp"
#include "graphics.hpp"
#include "graphics3d.hpp"

Renderer::Renderer(Window &window) : window(window),
                                     context(),
                                     red(0),
                                     green(0),
                                     blue(0) {}

void Renderer::setColor(int red, int green, int blue)
{
    this->red = red;
    this->blue = blue;
    this->green = green;
}

void Renderer::plot(int x, int y)
{
    if (x >= 0 & x < window.getXDimension() && y >= 0 & y < window.getYDimension())
    {
        window[x][y].set(red, green, blue);
    }
}

void Renderer::fill()
{
    for (int x = 0; x < window.getXDimension(); x++)
    {
        for (int y = 0; y < window.getYDimension(); y++)
        {
            plot(x, y);
        }
    }
}

void Renderer::line(int x1, int y1, int x2, int y2)
{
    int origX = x1 < x2 ? x1 : x2;
    int origY = x1 < x2 ? y1 : y2;

    int endX = x1 < x2 ? x2 : x1;
    int endY = x1 < x2 ? y2 : y1;

    // y = mx + b
    // Ax + By + C = 0
    // delta(y)x + -delta(x)y + (y-intercept / delta(x))
    int A = 2 * (endY - origY);
    int B = 2 * (origX - endX);

    if (endY >= origY)
    {
        if (endX - origX > endY - origY)
        {
            int dist = A + (B / 2);

            while (origX <= endX)
            {
                plot(origX, origY);

                if (dist > 0)
                {
                    origY++;
                    dist += B;
                }

                origX++;
                dist += A;
            }
        }
        else
        {
            int dist = B + (A / 2);

            while (origY <= endY)
            {
                plot(origX, origY);

                if (dist < 0)
                {
                    origX++;
                    dist += A;
                }

                origY++;
                dist += B;
            }
        }
    }
    else
    {
        if (endX - origX > origY - endY)
        {
            int dist = A - (B / 2);

            while (origX <= endX)
            {
                plot(origX, origY);

                if (dist < 0)
                {
                    origY--;
                    dist -= B;
                }

                origX++;
                dist += A;
            }
        }
        else
        {
            int dist = -B + (A / 2);

            while (origY >= endY)
            {
                plot(origX, origY);

                if (dist > 0)
                {
                    origX++;
                    dist += A;
                }

                origY--;
                dist -= B;
            }
        }
    }
}

void Renderer::addPlane()
{
    plane.push();
}

void Renderer::deletePlane()
{   
    plane.pop();
}

void Renderer::transformPlane(Transform &t)
{
    plane.addTranformation(t);
}

void Renderer::draw(Graphics &g)
{
    context.apply(g);

    for (int i = 0; i < g.getCount(); i += 2)
    {
        line((int)g[i].getX(), (int)g[i].getY(),
             (int)g[i + 1].getX(), (int)g[i + 1].getY());
    }

    g.clear();
}

void Renderer::draw(Graphics3D &g3d, bool cullBackFaces)
{  
    for (int i = 0; i < g3d.getCount(); i++)
    {
        if (!cullBackFaces || g3d.drawFace(i))
        {
            draw(g3d[i]);
        }
    }

    g3d.clear();
}