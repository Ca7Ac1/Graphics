#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <thread>
#include <chrono>

#include "window.hpp"
#include "renderer.hpp"
#include "graphics.hpp"
#include "graphics3d.hpp"
#include "transform.hpp"

void parse(Window &w, Renderer &r, std::string fileName)
{
    std::ifstream file(fileName);

    Graphics g;
    Graphics3D g3d;
    Transform t;

    int color[] = {255, 255, 255};

    while (file.good())
    {
        std::string cmd;
        file >> cmd;

        g.clear();
        g3d.clear();
        t.reset();

        if (cmd == "line")
        {
            int coords[6];
            file >> coords[0] >> coords[1] >> coords[2] >> coords[3] >> coords[4] >> coords[5];

            g.addEdge(coords[0], coords[1], coords[2], coords[3], coords[4], coords[5]);
        }
        else if (cmd == "circle")
        {
            int coords[3];
            int radius;

            file >> coords[0] >> coords[1] >> coords[2] >> radius;
            g.addCircle(coords[0], coords[1], coords[2], radius);
        }
        else if (cmd == "bezier")
        {
            int coords[8];

            file >> coords[0] >> coords[1] >> coords[2] >> coords[3] >> coords[4] >> coords[5] >> coords[6] >> coords[7];
            g.addBezierCurve(coords[0], coords[1], 0, coords[2], coords[3], 0,
                             coords[4], coords[5], 0, coords[6], coords[7], 0);
        }
        else if (cmd == "hermite")
        {
            int coords[4];
            int rates[4];

            file >> coords[0] >> coords[1] >> coords[2] >> coords[3] >> rates[0] >> rates[1] >> rates[2] >> rates[3];
            g.addHermiteCurve(coords[0], coords[1], 0, rates[0], rates[1], 0,
                              coords[2], coords[3], 0, rates[2], rates[3], 0);
        }
        else if (cmd == "box")
        {
            int coords[3];
            int dimensions[3];

            file >> coords[0] >> coords[1] >> coords[2] >> dimensions[0] >> dimensions[1] >> dimensions[2];
            g3d.addBox(coords[0], coords[1], coords[2], dimensions[0], dimensions[1], dimensions[2]);
        }
        else if (cmd == "sphere")
        {
            int coords[3];
            int radius;

            file >> coords[0] >> coords[1] >> coords[2] >> radius;
            g3d.addSphere(coords[0], coords[1], coords[2], radius);
        }
        else if (cmd == "torus")
        {
            int coords[3];
            int radii[2];

            file >> coords[0] >> coords[1] >> coords[2] >> radii[0] >> radii[1];
            g3d.addTorus(coords[0], coords[1], coords[2], radii[0], radii[1]);
        }
        else if (cmd == "ident")
        {
            t.reset();
        }
        else if (cmd == "scale")
        {
            double factor[3];
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
            g3d.transform(t);
        }
        else if (cmd == "pop")
        {
            r.deletePlane();
        }
        else if (cmd == "push")
        {
            r.addPlane();
        }
        else if (cmd == "display")
        {
            r.setColor(color[0], color[1], color[2]);

            w.draw("temp.ppm", false);
            w.display();

            // std::cin.ignore();
            system("rm temp.ppm");
        }
        else if (cmd == "save")
        {
            r.setColor(color[0], color[1], color[2]);

            std::string outputFile;
            file >> outputFile;

            w.draw(outputFile, false);
        }
        else if (cmd == "color")
        {
            file >> color[0] >> color[1] >> color[2];
        }
        else if (cmd == "clear")
        {
            r.setColor(0, 0, 0);
            r.fill();
            r.clearZBuffer();
        }
        else if (cmd == "fill")
        {
            int fillColor[] = {0, 0, 0};
            file >> fillColor[0] >> fillColor[1] >> fillColor[2];

            r.setColor(fillColor[0], fillColor[1], fillColor[2]);
            r.fill();
        }
        else if (cmd.find("#") != std::string::npos)
        {
            std::string skip;
            getline(file, skip);
        }
        else if (cmd != "")
        {
            std::cout << "bad command given {" << cmd << "}\n";
        }

        r.transformPlane(t);

        r.setColor(color[0], color[1], color[2]);
        r.draw(g);
        r.draw(g3d);
    }
}
