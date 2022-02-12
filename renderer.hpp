#ifndef RENDERER_H
#define RENDERER_H

#include "window.hpp"

class Renderer
{
private:
    Window &window;

    int red;
    int green;
    int blue;

public:
    Renderer(Window &window);

    void setColor(int red, int green, int blue);
    
    void plot(int x, int y);
    void fill();
    void line(int x1, int y1, int x2, int y2);
};

#endif