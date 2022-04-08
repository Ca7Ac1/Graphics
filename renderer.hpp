#ifndef RENDERER_H
#define RENDERER_H

#include "window.hpp"
#include "context.hpp"
#include "transform.hpp"
#include "graphics.hpp"
#include "graphics3d.hpp"

class Renderer
{
private:
    Window &window;
    Context plane;

    int red;
    int green;
    int blue;

public:
    Renderer(Window &window);

    void setColor(int red, int green, int blue);

    void plot(int x, int y);
    void fill();
    void line(int x1, int y1, int x2, int y2);

    void draw(Graphics &g);
    void draw(Graphics3D &g3d, bool cullBackFaces = true);

    void addPlane();
    void deletePlane();
    void transformPlane(Transform &t);
};

#endif