#include <vector>
#include <string>
#include <fstream>

#include "window.hpp"

Color::Color(int red, int green, int blue) : red(red), green(green), blue(blue) {}

void Color::set(int red, int green, int blue)
{
    this->red = red;
    this->green = green;
    this->blue = blue;
}

int Color::getRed() const
{
    return red;
}

int Color::getGreen() const
{
    return green;
}

int Color::getBlue() const
{
    return blue;
}

void Color::draw(std::ofstream &output, bool binary)
{
    if (binary)
    {
        output.write((char *)&red, sizeof(int));
        output.write(" ", sizeof(char) * 2);
        output.write((char *)&green, sizeof(int));
        output.write(" ", sizeof(char) * 2);
        output.write((char *)&blue, sizeof(int));
        output.write(" ", sizeof(char) * 2);
    }
    else
    {
        output << red << " " << green << " " << blue << " ";
    }
}

void Color::print() const
{
    std::cout << "(red: " << red << ", green: " << green << ", blue: " << blue << ")\n";
}

Window::Window(const std::string &file, int xDimension, int yDimension, bool binary) : xDimension(xDimension),
                                                                                       yDimension(yDimension),
                                                                                       window(xDimension, std::vector<Color>(yDimension, Color(0, 0, 0))),
                                                                                       binary(binary)
{
    if (binary)
    {
        output.open(file, std::ios::out | std::ios::binary);
    }
    else
    {
        output.open(file);
    }
}

Window::~Window()
{
    output.close();
}

void Window::display()
{
    int scale = 255;

    if (binary)
    {

        output.write("P3", sizeof(char) * 3);
        output.write(" ", sizeof(char) * 2);
        output.write((char *)&xDimension, sizeof(int));
        output.write(" ", sizeof(char) * 2);
        output.write((char *)&yDimension, sizeof(int));
        output.write(" ", sizeof(char) * 2);
        output.write((char *)&scale, sizeof(int));
    }
    else
    {
        output << "P3" << '\n'
               << xDimension << " " << yDimension << '\n'
               << scale << '\n';
    }

    for (int i = 0; i < yDimension; i++)
    {
        for (int j = 0; j < xDimension; j++)
        {
            window[j][i].draw(output, binary);
        }
    }

    if (!binary)
    {
        output << '\n';
    }
}

int Window::getX()
{
    return xDimension;
}

int Window::getY()
{
    return yDimension;
}

std::vector<Color> &Window::operator[](int i)
{
    return window[i];
}