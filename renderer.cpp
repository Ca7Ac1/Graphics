#include <vector>
#include <float.h>
#include <exception>
#include <algorithm>

#include "renderer.hpp"
#include "window.hpp"
#include "transform.hpp"
#include "graphics.hpp"
#include "graphics3d.hpp"

Renderer::Renderer(Window &window) : window(window),
                                     plane(),
                                     zBuffer(window.getXDimension(), std::vector<double>(window.getYDimension(), -DBL_MAX)),
                                     zBufferEnabled(false),
                                     fillEnabled(true),
                                     backfaceCullingEnabled(true),
                                     red(0),
                                     green(0),
                                     blue(0) {}

void Renderer::setColor(int red, int green, int blue)
{
    this->red = red;
    this->blue = blue;
    this->green = green;
}

void Renderer::enableZBuffer()
{
    zBufferEnabled = true;
}

void Renderer::disableZBuffer()
{
    zBufferEnabled = false;
}

void Renderer::enableFill()
{
    fillEnabled = true;
}

void Renderer::disableFill()
{
    fillEnabled = false;
}

void Renderer::plot(int x, int y, int z)
{
    plotColor(x, y, z, red, green, blue);
}

void Renderer::plotColor(int x, int y, int z, int red, int green, int blue)
{
    if (x >= 0 && x < window.getXDimension() && y >= 0 && y < window.getYDimension())
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
    plane.addTransformation(t);
}

void Renderer::draw(Graphics &g, bool applyContext)
{
    if (applyContext)
    {
        plane.apply(g);
    }

    for (int i = 0; i < g.getCount(); i += 2)
    {
        line((int)g[i].getX(), (int)g[i].getY(),
             (int)g[i + 1].getX(), (int)g[i + 1].getY());
    }

    g.clear();
}

void Renderer::drawFilled(Graphics &g)
{
    int cR = rand();
    int cG = rand();
    int cB = rand();

    if (g.getCount() != 6)
    {
        throw "Trying to draw bad matrix";
    }

    Point pts[] = {g[0], g[2], g[4]};
    std::sort(pts, pts + 3, cmprY);

    double x0 = pts[0].getX();
    double deltaX0 = (pts[2].getX() - pts[0].getX()) / (pts[2].getY() - pts[0].getY());
    double x1 = pts[0].getX();
    double deltaX1 = (pts[1].getX() - pts[0].getX()) / (pts[1].getY() - pts[0].getY());

    bool flip = false;
    for (double y = pts[0].getY(); y <= pts[2].getY(); y++)
    {
        if (y >= pts[1].getY() && !flip)
        {
            x1 = pts[1].getX();
            deltaX1 = (pts[2].getX() - x1) / (pts[2].getY() - pts[0].getY());
            
            flip = true;
        }

        double left = x0 < x1 ? x0 : x1;
        double right = x0 < x1 ? x1 : x0;
        for (double i = left; i <= right; i++)
        {
            plotColor((int)i, (int)y, 0, cR, cG, cB);
        }

        x0 += deltaX0;
        x1 += deltaX1;
    }
}

void Renderer::draw(Graphics3D &g3d, bool applyContext)
{
    for (int i = 0; i < g3d.getCount(); i++)
    {
        if (applyContext)
        {
            plane.apply(g3d[i]);
        }

        if (!backfaceCullingEnabled || g3d.drawFace(i))
        {
            if (fillEnabled)
            {
                drawFilled(g3d[i]);
            }
            else
            {
                draw(g3d[i], false);
            }
        }
    }

    g3d.clear();
}