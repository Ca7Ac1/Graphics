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

    r.setColor(50, 255, 255);
    r.addPointLight(.5, .75, 1);

    parse(win, r, "script");
}