#include <iostream>

#include "window.hpp"
#include "renderer.hpp"

#define XRES 500
#define YRES 500

int main() {

    Window win("main.ppm", XRES, YRES, true);
    Renderer draw(win);

    // win.invertX();
    win.invertY();

    draw.setColor(0, 0, 0);
    draw.fill();


    //octants 1 and 5
    draw.setColor(0, 255, 0);

    draw.line(0, 0, XRES-1, YRES-1);
    draw.line(0, 0, XRES-1, YRES / 2);
    draw.line(XRES-1, YRES-1, 0, YRES / 2);

    //octants 8 and 4
    draw.setColor(0, 255, 255);
    
    draw.line(0, YRES-1, XRES-1, 0);
    draw.line(0, YRES-1, XRES-1, YRES/2);
    draw.line(XRES-1, 0, 0, YRES/2);

    //octants 2 and 6
    draw.setColor(255, 0, 0);
    
    draw.line(0, 0, XRES/2, YRES-1);
    draw.line(XRES-1, YRES-1, XRES/2, 0);

    //octants 7 and 3
    draw.setColor(255, 0, 255);

    draw.line(0, YRES-1, XRES/2, 0);
    draw.line(XRES-1, 0, XRES/2, YRES-1);

    //horizontal and vertical
    draw.setColor(255, 255, 0);

    draw.line(0, YRES/2, XRES-1, YRES/2);
    draw.line(XRES/2, 0, XRES/2, YRES-1);

    win.display();
    std::cout << "main.ppm";
}
