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

    parse(win, r, "face_script");
}