#include <vector>
#include <float.h>
#include <exception>
#include <algorithm>
#include <ctime>
#include <stdlib.h>

#include "renderer.hpp"
#include "window.hpp"
#include "transform.hpp"
#include "graphics.hpp"
#include "graphics3d.hpp"

Renderer::Renderer(Window &window) : window(window),
                                     plane(),
                                     backfaceCullingEnabled(true),
                                     fillEnabled(true),
                                     zBufferEnabled(true),
                                     zBuffer(window.getXDimension(), std::vector<double>(window.getYDimension(), -DBL_MAX)),
                                     red(0),
                                     green(0),
                                     blue(0) {}

void Renderer::setColor(int red, int green, int blue)
{
    this->red = red;
    this->blue = blue;
    this->green = green;
}

void Renderer::enableBackFaceCulling()
{
    backfaceCullingEnabled = true;
}

void Renderer::disableBackFaceCulling()
{
    backfaceCullingEnabled = false;
}

void Renderer::enableZBuffer()
{
    zBufferEnabled = true;
    clearZBuffer();
}

void Renderer::disableZBuffer()
{
    zBufferEnabled = false;
    clearZBuffer();
}

void Renderer::clearZBuffer()
{
    zBuffer.clear();
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

void Renderer::plotColor(int x, int y, int z, int r, int g, int b)
{
    if (x >= 0 && x < window.getXDimension() && y >= 0 && y < window.getYDimension())
    {
        if (!zBufferEnabled || z > zBuffer[x][y])
        {
            zBuffer[x][y] = z;
            window[x][y].set(r, g, b);
        }
    }
}

void Renderer::fill()
{
    for (int x = 0; x < window.getXDimension(); x++)
    {
        for (int y = 0; y < window.getYDimension(); y++)
        {
            plot(x, y, -DBL_MAX);
        }
    }
}

void Renderer::line(int x1, int y1, int x2, int y2)
{
    line(x1, x2, 0.0, x2, y2, 0.0);
}

void Renderer::line(int x1, int y1, double z1, int x2, int y2, double z2)
{
    int origX = x1 < x2 ? x1 : x2;
    int origY = x1 < x2 ? y1 : y2;
    double origZ = x1 < x2 ? z1 : z2;

    int endX = x1 < x2 ? x2 : x1;
    int endY = x1 < x2 ? y2 : y1;
    double endZ = x1 < x2 ? z2 : z1;

    // y = mx + b
    // Ax + By + C = 0
    // delta(y)x + -delta(x)y + (y-intercept / delta(x))
    int A = 2 * (endY - origY);
    int B = 2 * (origX - endX);

    if (endY >= origY)
    {
        if (endX - origX > endY - origY)
        {
            double zStep = (endZ - origZ) / (endX - origX + 1); 
            int dist = A + (B / 2);

            while (origX <= endX)
            {
                plot(origX, origY, origZ);

                if (dist > 0)
                {
                    origY++;
                    dist += B;
                }

                origX++;
                dist += A;
                origZ += zStep;
            }
        }
        else
        {
            double zStep = (endZ - origZ) / (endY - origY + 1); 
            int dist = B + (A / 2);

            while (origY <= endY)
            {
                plot(origX, origY, origZ);

                if (dist < 0)
                {
                    origX++;
                    dist += A;
                }

                origY++;
                dist += B;
                origZ += zStep;
            }
        }
    }
    else
    {
        if (endX - origX > origY - endY)
        {
            double zStep = (endZ - origZ) / (endX - origX + 1); 
            int dist = A - (B / 2);

            while (origX <= endX)
            {
                plot(origX, origY, origZ);

                if (dist < 0)
                {
                    origY--;
                    dist -= B;
                }

                origX++;
                dist += A;
                origZ += zStep;
            }
        }
        else
        {
            double zStep = (endZ - origZ) / (origY - endY + 1); 
            int dist = -B + (A / 2);

            while (origY >= endY)
            {
                plot(origX, origY, origZ);

                if (dist > 0)
                {
                    origX++;
                    dist += A;
                }

                origY--;
                dist -= B;
                origZ += zStep;
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

    std::vector<Point> pts;
    pts.push_back(g[0]);
    pts.push_back(g[2]);
    pts.push_back(g[4]);
    std::sort(pts.begin(), pts.end(), cmprY);

    double x0 = pts[0].getX();
    double deltaX0 = (pts[2].getX() - pts[0].getX()) / (pts[2].getY() - pts[0].getY());
    double x1 = pts[0].getX();
    double deltaX1 = (pts[1].getX() - pts[0].getX()) / (pts[1].getY() - pts[0].getY());

    double z0 = pts[0].getZ();
    double deltaZ0 = (pts[2].getZ() - pts[0].getZ()) / (pts[2].getY() - pts[0].getY());
    double z1 = pts[0].getZ();
    double deltaZ1 = (pts[1].getZ() - pts[0].getZ()) / (pts[1].getY() - pts[0].getY());

    bool flip = false;

    int redTemp = rand();
    int greenTemp = rand();
    int blueTemp = rand();
    for (double y = pts[0].getY(); y <= pts[2].getY(); y++)
    {
        if (y >= pts[1].getY() && !flip)
        {
            x1 = pts[1].getX();
            deltaX1 = (pts[2].getX() - x1) / (pts[2].getY() - pts[1].getY());

            z1 = pts[1].getZ();
            deltaZ1 = (pts[2].getZ() - z1) / (pts[2].getY() - pts[1].getY());

            flip = true;
        }

        double startX = x0 < x1 ? x0 : x1;
        double endX = x0 < x1 ? x1 : x0;
        double startZ = z0 < z1 ? z0 : z1;
        for (double i = 0; i <= startX - endX; i++)
        {
            plotColor((int)(i + startX), (int)y, (int)(i + startZ), redTemp, greenTemp, blueTemp);
        }

        x0 += deltaX0;
        x1 += deltaX1;

        z0 += deltaZ0;
        z1 += deltaZ1;
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