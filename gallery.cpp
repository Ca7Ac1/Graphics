#include <iostream>

#include "window.hpp"
#include "renderer.hpp"
#include "script.hpp"

using namespace std;

int main()
{
    Window win(900, 450);
    Renderer r(win);

    win.invertY();

    parse(win, r, "gallery_script");
}