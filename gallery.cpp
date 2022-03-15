#include <iostream>

#include "window.hpp"
#include "renderer.hpp"
#include "script.hpp"

using namespace std;

int main()
{
    Window win(900, 400);
    Renderer r(win);

    parse(win, r, "gallery_script");
}