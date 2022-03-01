#include <iostream>
#include <random>
#include <ctime>

#include "window.hpp"
#include "renderer.hpp"
#include "graphics.hpp"

using namespace std;

void inkling(Graphics &g)
{
    g.addEdge(0, 9, 0, 7, 16, 0);
    g.addEdge(7, 16, 0, 9, 16, 0);
    g.addEdge(9, 16, 0, 16, 9, 0);
    g.addEdge(16, 9, 0, 16, 8, 0);
    g.addEdge(16, 8, 0, 13, 6, 0);
    g.addEdge(13, 6, 0, 13, 1, 0);
    g.addEdge(13, 1, 0, 12, 0, 0);
    g.addEdge(12, 0, 0, 11, 1, 0);
    g.addEdge(11, 1, 0, 10, 0, 0);
    g.addEdge(10, 0, 0, 8, 2, 0);
    g.addEdge(8, 2, 0, 6, 0, 0);
    g.addEdge(6, 0, 0, 5, 1, 0);
    g.addEdge(5, 1, 0, 4, 0, 0);
    g.addEdge(4, 0, 0, 3, 1, 0);
    g.addEdge(3, 1, 0, 3, 6, 0);
    g.addEdge(3, 6, 0, 0, 8, 0);
    g.addEdge(0, 8, 0, 0, 9, 0);
}

void transform_random(Matrix &transform)
{
    transform.setIdentity();
    transform[3][0] = rand() % 300 + (100 - 8);
    transform[3][1] = rand() % 300 + (100 - 8);
    transform[0][0] = (rand() % 3) + 1;
    transform[1][1] = transform[0][0];

    // transform.print();
}

int main()
{
    srand(time(NULL));

    Window win("gallery.ppm", 500, 500, true);
    Renderer r(win);
    Graphics g;

    win.invertY();

    inkling(g);

    Matrix transform;

    transform.setIdentity();
    transform[3][0] = 250 - (30 * 8);
    transform[3][1] = 250 - (30 * 8);
    transform[0][0] = 30;
    transform[1][1] = 30;

    g.transform(transform);

    r.setColor(0, 0, 0);
    r.fill();

    r.setColor(0, 183, 23);
    r.draw(g);

    g.clear();
    inkling(g);

    r.setColor(0, 255, 255);
    for (int i = 0; i < 35; i++)
    {
        g.clear();
        inkling(g);

        transform_random(transform);
        g.transform(transform);

        r.draw(g);
    }

    win.display();
}