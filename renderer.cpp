#include "renderer.hpp"
#include "window.hpp"

Renderer::Renderer(Window &window) : window(window),
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
    window[x][y].set(red, green, blue);
}
