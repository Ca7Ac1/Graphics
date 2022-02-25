#include <iostream>

#include "window.hpp"
#include "renderer.hpp"
#include "graphics.hpp"

int main()
{
    Window win("main.ppm", 500, 500, true);
    Renderer r(win);
    Graphics g;

    win.invertY();

    g.addEdge(50, 450, 0, 100, 450, 0);
    g.addEdge(50, 450, 0, 50, 400, 0);
    g.addEdge(100, 450, 0, 100, 400, 0);
    g.addEdge(100, 400, 0, 50, 400, 0);

    g.addEdge(200, 450, 0, 250, 450, 0);
    g.addEdge(200, 450, 0, 200, 400, 0);
    g.addEdge(250, 450, 0, 250, 400, 0);
    g.addEdge(250, 400, 0, 200, 400, 0);

    g.addEdge(150, 400, 0, 130, 360, 0);
    g.addEdge(150, 400, 0, 170, 360, 0);
    g.addEdge(130, 360, 0, 170, 360, 0);

    g.addEdge(100, 340, 0, 200, 340, 0);
    g.addEdge(100, 320, 0, 200, 320, 0);
    g.addEdge(100, 340, 0, 100, 320, 0);
    g.addEdge(200, 340, 0, 200, 320, 0);

    r.setColor(0, 0, 0);
    r.fill();

    r.setColor(255, 255, 255);
    r.draw(g);
 
    std::cout << "\n\n";

    win.display();
}
