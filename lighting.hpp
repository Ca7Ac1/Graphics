#ifndef LIGHTING_H
#define LIGHTING_H

#include <vector>

#include "window.hpp"
#include "matrix.hpp"
#include "graphics3d.hpp"

class Lighting
{
private:
    Color ambient;

    int lights;
    std::vector<Point> vectors;
    std::vector<Color> colors;

public:
    Lighting();

    void setAmbientLight(int r, int g, int b);
    void addPointLight(Color c, Point v);

    void clear();

    Color get(const Graphics3D &g3d, int triangle);
};

#endif