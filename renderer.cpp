#include <vector>
#include <float.h>
#include <exception>
#include <algorithm>
#include <ctime>
#include <float.h>

#include "renderer.hpp"
#include "window.hpp"
#include "matrix.hpp"
#include "transform.hpp"
#include "graphics.hpp"
#include "graphics3d.hpp"
#include "lighting.hpp"

Renderer::Renderer(Window &window) : window(window),
                                     plane(),
                                     backfaceCullingEnabled(true),
                                     fillEnabled(true),
                                     zBufferEnabled(true),
                                     flatShadingEnabled(true),
                                     gouraudShadingEnabled(false),
                                     phongShadingEnabled(false),
                                     zBuffer(window.getXDimension(), std::vector<double>(window.getYDimension(), -DBL_MAX)),
                                     red(0),
                                     green(0),
                                     blue(0),
                                     lighting() {}

void Renderer::setColor(int red, int green, int blue)
{
    this->red = red;
    this->blue = blue;
    this->green = green;

    lighting.setAmbientLight(red, green, blue);
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
    for (std::vector<double> &v : zBuffer)
    {
        for (double &depth : v)
        {
            depth = -DBL_MAX;
        }
    }
}

void Renderer::enableFill()
{
    fillEnabled = true;
}

void Renderer::disableFill()
{
    fillEnabled = false;
}

void Renderer::enableFlatShading()
{
    flatShadingEnabled = true;
    gouraudShadingEnabled = false;
    phongShadingEnabled = false;
}

void Renderer::enableGouraudShading()
{
    flatShadingEnabled = false;
    gouraudShadingEnabled = true;
    phongShadingEnabled = false;
}

void Renderer::enablePhongShading()
{
    flatShadingEnabled = false;
    gouraudShadingEnabled = false;
    phongShadingEnabled = true;
}

void Renderer::plot(int x, int y, double z)
{
    plotColor(x, y, z, red, green, blue);
}

void Renderer::plotColor(int x, int y, double z, int r, int g, int b)
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
    bool zBufferEnabled = this->zBufferEnabled;
    disableZBuffer();

    for (int x = 0; x < window.getXDimension(); x++)
    {
        for (int y = 0; y < window.getYDimension(); y++)
        {
            plot(x, y, -DBL_MAX);
        }
    }

    this->zBufferEnabled = zBufferEnabled;
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
            if (endX - origX == 0)
            {
                zStep = 0;
            }

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
            if (endY - origY == 0)
            {
                zStep = 0;
            }

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
            if (endX - origX == 0)
            {
                zStep = 0;
            }

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
            if (origY - endY == 0)
            {
                zStep = 0;
            }

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

bool Renderer::deletePlane()
{
    return plane.pop();
}

void Renderer::clearPlane()
{
    while (!plane.atEnd())
    {
        plane.pop();
    }

    plane.reset();
}

void Renderer::transformPlane(Transform &t)
{
    plane.addTransformation(t);
}

void Renderer::setAmbientLight()
{
    lighting.setAmbientLight(red, green, blue);
}

void Renderer::addPointLight(double x, double y, double z)
{
    lighting.addPointLight(Color(red, green, blue), Point(x, y, z));
}

