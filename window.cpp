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

void Color::print() const
{
    std::cout << "(red: " << red << ", green: " << green << ", blue: " << blue << ")\n";
}

Window::Window(const std::string &file, int xDimension, int yDimension) : file(file),
                                                                          xDimension(xDimension),
                                                                          yDimension(yDimension),
                                                                          window(xDimension, std::vector<Color>(yDimension, Color(0, 0, 0))) {}

Window::~Window()
{
    output.close();
}

void Window::display(bool binary = false)
{
    if (binary)
    {
        output.open(file, std::ios::binary);
    }
    else
    {
        output.open(file);
    }

    output << "P3\n"
           << xDimension << " " << yDimension << "\n255\n";

    for (int i = 0; i < yDimension; i++)
    {
        for (int j = 0; j < xDimension; j++)
        {
            output << window[j][i].getRed() << " " << window[j][i].getGreen() << " " << window[j][i].getBlue() << " ";
        }

        output << '\n';
    }

    output.close();
    output.clear();
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