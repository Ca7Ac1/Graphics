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

    Graphics3D ball;
    Graphics3D beam;

    Graphics3D rings[5];

    Transform t;

    
    ball.addSphere(0, 0, 0, 200);
    t.reset();
    t.addTranslation(250, 250, 0);
    ball.transform(t);

    beam.addBox(0, 600, 0, 24, 600, 24);
    t.reset();
    t.addRotation(90, Axis::X);
    t.addTranslation(250 - 12, 250 - 12, 200);
    beam.transform(t);

    for (int i = 0; i < 5; i++)
    {
        rings[i].addTorus(0, 0, 0, 10, 110 - 20 * i, 20, 20);
        t.reset();
        t.addRotation(90, Axis::X);
        t.addTranslation(250, 250, 200 + 80 * i);
        rings[i].transform(t);
    }
    
    t.reset();

    t.addTranslation(0, 0, -300);
    t.addRotation(-30, Axis::Y);
    t.addRotation(15, Axis::X);

    for (int i = 0; i < 5; i++)
    {
        rings[i].transform(t);
    }
    ball.transform(t);
    beam.transform(t);

    r.setColor(255, 255, 255);
    r.fill();

    r.setColor(192, 192, 192);
    r.draw(ball);

    r.setColor(57, 255, 20);
    r.draw(beam);

    r.setColor(0, 0, 0);
    for (int i = 0; i < 5; i++)
    {
        r.draw(rings[i]);
    }

    win.draw("gallery.ppm");
}