#include <iostream>
#include <math.h>

#include "window.hpp"
#include "renderer.hpp"

#define XRES 500
#define YRES 500

#define GAP 12
#define SQUARE 100
#define SIDE (XRES - 3 * SQUARE) / 2
#define ABOVE 30

#define O (SQUARE - 2 * GAP) / 2 
#define X (SQUARE - 2 * GAP)

#define PI 3.1415926

void circle(int x, int y, int r, Renderer &rend)
{
    int prevX = x + r;
    int prevY = y;

    for (double i = 0.0; i < 2.0 * PI; i += (2.0 * PI) / 500.0)
    {
        int nextX = x + (int) (cos(i) * r);
        int nextY = y + (int) (sin(i) * r);

        rend.line(prevX, prevY, nextX, nextY);

        prevX = nextX;
        prevY = nextY;
    }
}

void cross(int x, int y, int width, int height, Renderer &rend)
{
    rend.line(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
    rend.line(x - (width / 2), y + (height / 2), x + (width / 2), y - (height / 2));
}

int main() {

    Window win("gallery.ppm", XRES, YRES, true);
    Renderer draw(win);

    // win.invertX();
    // win.invertY();

    draw.setColor(0, 0, 0);
    draw.fill();
    
    draw.setColor(255, 255, 255);
    
    for (int i = 1; i <= 2; i++)
    {
        draw.line(SIDE, SIDE + ABOVE + (i * SQUARE), SIDE + 3 * SQUARE, SIDE + ABOVE + (i * SQUARE));
        draw.line(SIDE + (i * SQUARE), SIDE + ABOVE, SIDE + (i * SQUARE), SIDE + ABOVE + 3 * SQUARE);
    }
    
    circle(SIDE + (3 * SQUARE / 2), SIDE + ABOVE + (3 * SQUARE / 2), O, draw);
    cross(SIDE + (SQUARE / 2), SIDE + ABOVE + (SQUARE / 2), X, X, draw);
    circle(SIDE + (3 * SQUARE / 2), SIDE + ABOVE + (5 * SQUARE / 2), O, draw);
    cross(SIDE + (3 * SQUARE / 2), SIDE + ABOVE + (SQUARE / 2), X, X, draw);
    circle(SIDE + (5 * SQUARE / 2), SIDE + ABOVE + (SQUARE / 2), O, draw);
    cross(SIDE + (SQUARE / 2), SIDE + ABOVE + (5 * SQUARE / 2), X, X, draw);
    circle(SIDE + (SQUARE / 2), SIDE + ABOVE + (3 * SQUARE / 2), O, draw);
    cross(SIDE + (5 * SQUARE / 2), SIDE + ABOVE + (3 * SQUARE / 2), X, X, draw);
    circle(SIDE + (5 * SQUARE / 2), SIDE + ABOVE + (5 * SQUARE / 2), O, draw);
    cross(SIDE + (SQUARE / 2), SIDE + ABOVE - (SQUARE / 2), X, X, draw);

    draw.setColor(0, 255, 0);
    draw.line(SIDE, SIDE + ABOVE - SQUARE, SIDE + (5 * SQUARE / 2) + X / 2, SIDE + ABOVE + (3 * SQUARE / 2) + X / 2);

    win.display();
    std::cout << "gallery.ppm";
}
