#include <iostream>
#include <string>
#include <fstream>

#include "window.hpp"
#include "renderer.hpp"
#include "graphics.hpp"
#include "transform.hpp"

void parse(Window &w, Renderer &r, std::string fileName)
{
    std::ifstream file(fileName);

    Graphics g;
    Transform t;

    int color[] = {255, 255, 255};

    while (file.good())
    {
        std::string cmd;
        file >> cmd;

        if (cmd == "line")
        {
            int coords[6];
            file >> coords[0] >> coords[1] >> coords[2] >> coords[3] >> coords[4] >> coords[5];

            g.addEdge(coords[0], coords[1], coords[2], coords[3], coords[4], coords[5]);
        }
        else if (cmd == "ident")
        {
            t.reset();
        }
        else if (cmd == "scale")
        {
            int factor[3];
            file >> factor[0] >> factor[1] >> factor[2];

            t.addDilation(factor[0], factor[1], factor[2]);
        }
        else if (cmd == "move")
        {
            int amt[3];
            file >> amt[0] >> amt[1] >> amt[2];

            t.addTranslation(amt[0], amt[1], amt[2]);
        }
        else if (cmd == "rotate")
        {
            char axis;
            double theta;
            file >> axis >> theta;

            switch (axis)
            {
            case 'x':
                t.addRotation(theta, Axis::X);
                break;
            case 'y':
                t.addRotation(theta, Axis::Y);
                break;
            case 'z':
                t.addRotation(theta, Axis::Z);
                break;
            }
        }
        else if (cmd == "apply")
        {
            g.transform(t);
        }
        else if (cmd == "display")
        {
            r.setColor(0, 0, 0);
            r.fill();

            r.setColor(color[0], color[1], color[2]);
            r.draw(g);

            w.draw("temp.ppm");
            w.display();
        }
        else if (cmd == "save")
        {
            r.setColor(0, 0, 0);
            r.fill();

            r.setColor(color[0], color[1], color[2]);
            r.draw(g);

            std::string outputFile;
            file >> outputFile;

            w.draw(outputFile);
        }
        else if (cmd == "color")
        {
            file >> color[0] >> color[1] >> color[2];
        }
        else if (cmd == "")
        {
            continue;
        }
        else
        {
            std::cout << "bad command given {" << cmd << "}\n";
        }
    }
}