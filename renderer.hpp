#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

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

    std::vector<std::vector<double>> zBuffer;
    
    bool zBufferEnabled;
    bool fillEnabled;
    bool backfaceCullingEnabled;
    
    int red;
    int green;
    int blue;

    void drawFilled(Graphics &g);

public:
    Renderer(Window &window);

    void setColor(int red, int green, int blue);

    void enableZBuffer();
    void disableZBuffer();

    void enableFill();
    void disableFill();

    void plot(int x, int y);
    void fill();
    void line(int x1, int y1, int x2, int y2);

    void draw(Graphics &g, bool applyContext = true);
    void draw(Graphics3D &g3d, bool applyContext = true);

    void addPlane();
    void deletePlane();
    void transformPlane(Transform &t);
};

#endif