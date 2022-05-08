#include <iostream>

#include "window.hpp"
#include "renderer.hpp"
#include "script.hpp"

using namespace std;

int main()
{
    Window win(500, 500);
    Renderer r(win);

    win.invertY();

    r.setColor(1, 255, 255);
    r.addPointLight(.5, .75, 1);

    parse(win, r, "script");

    r.clearZBuffer();
    r.clearLights();
    r.clearPlane();

    r.setColor(0, 0, 0);
    r.fill();

    r.setColor(255, 1, 255);
    r.addPointLight(.5, .75, 1);

    r.deletePlane();

    parse(win, r, "script_robot");

    r.clearZBuffer();
    r.clearLights();
    r.clearPlane();

    r.setColor(0, 0, 0);
    r.fill();

    r.setColor(255, 255, 1);
    r.addPointLight(.5, .75, 1);

    parse(win, r, "script_shapes");
}