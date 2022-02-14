#include <vector>
#include <string>
#include <fstream>

#include "window.hpp"

Color::Color(int red, int green, int blue, int scale) : red(red % scale),
                                                        green(green % scale),
                                                        blue(blue % scale),
                                                        scale(scale) {}

void Color::set(int red, int green, int blue)
{
    this->red = red % (scale + 1);
    this->green = green % (scale + 1);
    this->blue = blue % (scale + 1);
}

void Color::setScale(int scale)
{
    this->scale = scale;

    red %= (scale + 1);
    green %= (scale + 1);
    blue %= (scale + 1);
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

Window::Window(const std::string &file, int xDimension, int yDimension, bool binary) : xDimension(xDimension),
                                                                                       yDimension(yDimension),
                                                                                       colorScale(255),
                                                                                       binary(binary),
                                                                                       invertX(false),
                                                                                       invertY(false);
                                                                                       window(xDimension, std::vector<Color>(yDimension, Color(0, 0, 0, colorScale)))
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

void Window::display()
{
    output << (binary ? "P6" : "P3") << '\n'
           << xDimension << " " << yDimension << '\n'
           << colorScale << '\n';

    for (int y = 0; y < yDimension; y++)
    {
        for (int x = 0; x < xDimension; x++)
        {
            int red = window[invertX ? xDimension - x - 1 : x][invertY ? yDimension - y - 1 : y].getRed();
            int blue = window[invertX ? xDimension - x - 1 : x][invertY ? yDimension - y - 1 : y].getBlue();
            int green = window[invertX ? xDimension - x - 1 : x][invertY ? yDimension - y - 1 : y].getGreen();

            if (binary)
            {
                output << (char)red << (char)green << (char)blue;
            }
            else
            {
                output << red << " " << green << " " << blue << " ";
            }
        }
    }

    if (!binary)
    {
        output << '\n';
    }
}

int Window::getXDimension() const
{
    return xDimension;
}

int Window::getYDimension() const
{
    return yDimension;
}

void invertX()
{
    invertX = !invertX;
}

void invertY()
{
    invertY = !invertY;
}

void Window::setColorScale(int colorScale)
{
    this->colorScale = colorScale;

    for (int x = 0; x < xDimension; x++)
    {
        for (int y = 0; y < yDimension; y++)
        {
            window[x][y].setScale(colorScale);
        }
    }
}

int Window::getColorScale() const
{
    return colorScale;
}

std::vector<Color> &Window::operator[](int i)
{
    return window[i];
}