void Renderer::clearLights()
{
    lighting.clear();
    lighting.setAmbientLight(1, 1, 1);
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

void Renderer::flat(Graphics &g, Color c)
{
    std::vector<Point> pts;
    pts.push_back(g[0]);
    pts.push_back(g[2]);
    pts.push_back(g[4]);
    std::sort(pts.begin(), pts.end(), cmprY);

    double x0 = pts[0].getX();
    double deltaX0 = (pts[2].getX() - pts[0].getX()) / (int)(pts[2].getY() - pts[0].getY() + 1);
    double x1 = pts[0].getX();
    double deltaX1 = (pts[1].getX() - pts[0].getX()) / (int)(pts[1].getY() - pts[0].getY() + 1);

    double z0 = pts[0].getZ();
    double deltaZ0 = (pts[2].getZ() - pts[0].getZ()) / (int)(pts[2].getY() - pts[0].getY() + 1);
    double z1 = pts[0].getZ();
    double deltaZ1 = (pts[1].getZ() - pts[0].getZ()) / (int)(pts[1].getY() - pts[0].getY() + 1);

    bool flip = false;
    for (int y = pts[0].getY(); y <= (int)pts[2].getY(); y++)
    {
        if (y >= (int)pts[1].getY() && !flip)
        {
            x1 = pts[1].getX();
            deltaX1 = (pts[2].getX() - x1) / (int)(pts[2].getY() - pts[1].getY() + 1);

            z1 = pts[1].getZ();
            deltaZ1 = (pts[2].getZ() - z1) / (int)(pts[2].getY() - pts[1].getY() + 1);

            flip = true;
        }

        double startX = x0 < x1 ? x0 : x1;
        double endX = x0 < x1 ? x1 : x0;

        double startZ = x0 < x1 ? z0 : z1;
        double endZ = x0 < x1 ? z1 : z0;

        double deltaZ = (endZ - startZ) / (endX - startX);

        if (endX - startX == 0)
        {
            deltaZ = 0;
        }

        for (int i = 0.0; i + (int)startX <= (int)endX; i++)
        {
            plotColor(i + startX, y, (i * deltaZ) + startZ, c.getRed(), c.getGreen(), c.getBlue());
        }

        x0 += deltaX0;
        x1 += deltaX1;

        z0 += deltaZ0;
        z1 += deltaZ1;
    }
}

void Renderer::gouraud(Graphics &g, Point kA, Point kD, Point kS, std::unordered_map<Point, Point> &normals)
{
    std::vector<Point> pts;
    pts.push_back(g[0]);
    pts.push_back(g[2]);
    pts.push_back(g[4]);
    std::sort(pts.begin(), pts.end(), cmprY);

    Color vertex0 = lighting.get(kA, kD, kS, normals[pts[0]]);
    Color vertex1 = lighting.get(kA, kD, kS, normals[pts[1]]);
    Color vertex2 = lighting.get(kA, kD, kS, normals[pts[2]]);

    Point c0(vertex0.getRed(), vertex0.getGreen(), vertex0.getBlue());
    Point deltaC0((vertex2.getRed() - vertex0.getRed()) / (int)(pts[2].getY() - pts[0].getY() + 1),
                  (vertex2.getGreen() - vertex0.getGreen()) / (int)(pts[2].getY() - pts[0].getY() + 1),
                  (vertex2.getBlue() - vertex0.getRed()) / (int)(pts[2].getY() - pts[0].getY() + 1));
    Point c1(vertex0.getRed(), vertex0.getGreen(), vertex0.getBlue());
    Point deltaC1((vertex1.getRed() - vertex0.getRed()) / (int)(pts[1].getY() - pts[0].getY() + 1),
                  (vertex1.getGreen() - vertex0.getGreen()) / (int)(pts[1].getY() - pts[0].getY() + 1),
                  (vertex1.getBlue() - vertex0.getRed()) / (int)(pts[1].getY() - pts[0].getY() + 1));

    double x0 = pts[0].getX();
    double deltaX0 = (pts[2].getX() - pts[0].getX()) / (int)(pts[2].getY() - pts[0].getY() + 1);
    double x1 = pts[0].getX();
    double deltaX1 = (pts[1].getX() - pts[0].getX()) / (int)(pts[1].getY() - pts[0].getY() + 1);

    double z0 = pts[0].getZ();
    double deltaZ0 = (pts[2].getZ() - pts[0].getZ()) / (int)(pts[2].getY() - pts[0].getY() + 1);
    double z1 = pts[0].getZ();
    double deltaZ1 = (pts[1].getZ() - pts[0].getZ()) / (int)(pts[1].getY() - pts[0].getY() + 1);

    bool flip = false;
    for (int y = pts[0].getY(); y <= (int)pts[2].getY(); y++)
    {
        if (y >= (int)pts[1].getY() && !flip)
        {
            c1.set(vertex1.getRed(), vertex1.getGreen(), vertex1.getBlue());
            deltaC1.set((vertex2.getRed() - vertex1.getRed()) / (int)(pts[2].getY() - pts[1].getY() + 1),
                        (vertex2.getGreen() - vertex1.getGreen()) / (int)(pts[2].getY() - pts[1].getY() + 1),
                        (vertex2.getBlue() - vertex1.getRed()) / (int)(pts[2].getY() - pts[1].getY() + 1));

            x1 = pts[1].getX();
            deltaX1 = (pts[2].getX() - x1) / (int)(pts[2].getY() - pts[1].getY() + 1);

            z1 = pts[1].getZ();
            deltaZ1 = (pts[2].getZ() - z1) / (int)(pts[2].getY() - pts[1].getY() + 1);

            flip = true;
        }

        Point startC = x0 < x1 ? c0 : c1;
        Point endC = x0 < x1 ? c1 : c0;

        double startX = x0 < x1 ? x0 : x1;
        double endX = x0 < x1 ? x1 : x0;

        double startZ = x0 < x1 ? z0 : z1;
        double endZ = x0 < x1 ? z1 : z0;

        Point deltaC = (endC - startC) / (endX - startX);
        double deltaZ = (endZ - startZ) / (endX - startX);

        if (endX - startX == 0)
        {
            deltaC.set(0, 0, 0);
            deltaZ = 0;
        }

        for (int i = 0.0; i + (int)startX <= (int)endX; i++)
        {
            Point currColor = (deltaC * i) + startC;
            Color c(currColor[0], currColor[1], currColor[2]);

            plotColor(i + startX, y, (i * deltaZ) + startZ, c.getRed(), c.getGreen(), c.getBlue());
        }

        x0 += deltaX0;
        x1 += deltaX1;

        z0 += deltaZ0;
        z1 += deltaZ1;
    }
}

std::unordered_map<Point, Point> &Renderer::calculateNormals(Graphics3D &g3d)
{
    std::unordered_map<Point, Point> *normals = new std::unordered_map<Point, Point>();

    for (int i = 0; i < g3d.getCount(); i++)
    {
        for (int j = 0; j < g3d[i].getCount(); j++)
        {
            Point vertex = g3d[i][j];
            Point normal = g3d.getNormal(i);
            // normal.normalize();

            if ((*normals).find(vertex) == (*normals).end())
            {
                (*normals)[vertex] = normal;
            }
            else
            {
                (*normals)[vertex] = (*normals)[vertex] + normal;
            }
        }
    }

    for (const auto &p : (*normals))
    {
        (*normals)[p.first].normalize();
    }

    return *normals;
}

void Renderer::draw(Graphics3D &g3d, bool applyContext)
{
    if (applyContext)
    {
        plane.apply(g3d);
    }
    
    std::unordered_map<Point, Point> &normals = calculateNormals(g3d);

    for (int i = 0; i < g3d.getCount(); i++)
    {
        // if (applyContext)
        // {
        //     plane.apply(g3d[i]);
        // }

        if (!backfaceCullingEnabled || g3d.drawFace(i))
        {
            if (fillEnabled)
            {
                if (flatShadingEnabled)
                {
                    flat(g3d[i], lighting.get(g3d.getAmbient(),
                                              g3d.getDiffuse(),
                                              g3d.getSpecular(),
                                              g3d.getNormal(i)));
                }
                else if (gouraudShadingEnabled)
                {
                    gouraud(g3d[i], g3d.getAmbient(), g3d.getDiffuse(), g3d.getSpecular(), normals);
                }
                else if (phongShadingEnabled)
                {
                    std::cout << "p shade" << std::endl;
                }
            }
            else
            {
                draw(g3d[i], false);
            }
        }
    }

    delete &normals;

    g3d.clear();
}